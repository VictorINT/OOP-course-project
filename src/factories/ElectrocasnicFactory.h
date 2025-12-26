#ifndef ELECTROCASNIC_FACTORY_H
#define ELECTROCASNIC_FACTORY_H

#include <memory>
#include <string>
#include "../models/Electrocasnic.h"

using namespace std;

class ElectrocasnicFactory {
public:
    // Creeaza un electrocasnic pe baza tipului specificat
    static shared_ptr<Electrocasnic> creeazaElectrocasnic(
        const string&,  // tip: "Frigider", "TV", "MasinaSpalat"
        const string&,  // marca
        const string&,  // model
        int,                 // an fabricatie
        double,              // pret catalog
        const string&   // detalii specifice (format tip-dependent)
    );
    
private:
    static shared_ptr<Electrocasnic> creeazaFrigider(
        const string&, const string&, int, double, const string&);
    static shared_ptr<Electrocasnic> creeazaTV(
        const string&, const string&, int, double, const string&);
    static shared_ptr<Electrocasnic> creeazaMasinaSpalat(
        const string&, const string&, int, double, const string&);
};

#endif

