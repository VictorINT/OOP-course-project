#ifndef ELECTROCASNIC_H
#define ELECTROCASNIC_H

#include <string>

using namespace std;

class Electrocasnic {
protected:
    string tip;
    string marca;
    string model;
    int anFabricatie;
    double pretCatalog;
    
public:
    Electrocasnic(const string&, const string&, 
                  const string&, int, double);
    virtual ~Electrocasnic() = default;
    
    // Getters
    string getTip() const;
    string getMarca() const;
    string getModel() const;
    int getAnFabricatie() const;
    double getPretCatalog() const;
    
    // Metode virtuale
    virtual void afiseazaDetalii() const;
    virtual string getDetaliiSpecifice() const = 0;
    
    int calculeazaVechime() const;
};

#endif

