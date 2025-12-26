#include "MasinaSpalat.h"
#include <iostream>

using namespace std;

MasinaSpalat::MasinaSpalat(const string& marca, const string& model, 
                           int an, double pret, double cap)
    : Electrocasnic("MasinaSpalat", marca, model, an, pret), 
      capacitate(cap) {}

double MasinaSpalat::getCapacitate() const {
    return capacitate;
}

void MasinaSpalat::afiseazaDetalii() const {
    Electrocasnic::afiseazaDetalii();
    cout << "Capacitate: " << capacitate << " kg\n";
}

string MasinaSpalat::getDetaliiSpecifice() const {
    return "Capacitate: " + to_string(capacitate) + " kg";
}

