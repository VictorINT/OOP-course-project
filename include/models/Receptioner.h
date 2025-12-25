#pragma once
#include "Angajat.h"
#include <vector>
#include <memory>

using namespace std;

class CerereReparatie;

class Receptioner : public Angajat {
private:
    std::vector<std::weak_ptr<CerereReparatie>> cereriGestionate;

public:
    Receptioner();
    Receptioner(int, const string&, const string&);
    ~Receptioner() override;
    
    double getSalariu() const override;
    string getTip() const override;
    
    void adaugaCerere(std::shared_ptr<CerereReparatie>);
    std::vector<std::shared_ptr<CerereReparatie>> getCereri() const;
};
