#ifndef SUPERVIZOR_H
#define SUPERVIZOR_H

#include "Employee.h"

using namespace std;

class Supervizor : public Employee {
public:
    Supervizor(const string&, const string&, const string&, 
               const string&, const string&);
    
    double calculeazaSalariu() const override;
    string getTipAngajat() const override;
};

#endif

