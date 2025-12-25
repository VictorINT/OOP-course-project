#include "../../include/managers/ServiceManager.h"
#include "../../include/models/Receptioner.h"
#include "../../include/models/Tehnician.h"
#include "../../include/models/Supervizor.h"
#include "../../include/utils/Factory.h"
#include "../../include/utils/DateUtils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

namespace {
    string trim(const string& value) {
        const string whitespace = " \t\r\n";
        size_t start = value.find_first_not_of(whitespace);
        if (start == string::npos) return "";
        size_t end = value.find_last_not_of(whitespace);
        return value.substr(start, end - start + 1);
    }
}

ServiceManager::ServiceManager() {}

ServiceManager::~ServiceManager() {
    // shared_ptr cleanup automat
}

ServiceManager& ServiceManager::getInstance() {
    static ServiceManager instance;
    return instance;
}

void ServiceManager::adaugaAngajat(std::shared_ptr<Angajat> angajat) {
    angajati.push_back(angajat);
}

std::shared_ptr<Angajat> ServiceManager::cautaAngajat(int id) {
    for(auto angajat : angajati){
        if(angajat && angajat->getId() == id)
            return angajat;
    }

    return nullptr;
}

const std::vector<std::shared_ptr<Angajat>>& ServiceManager::getAngajati() const {
    return angajati;
}

void ServiceManager::adaugaElectrocasnic(std::shared_ptr<Electrocasnic> electrocasnic) {
    electrocasnice.push_back(electrocasnic);
}

const std::vector<std::shared_ptr<Electrocasnic>>& ServiceManager::getElectrocasnice() const {
    return electrocasnice;
}

void ServiceManager::adaugaCerere(std::shared_ptr<CerereReparatie> cerere) {
    cereri.push_back(cerere);
}

std::shared_ptr<CerereReparatie> ServiceManager::cautaCerere(int id) {
    for (auto cerere : cereri){
        if(cerere && cerere->getId() == id)
            return cerere;
    }

    return nullptr;
}

const std::vector<std::shared_ptr<CerereReparatie>>& ServiceManager::getCereri() const {
    return cereri;
}

void ServiceManager::incarcaAngajatiDinCSV(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Nu s-a putut deschide fisierul angajati: " << filepath << "\n";
        return;
    }

    string line;
    getline(file, line); // header

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        vector<string> cols;
        string col;
        while (getline(ss, col, ',')) {
            cols.push_back(trim(col));
        }

        if (cols.size() < 4) {
            cerr << "Linie angajat invalida: " << line << "\n";
            continue;
        }

        int id = stoi(cols[0]);
        string tip = cols[1];
        string nume = cols[2];
        string cnp = cols[3];
        string extra = cols.size() > 4 ? cols[4] : "";

        auto angajat = Factory::creeazaAngajat(tip, id, nume, cnp, extra);
        if (angajat != nullptr) {
            adaugaAngajat(angajat);
        }
    }
}

void ServiceManager::incarcaElectrocasniceDinCSV(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Nu s-a putut deschide fisierul electrocasnice: " << filepath << "\n";
        return;
    }

    string line;
    getline(file, line); // header

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        vector<string> cols;
        string col;
        while (getline(ss, col, ',')) {
            cols.push_back(trim(col));
        }

        if (cols.size() < 4) {
            cerr << "Linie electrocasnic invalida: " << line << "\n";
            continue;
        }

        string tip = cols[0];
        string marca = cols[1];
        string model = cols[2];
        int anFabricatie = stoi(cols[3]);
        string parametri = cols.size() > 4 ? cols[4] : "";

        auto aparat = Factory::creeazaElectrocasnic(tip, marca, model, anFabricatie, parametri);
        if (aparat != nullptr) {
            adaugaElectrocasnic(aparat);
        }
    }
}

void ServiceManager::incarcaCereriDinCSV(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Nu s-a putut deschide fisierul cereri: " << filepath << "\n";
        return;
    }

    string line;
    getline(file, line); // header

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        vector<string> cols;
        string col;
        while (getline(ss, col, ',')) {
            cols.push_back(trim(col));
        }

        if (cols.size() < 6) {
            cerr << "Linie cerere invalida: " << line << "\n";
            continue;
        }

        int id = stoi(cols[0]);
        string tipAparat = cols[1];
        string marca = cols[2];
        string model = cols[3];
        string descriere = cols[4];
        string dataStr = cols[5];

        std::shared_ptr<Electrocasnic> aparat = nullptr;
        for (auto existing : electrocasnice) {
            if (existing != nullptr && existing->getTip() == tipAparat && existing->getMarca() == marca && existing->getModel() == model) {
                aparat = existing;
                break;
            }
        }

        if (aparat == nullptr) {
            aparat = Factory::creeazaElectrocasnic(tipAparat, marca, model, 0, "");
            if (aparat != nullptr) {
                adaugaElectrocasnic(aparat);
            }
        }

        if (aparat == nullptr) {
            cerr << "Nu s-a putut crea/aprovisiona aparatul pentru cerere: " << line << "\n";
            continue;
        }

        auto cerere = std::make_shared<CerereReparatie>(id, aparat, descriere);
        cerere->setDataInregistrare(DateUtils::parseTimestamp(dataStr));
        adaugaCerere(cerere);
    }
}

void ServiceManager::adaugaEveniment(long long timestamp, const string& mesaj) {
    evenimente.push_back({timestamp, mesaj});
}

const vector<ServiceManager::EvenimentSimulare>& ServiceManager::getEvenimente() const {
    return evenimente;
}
