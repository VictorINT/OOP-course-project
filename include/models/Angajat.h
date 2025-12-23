#pragma once

#include <string>

using namespace std;

class Angajat {
protected:
    int id;
    string nume;
    string cnp;

public:
    Angajat();
    Angajat(int, const string&, const string&);
    virtual ~Angajat();
    
    // Getters
    int getId() const;
    string getNume() const;
    string getCnp() const;
    
    // Virtual methods
    virtual double getSalariu() const = 0;
    virtual string getTip() const = 0;
};
