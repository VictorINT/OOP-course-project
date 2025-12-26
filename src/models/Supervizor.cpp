#include "Supervizor.h"

using namespace std;

Supervizor::Supervizor(const string& n, const string& p, 
                       const string& c, const string& data, 
                       const string& o)
    : Employee(n, p, c, data, o) {}

double Supervizor::calculeazaSalariu() const {
    double salariu = 4000.0;  // Salariu de baza
    salariu += calculeazaBonusFidelitate();  // Bonus fidelitate
    salariu += calculeazaPrimaTransport();  // Prima transport
    salariu += 4000.0 * 0.20;  // Spor de conducere (20%)
    return salariu;
}

string Supervizor::getTipAngajat() const {
    return "Supervizor";
}

