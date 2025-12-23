#pragma once
#include <vector>
#include <string>
#include "../models/Angajat.h"
#include "../models/Electrocasnic.h"
#include "../models/CerereReparatie.h"

using namespace std;

class ServiceManager {
private:
    static ServiceManager* instance;
    vector<Angajat*> angajati;
    vector<Electrocasnic*> electrocasnice;
    vector<CerereReparatie*> cereri;
    
    ServiceManager();
    ~ServiceManager();

public:
    static ServiceManager* getInstance();
    static void deleteInstance();
    
    ServiceManager(const ServiceManager&) = delete;
    ServiceManager& operator=(const ServiceManager&) = delete;
    
    // Angajati management
    void adaugaAngajat(Angajat*);
    Angajat* cautaAngajat(int);
    const vector<Angajat*>& getAngajati() const;
    
    // Electrocasnice management
    void adaugaElectrocasnic(Electrocasnic*);
    const vector<Electrocasnic*>& getElectrocasnice() const;
    
    // Cereri management
    void adaugaCerere(CerereReparatie*);
    CerereReparatie* cautaCerere(int);
    const vector<CerereReparatie*>& getCereri() const;
    
    // Incarcari din fisiere
    void incarcaAngajatiDinCSV(const string&);
    void incarcaElectrocasniceDinCSV(const string&);
    void incarcaCereriDinCSV(const string&);
};
