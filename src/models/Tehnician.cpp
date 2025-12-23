#include "../../include/models/Tehnician.h"
#include "../../include/models/CerereReparatie.h"

using namespace std;

Tehnician::Tehnician() : Angajat(), specializare("") {}

Tehnician::Tehnician(int id, const string& nume, const string& cnp, const string& specializare) : Angajat(id, nume, cnp), specializare(specializare) {}

Tehnician::~Tehnician() {}

double Tehnician::getSalariu() const {
    //! TODO: Implement salary calculation
    return 0.0;
}

string Tehnician::getTip() const {
    return "Tehnician";
}

string Tehnician::getSpecializare() const {
    return specializare;
}

void Tehnician::adaugaReparatie(CerereReparatie* reparatie) {
    reparatiiEfectuate.push_back(reparatie);
}

const vector<CerereReparatie*>& Tehnician::getReparatii() const {
    return reparatiiEfectuate;
}
