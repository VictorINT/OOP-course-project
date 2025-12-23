#pragma once
#include "Angajat.h"
#include <vector>

using namespace std;

class CerereReparatie;

class Receptioner : public Angajat {
private:
    vector<CerereReparatie*> cereriGestionate;

public:
    Receptioner();
    Receptioner(int, const string&, const string&);
    ~Receptioner() override;
    
    double getSalariu() const override;
    string getTip() const override;
    
    void adaugaCerere(CerereReparatie*);
    const vector<CerereReparatie*>& getCereri() const;
};
