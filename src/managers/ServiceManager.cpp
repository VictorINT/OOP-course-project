#include "../../include/managers/ServiceManager.h"
#include "../../include/models/Receptioner.h"
#include "../../include/models/Tehnician.h"
#include "../../include/models/Supervizor.h"
#include "../../include/utils/Factory.h"
#include "../../include/utils/DateUtils.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

ServiceManager* ServiceManager::instance = nullptr;

ServiceManager::ServiceManager() {}

ServiceManager::~ServiceManager() {
    // Cleanup
    for (auto angajat : angajati) {
        delete angajat;
    }
    for (auto electrocasnic : electrocasnice) {
        delete electrocasnic;
    }
    for (auto cerere : cereri) {
        delete cerere;
    }
}

ServiceManager* ServiceManager::getInstance() {
    if (instance == nullptr) {
        instance = new ServiceManager();
    }
    return instance;
}

void ServiceManager::deleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

void ServiceManager::adaugaAngajat(Angajat* angajat) {
    angajati.push_back(angajat);
}

Angajat* ServiceManager::cautaAngajat(int id) {
    for(auto angajat : angajati){
        if(angajat->getId() == id)
            return angajat;
    }

    return nullptr;
}

const vector<Angajat*>& ServiceManager::getAngajati() const {
    return angajati;
}

void ServiceManager::adaugaElectrocasnic(Electrocasnic* electrocasnic) {
    electrocasnice.push_back(electrocasnic);
}

const vector<Electrocasnic*>& ServiceManager::getElectrocasnice() const {
    return electrocasnice;
}

void ServiceManager::adaugaCerere(CerereReparatie* cerere) {
    cereri.push_back(cerere);
}

CerereReparatie* ServiceManager::cautaCerere(int id) {
    for (auto cerere : cereri){
        if(cerere->getId() == id)
            return cerere;
    }

    return nullptr;
}

const vector<CerereReparatie*>& ServiceManager::getCereri() const {
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
            cols.push_back(col);
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

        Angajat* angajat = Factory::creeazaAngajat(tip, id, nume, cnp, extra);
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
            cols.push_back(col);
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

        Electrocasnic* aparat = Factory::creeazaElectrocasnic(tip, marca, model, anFabricatie, parametri);
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
            cols.push_back(col);
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

        Electrocasnic* aparat = nullptr;
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

        CerereReparatie* cerere = new CerereReparatie(id, aparat, descriere);
        cerere->setDataInregistrare(DateUtils::parseTimestamp(dataStr));
        adaugaCerere(cerere);
    }
}
