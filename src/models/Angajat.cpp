#include "../../include/models/Angajat.h"

using namespace std;

Angajat::Angajat() : id(0), nume(""), cnp("") {}

Angajat::Angajat(int id, const string& nume, const string& cnp) : id(id), nume(nume), cnp(cnp) {}

Angajat::~Angajat() {}

int Angajat::getId() const {
    return id;
}

string Angajat::getNume() const {
    return nume;
}

string Angajat::getCnp() const {
    return cnp;
}
