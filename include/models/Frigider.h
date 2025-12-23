#pragma once
#include "Electrocasnic.h"

using namespace std;

class Frigider : public Electrocasnic {
private:
    bool areCongelator;
    int capacitateLitri;

public:
    Frigider();
    Frigider(const string&, const string&, int, bool, int);
    ~Frigider() override;
    
    string getDetalii() const override;
    bool getAreCongelator() const;
    int getCapacitateLitri() const;
};
