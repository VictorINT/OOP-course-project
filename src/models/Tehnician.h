#ifndef TEHNICIAN_H
#define TEHNICIAN_H

#include "Employee.h"
#include <map>
#include <vector>
#include <memory>

using namespace std;

class CerereReparatie;

class Tehnician : public Employee {
private:
    map<string, vector<string>> specializari;
    vector<shared_ptr<CerereReparatie>> cereriActive;
    double durataTotala;
    double valoareReparatiiEfectuate;
    
public:
    Tehnician(const string&, const string&, const string&, 
              const string&, const string&);
    
    double calculeazaSalariu() const override;
    string getTipAngajat() const override;
    void afiseazaDetalii() const override;
    
    // Metode specifice
    void adaugaSpecializare(const string&, const string&);
    bool poateRepara(const string&, const string&) const;
    bool areLoc() const;
    void adaugaCerereActiva(shared_ptr<CerereReparatie>);
    void eliminaCerereActiva(shared_ptr<CerereReparatie>);
    void adaugaValoareReparatie(double);
    
    double getDurataTotala() const;
    const vector<shared_ptr<CerereReparatie>>& getCereriActive() const;
    const map<string, vector<string>>& getSpecializari() const;
};

#endif

