#pragma once
#include "Electrocasnic.h"

using namespace std;

class Televizor : public Electrocasnic {
private:
    double diagonalaInch;
    bool esteSmart;

public:
    Televizor();
    Televizor(const string&, const string&, int, double, bool);
    ~Televizor() override;
    
    string getDetalii() const override;
    double getDiagonalaInch() const;
    bool getEsteSmart() const;
};
