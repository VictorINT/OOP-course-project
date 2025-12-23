#include "../../include/models/Supervizor.h"

using namespace std;

Supervizor::Supervizor() : Angajat(), sporConducere(0.0) {}

Supervizor::Supervizor(int id, const string& nume, const string& cnp, double sporConducere) : Angajat(id, nume, cnp), sporConducere(sporConducere) {}

Supervizor::~Supervizor() {}

double Supervizor::getSalariu() const {
    const double salariuBaza = 4000.0;
    return salariuBaza + salariuBaza * sporConducere;
}

string Supervizor::getTip() const {
    return "Supervizor";
}

double Supervizor::getSporConducere() const {
    return sporConducere;
}

void Supervizor::setSporConducere(double spor) {
    sporConducere = spor;
}
