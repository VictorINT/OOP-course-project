#ifndef RAPORT_GENERATOR_H
#define RAPORT_GENERATOR_H

#include <string>
#include <vector>
#include <memory>
#include "../models/Employee.h"
#include "../models/Tehnician.h"
#include "../models/CerereReparatie.h"

using namespace std;

class RaportGenerator {
public:
    // Genereaza raport cu top 3 salarii
    static void genereazaTopSalarii(
        const vector<shared_ptr<Employee>>&, 
        const string&
    );
    
    // Genereaza raport cu tehnicianul cu cea mai lunga reparatie
    static void genereazaRaportTehnician(
        shared_ptr<Tehnician>, 
        const string&
    );
    
    // Genereaza raport cu cereri in asteptare
    static void genereazaCereriAsteptare(
        const map<string, vector<shared_ptr<CerereReparatie>>>&,
        const string&
    );
    
    // Genereaza raport simulare
    static void genereazaRaportSimulare(
        const vector<string>&,
        const string&
    );
};

#endif

