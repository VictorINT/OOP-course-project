#include "Tehnician.h"
#include "CerereReparatie.h"
#include <iostream>
#include <algorithm>

using namespace std;

Tehnician::Tehnician(const string& n, const string& p, 
                     const string& c, const string& data, 
                     const string& o)
    : Employee(n, p, c, data, o), durataTotala(0.0), 
      valoareReparatiiEfectuate(0.0) {}

double Tehnician::calculeazaSalariu() const {
    double salariu = 4000.0;  // Salariu de baza
    salariu += calculeazaBonusFidelitate();  // Bonus fidelitate
    salariu += calculeazaPrimaTransport();  // Prima transport
    salariu += valoareReparatiiEfectuate * 0.02;  // Bonus reparatii (2%)
    return salariu;
}

string Tehnician::getTipAngajat() const {
    return "Tehnician";
}

void Tehnician::afiseazaDetalii() const {
    Employee::afiseazaDetalii();
    cout << "Cereri active: " << cereriActive.size() << "\n";
    cout << "Durata totala: " << durataTotala << "\n";
    cout << "Valoare reparatii efectuate: " << valoareReparatiiEfectuate << " RON\n";
    cout << "Specializari:\n";
    for (const auto& [tip, marci] : specializari) {
        cout << "  " << tip << ": ";
        for (size_t i = 0; i < marci.size(); i++) {
            cout << marci[i];
            if (i < marci.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
}

void Tehnician::adaugaSpecializare(const string& tip, 
                                    const string& marca) {
    specializari[tip].push_back(marca);
}

bool Tehnician::poateRepara(const string& tip, 
                             const string& marca) const {
    auto it = specializari.find(tip);
    if (it == specializari.end()) return false;
    
    const auto& marci = it->second;
    return find(marci.begin(), marci.end(), marca) != marci.end();
}

bool Tehnician::areLoc() const {
    return cereriActive.size() < 3;
}

void Tehnician::adaugaCerereActiva(shared_ptr<CerereReparatie> cerere) {
    cereriActive.push_back(cerere);
}

void Tehnician::eliminaCerereActiva(shared_ptr<CerereReparatie> cerere) {
    auto it = find(cereriActive.begin(), cereriActive.end(), cerere);
    if (it != cereriActive.end()) {
        cereriActive.erase(it);
    }
}

void Tehnician::adaugaValoareReparatie(double valoare) {
    valoareReparatiiEfectuate += valoare;
}

double Tehnician::getDurataTotala() const {
    return durataTotala;
}

const vector<shared_ptr<CerereReparatie>>& 
Tehnician::getCereriActive() const {
    return cereriActive;
}

const map<string, vector<string>>& 
Tehnician::getSpecializari() const {
    return specializari;
}

