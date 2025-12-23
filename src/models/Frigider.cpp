#include "../../include/models/Frigider.h"
#include <sstream>

using namespace std;

Frigider::Frigider() : Electrocasnic(), areCongelator(false), capacitateLitri(0) {}

Frigider::Frigider(const string& marca, const string& model, int anFabricatie, bool areCongelator, int capacitateLitri) : Electrocasnic("Frigider", marca, model, anFabricatie), areCongelator(areCongelator), capacitateLitri(capacitateLitri) {}

Frigider::~Frigider() {}

string Frigider::getDetalii() const {
    ostringstream oss;
    oss << "Frigider " << marca << " " << model << " (" << anFabricatie << ")"
        << " | congelator: " << (areCongelator ? "da" : "nu")
        << " | capacitate: " << capacitateLitri << " L";
    return oss.str();
}

bool Frigider::getAreCongelator() const {
    return areCongelator;
}

int Frigider::getCapacitateLitri() const {
    return capacitateLitri;
}
