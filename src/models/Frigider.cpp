#include "Frigider.h"
#include <iostream>

using namespace std;

Frigider::Frigider(const string& marca, const string& model, 
                   int an, double pret, bool congelator)
    : Electrocasnic("Frigider", marca, model, an, pret), 
      areCongelator(congelator) {}

bool Frigider::getAreCongelator() const {
    return areCongelator;
}

void Frigider::afiseazaDetalii() const {
    Electrocasnic::afiseazaDetalii();
    cout << "Are congelator: " << (areCongelator ? "Da" : "Nu") << "\n";
}

string Frigider::getDetaliiSpecifice() const {
    return string("Are congelator: ") + (areCongelator ? "Da" : "Nu");
}

