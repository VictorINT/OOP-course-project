#ifndef FRIGIDER_H
#define FRIGIDER_H

#include "Electrocasnic.h"

using namespace std;

class Frigider : public Electrocasnic {
private:
    bool areCongelator;
    
public:
    Frigider(const string&, const string&, int, double, bool);
    
    bool getAreCongelator() const;
    void afiseazaDetalii() const override;
    string getDetaliiSpecifice() const override;
};

#endif

