#include "../../include/managers/ReportGenerator.h"
#include "../../include/managers/ServiceManager.h"
#include "../../include/models/Tehnician.h"
#include "../../include/utils/DateUtils.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <memory>

#include <iostream>

using namespace std;

namespace {
    string statusToString(StatusCerere status) {
        switch (status) {
            case StatusCerere::IN_ASTEPTARE: return "IN_ASTEPTARE";
            case StatusCerere::IN_LUCRU: return "IN_LUCRU";
            case StatusCerere::FINALIZATA: return "FINALIZATA";
            case StatusCerere::ANULATA: return "ANULATA";
        }
        return "NECUNOSCUT";
    }
}

ReportGenerator::ReportGenerator() {}

void ReportGenerator::genereazaRaportAngajati(const string& filepath) {
    asiguraDirector(filepath);
    ofstream out(filepath);
    if (!out.is_open()) {
        cerr << "Nu s-a putut scrie raportul angajati: " << filepath << "\n";
        return;
    }

    out << "ID,Tip,Nume,CNP,Salariu" << '\n';
    const auto& angajati = ServiceManager::getInstance().getAngajati();
    for (auto angajat : angajati) {
        if (!angajat) continue;
        out << angajat->getId() << ','
            << escapeCSV(angajat->getTip()) << ','
            << escapeCSV(angajat->getNume()) << ','
            << escapeCSV(angajat->getCnp()) << ','
            << angajat->getSalariu() << '\n';
    }
}

void ReportGenerator::genereazaRaportCereri(const string& filepath) {
    asiguraDirector(filepath);
    ofstream out(filepath);
    if (!out.is_open()) {
        cerr << "Nu s-a putut scrie raportul cereri: " << filepath << "\n";
        return;
    }

    out << "ID,Tip,Marca,Model,Status,Tehnician,CostTotal" << '\n';
    const auto& cereri = ServiceManager::getInstance().getCereri();
    for (auto cerere : cereri) {
        if (!cerere) continue;
        auto aparat = cerere->getAparat();
        string tip = aparat ? aparat->getTip() : "";
        string marca = aparat ? aparat->getMarca() : "";
        string model = aparat ? aparat->getModel() : "";
        auto tehnicianPtr = cerere->getTehnicianAlocat();
        string tehnician = tehnicianPtr ? tehnicianPtr->getNume() : "";
        out << cerere->getId() << ','
            << escapeCSV(tip) << ','
            << escapeCSV(marca) << ','
            << escapeCSV(model) << ','
            << escapeCSV(statusToString(cerere->getStatus())) << ','
            << escapeCSV(tehnician) << ','
            << cerere->getCostTotal() << '\n';
    }
}

void ReportGenerator::genereazaRaportFinanciar(const string& filepath) {
    asiguraDirector(filepath);
    ofstream out(filepath);
    if (!out.is_open()) {
        cerr << "Nu s-a putut scrie raportul financiar: " << filepath << "\n";
        return;
    }

    double totalFinalizat = 0.0;
    double totalInLucru = 0.0;

    const auto& cereri = ServiceManager::getInstance().getCereri();
    for (auto cerere : cereri) {
        if (!cerere) continue;
        if (cerere->getStatus() == StatusCerere::FINALIZATA) {
            totalFinalizat += cerere->getCostTotal();
        } else if (cerere->getStatus() == StatusCerere::IN_LUCRU) {
            totalInLucru += cerere->getCostTotal();
        }
    }

    out << "Categorie,Valoare" << '\n';
    out << "TotalFinalizat," << totalFinalizat << '\n';
    out << "TotalInLucru," << totalInLucru << '\n';
}

void ReportGenerator::genereazaRaportPerformanta(const string& filepath) {
    asiguraDirector(filepath);
    ofstream out(filepath);
    if (!out.is_open()) {
        cerr << "Nu s-a putut scrie raportul performanta: " << filepath << "\n";
        return;
    }

    const auto& angajati = ServiceManager::getInstance().getAngajati();
    std::shared_ptr<Tehnician> topTech = nullptr;
    size_t maxReparatii = 0;

    for (auto angajat : angajati) {
        auto tech = std::dynamic_pointer_cast<Tehnician>(angajat);
        if (!tech) continue;
        size_t cnt = tech->getReparatii().size();
        if (cnt > maxReparatii) {
            maxReparatii = cnt;
            topTech = tech;
        }
    }

    out << "Nume,Specializare,NumarReparatii,Salariu" << '\n';
    if (topTech != nullptr) {
        out << escapeCSV(topTech->getNume()) << ','
            << escapeCSV(topTech->getSpecializare()) << ','
            << topTech->getReparatii().size() << ','
            << topTech->getSalariu() << '\n';
    }
}

void ReportGenerator::genereazaRaportEvenimente(const string& filepath) {
    asiguraDirector(filepath);
    ofstream out(filepath);
    if (!out.is_open()) {
        cerr << "Nu s-a putut scrie raportul evenimente: " << filepath << "\n";
        return;
    }

    out << "Timestamp,Eveniment" << '\n';
    const auto& evenimente = ServiceManager::getInstance().getEvenimente();
    for (const auto& ev : evenimente) {
        string ts = DateUtils::formatTimestamp(ev.timestamp);
        out << escapeCSV(ts) << ',' << escapeCSV(ev.mesaj) << '\n';
    }
}

string ReportGenerator::escapeCSV(const string& field) {
    bool needQuotes = field.find(',') != string::npos || field.find('"') != string::npos || field.find('\n') != string::npos;
    if (!needQuotes) {
        return field;
    }

    string escaped;
    for (char c : field) {
        if (c == '"') {
            escaped.push_back('"');
        }
        escaped.push_back(c);
    }
    return string("\"") + escaped + string("\"");
}

void ReportGenerator::asiguraDirector(const string& filepath) {
    try {
        std::filesystem::path p(filepath);
        auto dir = p.parent_path();
        if (!dir.empty()) {
            std::filesystem::create_directories(dir);
        }
    } catch (const std::exception& e) {
        cerr << "Eroare la crearea directorului pentru raport: " << e.what() << "\n";
    }
}
