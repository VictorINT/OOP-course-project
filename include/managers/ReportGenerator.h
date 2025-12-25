#pragma once
#include <string>
#include <vector>

using namespace std;

class ReportGenerator {
public:
    ReportGenerator();
    
    void genereazaRaportAngajati(const string&);
    void genereazaRaportCereri(const string&);
    void genereazaRaportFinanciar(const string&);
    void genereazaRaportPerformanta(const string&);
    void genereazaRaportEvenimente(const string&);
    
private:
    string escapeCSV(const string&);
    void asiguraDirector(const string&);
};
