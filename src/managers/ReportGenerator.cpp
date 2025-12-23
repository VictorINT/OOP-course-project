#include "../../include/managers/ReportGenerator.h"
#include "../../include/managers/ServiceManager.h"
#include "../../include/models/Tehnician.h"
#include <fstream>
#include <sstream>

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
    ofstream out(filepath);
    if (!out.is_open()) {
        cerr << "Nu s-a putut scrie raportul angajati: " << filepath << "\n";
        return;
    }

    out << "ID,Tip,Nume,CNP,Salariu" << '\n';
    const auto& angajati = ServiceManager::getInstance()->getAngajati();
    for (auto angajat : angajati) {
        if (angajat == nullptr) continue;
        out << angajat->getId() << ','
            << escapeCSV(angajat->getTip()) << ','
            << escapeCSV(angajat->getNume()) << ','
            << escapeCSV(angajat->getCnp()) << ','
            << angajat->getSalariu() << '\n';
    }
}

void ReportGenerator::genereazaRaportCereri(const string& filepath) {
    ofstream out(filepath);
    if (!out.is_open()) {
        cerr << "Nu s-a putut scrie raportul cereri: " << filepath << "\n";
        return;
    }

    out << "ID,Tip,Marca,Model,Status,Tehnician,CostTotal" << '\n';
    const auto& cereri = ServiceManager::getInstance()->getCereri();
    for (auto cerere : cereri) {
        if (cerere == nullptr) continue;
        Electrocasnic* aparat = cerere->getAparat();
        string tip = aparat ? aparat->getTip() : "";
        string marca = aparat ? aparat->getMarca() : "";
        string model = aparat ? aparat->getModel() : "";
        string tehnician = cerere->getTehnicianAlocat() ? cerere->getTehnicianAlocat()->getNume() : "";
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
    ofstream out(filepath);
    if (!out.is_open()) {
        cerr << "Nu s-a putut scrie raportul financiar: " << filepath << "\n";
        return;
    }

    double totalFinalizat = 0.0;
    double totalInLucru = 0.0;

    const auto& cereri = ServiceManager::getInstance()->getCereri();
    for (auto cerere : cereri) {
        if (cerere == nullptr) continue;
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
    ofstream out(filepath);
    if (!out.is_open()) {
        cerr << "Nu s-a putut scrie raportul performanta: " << filepath << "\n";
        return;
    }

    const auto& angajati = ServiceManager::getInstance()->getAngajati();
    Tehnician* topTech = nullptr;
    size_t maxReparatii = 0;

    for (auto angajat : angajati) {
        Tehnician* tech = dynamic_cast<Tehnician*>(angajat);
        if (tech == nullptr) continue;
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
