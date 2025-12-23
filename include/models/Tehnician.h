#pragma once
#include "Angajat.h"
#include <string>
#include <vector>

using namespace std;

class CerereReparatie;

class Tehnician : public Angajat {
private:
    string specializare;
    vector<CerereReparatie*> reparatiiEfectuate;

public:
    Tehnician();
    Tehnician(int, const string&, const string&, const string&);
    ~Tehnician() override;
    
    double getSalariu() const override;
    string getTip() const override;
    
    string getSpecializare() const;
    void adaugaReparatie(CerereReparatie*);
    const vector<CerereReparatie*>& getReparatii() const;
};
