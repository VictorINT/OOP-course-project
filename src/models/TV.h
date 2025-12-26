#ifndef TV_H
#define TV_H

#include "Electrocasnic.h"

using namespace std;

class TV : public Electrocasnic {
private:
    double diagonala;
    string unitateMasura;  // "cm" sau "inch"
    
public:
    TV(const string&, const string&, int, double, 
       double, const string&);
    
    double getDiagonala() const;
    string getUnitateMasura() const;
    void afiseazaDetalii() const override;
    string getDetaliiSpecifice() const override;
};

#endif

