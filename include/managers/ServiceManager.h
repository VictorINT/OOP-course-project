#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../models/Angajat.h"
#include "../models/Electrocasnic.h"
#include "../models/CerereReparatie.h"

using namespace std;

class ServiceManager {
public:
    struct EvenimentSimulare {
        long long timestamp;
        string mesaj;
    };

private:
    // Stocare cu shared_ptr (owner: ServiceManager)
    std::vector<std::shared_ptr<Angajat>> angajati;
    std::vector<std::shared_ptr<Electrocasnic>> electrocasnice;
    std::vector<std::shared_ptr<CerereReparatie>> cereri;
    vector<EvenimentSimulare> evenimente;
    
    ServiceManager();
    ~ServiceManager();

public:
    // Singleton – acces prin referinta (fara raw pointer)
    static ServiceManager& getInstance();
    
    ServiceManager(const ServiceManager&) = delete;
    ServiceManager& operator=(const ServiceManager&) = delete;
    
    // Angajati management
    void adaugaAngajat(std::shared_ptr<Angajat>);
    std::shared_ptr<Angajat> cautaAngajat(int);
    const std::vector<std::shared_ptr<Angajat>>& getAngajati() const;
    
    // Electrocasnice management
    void adaugaElectrocasnic(std::shared_ptr<Electrocasnic>);
    const std::vector<std::shared_ptr<Electrocasnic>>& getElectrocasnice() const;
    
    // Cereri management
    void adaugaCerere(std::shared_ptr<CerereReparatie>);
    std::shared_ptr<CerereReparatie> cautaCerere(int);
    const std::vector<std::shared_ptr<CerereReparatie>>& getCereri() const;
    
    // Incarcari din fisiere
    void incarcaAngajatiDinCSV(const string&);
    void incarcaElectrocasniceDinCSV(const string&);
    void incarcaCereriDinCSV(const string&);

    // Evenimente simulare
    void adaugaEveniment(long long, const string&);
    const vector<EvenimentSimulare>& getEvenimente() const;
};
