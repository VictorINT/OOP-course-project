#include "RaportGenerator.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

void RaportGenerator::genereazaTopSalarii(
    const vector<shared_ptr<Employee>>& topAngajati,
    const string& numeFisier) {
    
    ofstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide fisierul " << numeFisier << "\n";
        return;
    }
    
    // Header CSV
    fisier << "Pozitie,Nume,Prenume,Tip,Salariu\n";
    
    int pozitie = 1;
    for (const auto& ang : topAngajati) {
        fisier << pozitie << ","
               << ang->getNume() << ","
               << ang->getPrenume() << ","
               << ang->getTipAngajat() << ","
               << fixed << setprecision(2) << ang->calculeazaSalariu() << "\n";
        pozitie++;
    }
    
    fisier.close();
    cout << "Raport generat: " << numeFisier << "\n";
}

void RaportGenerator::genereazaRaportTehnician(
    shared_ptr<Tehnician> tehnician,
    const string& numeFisier) {
    
    ofstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide fisierul " << numeFisier << "\n";
        return;
    }
    
    if (!tehnician) {
        fisier << "Nu exista date despre tehnicieni cu reparatii finalizate.\n";
        fisier.close();
        return;
    }
    
    // Header CSV
    fisier << "Camp,Valoare\n";
    fisier << "ID," << tehnician->getId() << "\n";
    fisier << "Nume," << tehnician->getNume() << "\n";
    fisier << "Prenume," << tehnician->getPrenume() << "\n";
    fisier << "CNP," << tehnician->getCNP() << "\n";
    fisier << "Data angajarii," << tehnician->getDataAngajarii() << "\n";
    fisier << "Oras," << tehnician->getOras() << "\n";
    fisier << "Salariu," << fixed << setprecision(2) 
           << tehnician->calculeazaSalariu() << "\n";
    
    fisier.close();
    cout << "Raport generat: " << numeFisier << "\n";
}

void RaportGenerator::genereazaCereriAsteptare(
    const map<string, vector<shared_ptr<CerereReparatie>>>& grupate,
    const string& numeFisier) {
    
    ofstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide fisierul " << numeFisier << "\n";
        return;
    }
    
    if (grupate.empty()) {
        fisier << "Nu exista cereri in asteptare.\n";
        fisier.close();
        return;
    }
    
    // Header CSV
    fisier << "Tip,Marca,Model,Numar cereri\n";
    
    for (const auto& [cheie, cereri] : grupate) {
        // Parseaza cheia (format: tip:marca:model)
        size_t pos1 = cheie.find(':');
        size_t pos2 = cheie.find(':', pos1 + 1);
        
        string tip = cheie.substr(0, pos1);
        string marca = cheie.substr(pos1 + 1, pos2 - pos1 - 1);
        string model = cheie.substr(pos2 + 1);
        
        fisier << tip << "," << marca << "," << model << "," << cereri.size() << "\n";
    }
    
    fisier.close();
    cout << "Raport generat: " << numeFisier << "\n";
}

void RaportGenerator::genereazaRaportSimulare(
    const vector<string>& istoric,
    const string& numeFisier) {
    
    ofstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide fisierul " << numeFisier << "\n";
        return;
    }
    
    fisier << "================================================================================\n";
    fisier << "                    Raport Simulare - FixItNow Service\n";
    fisier << "================================================================================\n\n";
    
    // Data generare
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    fisier << "Data generare: " << ctime(&now_time);
    fisier << "--------------------------------------------------------------------------------\n\n";
    
    if (istoric.empty()) {
        fisier << "Nu exista evenimente inregistrate in simulare.\n";
    } else {
        // Calculeaza statistici
        int nrAsignari = 0;
        int nrFinalizari = 0;
        
        for (const auto& mesaj : istoric) {
            if (mesaj.find("[Asignare]") != string::npos) nrAsignari++;
            if (mesaj.find("[Finalizat]") != string::npos) nrFinalizari++;
        }
        
        // Statistici sumare
        fisier << "STATISTICI GENERALE:\n";
        fisier << "--------------------\n";
        fisier << "Total evenimente:     " << istoric.size() << "\n";
        fisier << "Cereri asignate:      " << nrAsignari << "\n";
        fisier << "Reparatii finalizate: " << nrFinalizari << "\n";
        fisier << "\n";
        
        // Separa asignarile de finalizari
        fisier << "================================================================================\n";
        fisier << "ASIGNARI DE CERERI\n";
        fisier << "================================================================================\n\n";
        
        int nrAsignare = 1;
        for (const auto& mesaj : istoric) {
            if (mesaj.find("[Asignare]") != string::npos) {
                fisier << nrAsignare << ". " << mesaj << "\n\n";
                nrAsignare++;
            }
        }
        
        fisier << "================================================================================\n";
        fisier << "REPARATII FINALIZATE\n";
        fisier << "================================================================================\n\n";
        
        int nrFinalizare = 1;
        for (const auto& mesaj : istoric) {
            if (mesaj.find("[Finalizat]") != string::npos) {
                fisier << nrFinalizare << ". " << mesaj << "\n";
                nrFinalizare++;
            }
        }
        
        fisier << "\n================================================================================\n";
        fisier << "CRONOLOGIE COMPLETA (ordine temporala)\n";
        fisier << "================================================================================\n\n";
        
        int evenimentNr = 1;
        for (const auto& mesaj : istoric) {
            fisier << evenimentNr << ". " << mesaj << "\n";
            evenimentNr++;
        }
        
        fisier << "\n================================================================================\n";
        fisier << "REZUMAT:\n";
        fisier << "  - Total cereri procesate:  " << nrAsignari << "\n";
        fisier << "  - Reparatii finalizate:    " << nrFinalizari << "\n";
        fisier << "  - Rata finalizare:         " 
               << (nrAsignari > 0 ? (nrFinalizari * 100 / nrAsignari) : 0) << "%\n";
        fisier << "================================================================================\n";
    }
    
    fisier.close();
    cout << "Raport simulare generat: " << numeFisier << "\n";
}

