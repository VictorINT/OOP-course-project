#include "TV.h"
#include <iostream>

using namespace std;

TV::TV(const string& marca, const string& model, 
       int an, double pret, double diag, const string& unitate)
    : Electrocasnic("TV", marca, model, an, pret), 
      diagonala(diag), unitateMasura(unitate) {}

double TV::getDiagonala() const {
    return diagonala;
}

string TV::getUnitateMasura() const {
    return unitateMasura;
}

void TV::afiseazaDetalii() const {
    Electrocasnic::afiseazaDetalii();
    cout << "Diagonala: " << diagonala << " " << unitateMasura << "\n";
}

string TV::getDetaliiSpecifice() const {
    return "Diagonala: " + to_string(diagonala) + " " + unitateMasura;
}

