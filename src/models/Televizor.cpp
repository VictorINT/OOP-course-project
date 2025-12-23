#include "../../include/models/Televizor.h"

using namespace std;

Televizor::Televizor() : Electrocasnic(), diagonalaInch(0.0), esteSmart(false) {}

Televizor::Televizor(const string& marca, const string& model, int anFabricatie, double diagonalaInch, bool esteSmart) : Electrocasnic("Televizor", marca, model, anFabricatie), diagonalaInch(diagonalaInch), esteSmart(esteSmart) {}

Televizor::~Televizor() {}

string Televizor::getDetalii() const {
    //! TODO: Implement details formatting
    return "";
}

double Televizor::getDiagonalaInch() const {
    return diagonalaInch;
}

bool Televizor::getEsteSmart() const {
    return esteSmart;
}
