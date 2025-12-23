#pragma once
#include "Electrocasnic.h"

using namespace std;

class MasinaSpalat : public Electrocasnic {
private:
    int capacitateKg;
    int turatieStoarcere;

public:
    MasinaSpalat();
    MasinaSpalat(const string&, const string&, int, int, int);
    ~MasinaSpalat() override;
    
    string getDetalii() const override;
    int getCapacitateKg() const;
    int getTuratieStoarcere() const;
};
