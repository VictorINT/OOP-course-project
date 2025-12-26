#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include <vector>
#include <map>
#include <queue>
#include <memory>
#include <string>
#include "../models/Employee.h"
#include "../models/Tehnician.h"
#include "../models/Receptioner.h"
#include "../models/Supervizor.h"
#include "../models/Electrocasnic.h"
#include "../models/CerereReparatie.h"

using namespace std;

// Structura pentru informatii despre aparate reparabile
struct ApparatInfo {
    string model;
    int anFabricatie;
    double pretCatalog;
    string detaliiSpecifice;
};

class ServiceManager {
private:
    // Singleton
    ServiceManager() = default;
    ServiceManager(const ServiceManager&) = delete;
    ServiceManager& operator=(const ServiceManager&) = delete;
    
    // Date
    vector<shared_ptr<Employee>> angajati;
    map<string, map<string, vector<ApparatInfo>>> aparateReparabile;
    queue<shared_ptr<CerereReparatie>> cereriInAsteptare;
    vector<shared_ptr<CerereReparatie>> toateCererile;
    vector<shared_ptr<CerereReparatie>> cereriFinalizate;
    map<string, int> aparateNereparabile;  // marca:model -> numar aparitii
    vector<string> istoricSimulare;  // Istoric mesaje simulare
    
public:
    static ServiceManager& getInstance();
    
    // Gestiune angajati
    void adaugaAngajat(shared_ptr<Employee>);
    void stergeAngajat(const string&);  // dupa CNP
    void modificaNumeAngajat(const string&, const string&, const string&);
    shared_ptr<Employee> cautaAngajatDupaCNP(const string&) const;
    void afiseazaAngajati() const;
    bool poateFunctiona() const;
    
    // Gestiune electrocasnice
    void adaugaAparatReparabil(const string&, const string&, const ApparatInfo&);
    void stergeAparatReparabil(const string&, const string&, const string&);
    bool poateRepara(const string&, const string&, const string&) const;
    void afiseazaAparateReparabile() const;
    void afiseazaAparateNereparabile() const;
    
    // Procesare cereri
    void adaugaCerere(shared_ptr<CerereReparatie>);
    bool alocareCerere(shared_ptr<CerereReparatie>);
    void procesareCereriInAsteptare();
    
    // Simulare
    void simulareUnTic();
    void afiseazaStatusCurent() const;
    
    // Raportari
    vector<shared_ptr<Employee>> getTop3Salarii() const;
    shared_ptr<Tehnician> getTehnicianCeaMaiLungaReparatie() const;
    map<string, vector<shared_ptr<CerereReparatie>>> 
        getCereriInAsteptareGrupate() const;
    vector<string> getIstoricSimulare() const;
    
    // Getters
    const vector<shared_ptr<Employee>>& getAngajati() const;
    const vector<shared_ptr<CerereReparatie>>& getToateCererile() const;
    
private:
    vector<shared_ptr<Tehnician>> getTehnicieni() const;
    shared_ptr<Tehnician> gasesteTehnicianOptim(const string&, const string&);
};

#endif

