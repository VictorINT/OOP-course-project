#include "Employee.h"
#include "../utils/CNPValidator.h"
#include "../exceptions/ServiceException.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

using namespace std;

int Employee::nextId = 1;

Employee::Employee(const string& n, const string& p, 
                   const string& c, const string& data, 
                   const string& o) 
    : id(nextId++), nume(n), prenume(p), cnp(c), 
      dataAngajarii(data), oras(o) {
    
    // Valideaza nume si prenume
    if (nume.length() < 3 || nume.length() > 30) {
        throw InvalidDataException("Nume invalid: lungime trebuie sa fie intre 3 si 30 caractere");
    }
    if (prenume.length() < 3 || prenume.length() > 30) {
        throw InvalidDataException("Prenume invalid: lungime trebuie sa fie intre 3 si 30 caractere");
    }
    
    // Valideaza CNP
    if (!CNPValidator::valideaza(cnp)) {
        throw InvalidCNPException("CNP invalid: " + cnp);
    }
}

int Employee::getId() const { return id; }
string Employee::getNume() const { return nume; }
string Employee::getPrenume() const { return prenume; }
string Employee::getCNP() const { return cnp; }
string Employee::getDataAngajarii() const { return dataAngajarii; }
string Employee::getOras() const { return oras; }

void Employee::setNume(const string& n) {
    if (n.length() < 3 || n.length() > 30) {
        throw InvalidDataException("Nume invalid: lungime trebuie sa fie intre 3 si 30 caractere");
    }
    nume = n;
}

void Employee::setPrenume(const string& p) {
    if (p.length() < 3 || p.length() > 30) {
        throw InvalidDataException("Prenume invalid: lungime trebuie sa fie intre 3 si 30 caractere");
    }
    prenume = p;
}

void Employee::afiseazaDetalii() const {
    cout << "ID: " << id << "\n";
    cout << "Nume: " << nume << " " << prenume << "\n";
    cout << "CNP: " << cnp << "\n";
    cout << "Data angajarii: " << dataAngajarii << "\n";
    cout << "Oras: " << oras << "\n";
    cout << "Tip: " << getTipAngajat() << "\n";
}

double Employee::calculeazaBonusFidelitate() const {
    int aniLucrati = calculeazaAniLucrati();
    int perioade = aniLucrati / 3;
    return 4000.0 * 0.05 * perioade;
}

double Employee::calculeazaPrimaTransport() const {
    if (oras != "Bucuresti") {
        return 400.0;
    }
    return 0.0;
}

int Employee::calculeazaAniLucrati() const {
    // Extrage anul din data angajarii (format: YYYY-MM-DD)
    int anAngajare = stoi(dataAngajarii.substr(0, 4));
    
    // Obtine anul curent
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm* now_tm = localtime(&now_time);
    int anCurent = now_tm->tm_year + 1900;
    
    return anCurent - anAngajare;
}

