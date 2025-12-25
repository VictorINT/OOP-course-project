#include "../../include/models/Tehnician.h"
#include "../../include/models/CerereReparatie.h"
#include <memory>

using namespace std;

Tehnician::Tehnician() : Angajat(), specializare("") {}

Tehnician::Tehnician(int id, const string& nume, const string& cnp, const string& specializare) : Angajat(id, nume, cnp), specializare(specializare) {}

Tehnician::~Tehnician() {}

double Tehnician::getSalariu() const {
    const double salariuBaza = 4000.0;
    double bonusReparatii = 0.0;

    for (auto& w : reparatiiEfectuate) {
        auto cerere = w.lock();
        if (cerere) {
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

void Tehnician::adaugaReparatie(std::shared_ptr<CerereReparatie> reparatie) {
    reparatiiEfectuate.push_back(reparatie);
}

std::vector<std::shared_ptr<CerereReparatie>> Tehnician::getReparatii() const {
    std::vector<std::shared_ptr<CerereReparatie>> v;
    for (auto& w : reparatiiEfectuate) {
        auto s = w.lock();
        if (s) v.push_back(s);
    }
    return v;
}
