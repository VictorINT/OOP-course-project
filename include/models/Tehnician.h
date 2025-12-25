#pragma once
#include "Angajat.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

class CerereReparatie;

class Tehnician : public Angajat {
private:
    string specializare;
    std::vector<std::weak_ptr<CerereReparatie>> reparatiiEfectuate;

public:
    Tehnician();
    Tehnician(int, const string&, const string&, const string&);
    ~Tehnician() override;
    
    double getSalariu() const override;
    string getTip() const override;
    
    string getSpecializare() const;
    void adaugaReparatie(std::shared_ptr<CerereReparatie>);
    std::vector<std::shared_ptr<CerereReparatie>> getReparatii() const;
};
