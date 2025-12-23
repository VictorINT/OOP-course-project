#pragma once
#include <string>

using namespace std;

class Menu {
public:
    Menu();
    
    void afiseazaMeniuPrincipal();
    void ruleaza();
    
private:
    void afiseazaAngajati();
    void adaugaAngajat();
    void afiseazaCereri();
    void adaugaCerere();
    void ruleazaSimulare();
    void genereazaRapoarte();
    void incarcaDate();
    
    void clearScreen();
    void pausaConsola();
    int citesteOptiune(int min, int max);
};
