#include "Receptioner.h"
#include <iostream>

using namespace std;

Receptioner::Receptioner(const string& n, const string& p, 
                         const string& c, const string& data, 
                         const string& o)
    : Employee(n, p, c, data, o) {}

double Receptioner::calculeazaSalariu() const {
    double salariu = 4000.0;  // Salariu de baza
    salariu += calculeazaBonusFidelitate();  // Bonus fidelitate
    salariu += calculeazaPrimaTransport();  // Prima transport
    return salariu;
}

string Receptioner::getTipAngajat() const {
    return "Receptioner";
}

void Receptioner::afiseazaDetalii() const {
    Employee::afiseazaDetalii();
    cout << "Numar cereri inregistrate: " << idCereriInregistrate.size() << "\n";
}

void Receptioner::adaugaCerereInregistrata(int idCerere) {
    idCereriInregistrate.push_back(idCerere);
}

const vector<int>& Receptioner::getCereriInregistrate() const {
    return idCereriInregistrate;
}

