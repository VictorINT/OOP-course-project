#include "Electrocasnic.h"
#include <iostream>
#include <chrono>

using namespace std;

Electrocasnic::Electrocasnic(const string& t, const string& m, 
                             const string& mod, int an, double pret)
    : tip(t), marca(m), model(mod), anFabricatie(an), pretCatalog(pret) {}

string Electrocasnic::getTip() const { return tip; }
string Electrocasnic::getMarca() const { return marca; }
string Electrocasnic::getModel() const { return model; }
int Electrocasnic::getAnFabricatie() const { return anFabricatie; }
double Electrocasnic::getPretCatalog() const { return pretCatalog; }

void Electrocasnic::afiseazaDetalii() const {
    cout << "Tip: " << tip << "\n";
    cout << "Marca: " << marca << "\n";
    cout << "Model: " << model << "\n";
    cout << "An fabricatie: " << anFabricatie << "\n";
    cout << "Pret catalog: " << pretCatalog << " RON\n";
}

int Electrocasnic::calculeazaVechime() const {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm* now_tm = localtime(&now_time);
    int anCurent = now_tm->tm_year + 1900;
    
    return anCurent - anFabricatie;
}

