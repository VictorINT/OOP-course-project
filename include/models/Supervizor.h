#pragma once
#include "Angajat.h"

using namespace std;

class Supervizor : public Angajat {
private:
    double sporConducere;

public:
    Supervizor();
    Supervizor(int, const string&, const string&, double);
    ~Supervizor() override;
    
    double getSalariu() const override;
    string getTip() const override;
    
    double getSporConducere() const;
    void setSporConducere(double);
};
