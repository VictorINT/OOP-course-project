#include "../../include/models/Receptioner.h"
#include "../../include/models/CerereReparatie.h"

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

void Receptioner::adaugaCerere(CerereReparatie* cerere) {
    cereriGestionate.push_back(cerere);
}

const vector<CerereReparatie*>& Receptioner::getCereri() const {
    return cereriGestionate;
}
