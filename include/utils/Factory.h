#pragma once
#include <string>
#include <memory>
#include "../models/Angajat.h"
#include "../models/Electrocasnic.h"

using namespace std;

class Factory {
public:
    // Factory pentru crearea de angajati
    static std::shared_ptr<Angajat> creeazaAngajat(const string& tip, int id, 
                                   const string& nume, 
                                   const string& cnp,
                                   const string& parametruExtra = "");
    
    // Factory pentru crearea de electrocasnice
    static std::shared_ptr<Electrocasnic> creeazaElectrocasnic(const string& tip,
                                               const string& marca,
                                               const string& model,
                                               int anFabricatie,
                                               const string& parametri);
};
