#include "../../include/models/MasinaSpalat.h"
#include <sstream>

using namespace std;

MasinaSpalat::MasinaSpalat() : Electrocasnic(), capacitateKg(0), turatieStoarcere(0) {}

MasinaSpalat::MasinaSpalat(const string& marca, const string& model, int anFabricatie, int capacitateKg, int turatieStoarcere) : Electrocasnic("MasinaSpalat", marca, model, anFabricatie), capacitateKg(capacitateKg), turatieStoarcere(turatieStoarcere) {}

MasinaSpalat::~MasinaSpalat() {}

string MasinaSpalat::getDetalii() const {
    ostringstream oss;
    oss << "MasinaSpalat " << marca << " " << model << " (" << anFabricatie << ")"
        << " | capacitate: " << capacitateKg << " kg"
        << " | turatie: " << turatieStoarcere << " rpm";
    return oss.str();
}

int MasinaSpalat::getCapacitateKg() const {
    return capacitateKg;
}

int MasinaSpalat::getTuratieStoarcere() const {
    return turatieStoarcere;
}
