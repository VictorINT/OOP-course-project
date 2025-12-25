#include "../../include/models/Receptioner.h"
#include "../../include/models/CerereReparatie.h"
#include <memory>

using namespace std;

Receptioner::Receptioner() : Angajat() {}

Receptioner::Receptioner(int id, const string& nume, const string& cnp) : Angajat(id, nume, cnp) {}

Receptioner::~Receptioner() {}

double Receptioner::getSalariu() const {
    const double salariuBaza = 4000.0;
    return salariuBaza;
}

string Receptioner::getTip() const {
    return "Receptioner";
}

void Receptioner::adaugaCerere(std::shared_ptr<CerereReparatie> cerere) {
    cereriGestionate.push_back(cerere);
}

std::vector<std::shared_ptr<CerereReparatie>> Receptioner::getCereri() const {
    std::vector<std::shared_ptr<CerereReparatie>> v;
    for (auto& w : cereriGestionate) {
        auto s = w.lock();
        if (s) v.push_back(s);
    }
    return v;
}
