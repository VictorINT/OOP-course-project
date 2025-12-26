#ifndef MASINA_SPALAT_H
#define MASINA_SPALAT_H

#include "Electrocasnic.h"

using namespace std;

class MasinaSpalat : public Electrocasnic {
private:
    double capacitate;  // in kg
    
public:
    MasinaSpalat(const string&, const string&, int, double, double);
    
    double getCapacitate() const;
    void afiseazaDetalii() const override;
    string getDetaliiSpecifice() const override;
};

#endif

