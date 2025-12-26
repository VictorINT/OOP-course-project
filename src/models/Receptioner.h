#ifndef RECEPTIONER_H
#define RECEPTIONER_H

#include "Employee.h"
#include <vector>

using namespace std;

class Receptioner : public Employee {
private:
    vector<int> idCereriInregistrate;
    
public:
    Receptioner(const string&, const string&, const string&, 
                const string&, const string&);
    
    double calculeazaSalariu() const override;
    string getTipAngajat() const override;
    void afiseazaDetalii() const override;
    
    // Metode specifice
    void adaugaCerereInregistrata(int);
    const vector<int>& getCereriInregistrate() const;
};

#endif

