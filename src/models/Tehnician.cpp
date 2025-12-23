#include "../../include/models/Tehnician.h"
#include "../../include/models/CerereReparatie.h"

using namespace std;

Tehnician::Tehnician() : Angajat(), specializare("") {}

Tehnician::Tehnician(int id, const string& nume, const string& cnp, const string& specializare) : Angajat(id, nume, cnp), specializare(specializare) {}

Tehnician::~Tehnician() {}

double Tehnician::getSalariu() const {
    const double salariuBaza = 4000.0;
    double bonusReparatii = 0.0;

    for (auto cerere : reparatiiEfectuate) {
        if (cerere != nullptr) {
            bonusReparatii += 0.02 * cerere->getCostTotal();
        }
    }

    return salariuBaza + bonusReparatii;
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
