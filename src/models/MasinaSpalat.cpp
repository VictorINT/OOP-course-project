#include "../../include/models/MasinaSpalat.h"

using namespace std;

MasinaSpalat::MasinaSpalat() : Electrocasnic(), capacitateKg(0), turatieStoarcere(0) {}

MasinaSpalat::MasinaSpalat(const string& marca, const string& model, int anFabricatie, int capacitateKg, int turatieStoarcere) : Electrocasnic("MasinaSpalat", marca, model, anFabricatie), capacitateKg(capacitateKg), turatieStoarcere(turatieStoarcere) {}

MasinaSpalat::~MasinaSpalat() {}

string MasinaSpalat::getDetalii() const {
    //! TODO: Implement details formatting
    return "";
}

int MasinaSpalat::getCapacitateKg() const {
    return capacitateKg;
}

int MasinaSpalat::getTuratieStoarcere() const {
    return turatieStoarcere;
}
