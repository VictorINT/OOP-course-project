#include "../../include/models/Televizor.h"
#include <sstream>

using namespace std;

Televizor::Televizor() : Electrocasnic(), diagonalaInch(0.0), esteSmart(false) {}

Televizor::Televizor(const string& marca, const string& model, int anFabricatie, double diagonalaInch, bool esteSmart) : Electrocasnic("Televizor", marca, model, anFabricatie), diagonalaInch(diagonalaInch), esteSmart(esteSmart) {}

Televizor::~Televizor() {}

string Televizor::getDetalii() const {
    ostringstream oss;
    oss << "Televizor " << marca << " " << model << " (" << anFabricatie << ")"
        << " | diagonala: " << diagonalaInch << " in"
        << " | smart: " << (esteSmart ? "da" : "nu");
    return oss.str();
}

double Televizor::getDiagonalaInch() const {
    return diagonalaInch;
}

bool Televizor::getEsteSmart() const {
    return esteSmart;
}
