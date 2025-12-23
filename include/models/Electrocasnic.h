#pragma once
#include <string>

using namespace std;

class Electrocasnic {
protected:
    string tip;
    string marca;
    string model;
    int anFabricatie;

public:
    Electrocasnic();
    Electrocasnic(const string&, const string&, const string&, int);
    virtual ~Electrocasnic();
    
    // Getters
    string getTip() const;
    string getMarca() const;
    string getModel() const;
    int getAnFabricatie() const;
    
    // Virtual methods
    virtual string getDetalii() const = 0;
};
