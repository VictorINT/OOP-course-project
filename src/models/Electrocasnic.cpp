#include "../../include/models/Electrocasnic.h"

using namespace std;

Electrocasnic::Electrocasnic() : tip(""), marca(""), model(""), anFabricatie(0) {}

Electrocasnic::Electrocasnic(const string& tip, const string& marca, const string& model, int anFabricatie) : tip(tip), marca(marca), model(model), anFabricatie(anFabricatie) {}

Electrocasnic::~Electrocasnic() {}

string Electrocasnic::getTip() const {
    return tip;
}

string Electrocasnic::getMarca() const {
    return marca;
}

string Electrocasnic::getModel() const {
    return model;
}

int Electrocasnic::getAnFabricatie() const {
    return anFabricatie;
}
