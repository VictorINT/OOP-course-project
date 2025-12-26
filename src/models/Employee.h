#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <memory>

using namespace std;

class Employee {
protected:
    int id;
    string nume;
    string prenume;
    string cnp;
    string dataAngajarii;
    string oras;
    
    static int nextId;
    
public:
    Employee(const string&, const string&, const string&, 
             const string&, const string&);
    virtual ~Employee() = default;
    
    // Getters
    int getId() const;
    string getNume() const;
    string getPrenume() const;
    string getCNP() const;
    string getDataAngajarii() const;
    string getOras() const;
    
    // Setters
    void setNume(const string&);
    void setPrenume(const string&);
    
    // Metode virtuale pure
    virtual double calculeazaSalariu() const = 0;
    virtual void afiseazaDetalii() const;
    virtual string getTipAngajat() const = 0;
    
protected:
    double calculeazaBonusFidelitate() const;
    double calculeazaPrimaTransport() const;
    int calculeazaAniLucrati() const;
};

#endif

