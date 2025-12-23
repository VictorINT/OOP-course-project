#include "../../include/managers/ServiceManager.h"
#include "../../include/models/Receptioner.h"
#include "../../include/models/Tehnician.h"
#include "../../include/models/Supervizor.h"
#include <fstream>
#include <sstream>

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
    // TODO: Implement search logic
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
    // TODO: Implement search logic
    return nullptr;
}

const vector<CerereReparatie*>& ServiceManager::getCereri() const {
    return cereri;
}

void ServiceManager::incarcaAngajatiDinCSV(const string& filepath) {
    // TODO: Implement CSV loading logic
}

void ServiceManager::incarcaElectrocasniceDinCSV(const string& filepath) {
    // TODO: Implement CSV loading logic
}

void ServiceManager::incarcaCereriDinCSV(const string& filepath) {
    // TODO: Implement CSV loading logic
}
