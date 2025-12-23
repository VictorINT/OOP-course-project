#include "../../include/views/Menu.h"
#include "../../include/managers/ServiceManager.h"
#include "../../include/managers/Simulator.h"
#include "../../include/managers/ReportGenerator.h"
#include "../../include/utils/Factory.h"
#include "../../include/models/Receptioner.h"
#include "../../include/models/Tehnician.h"
#include "../../include/models/Supervizor.h"
#include <iostream>
#include <limits>

using namespace std;

Menu::Menu() {}

void Menu::afiseazaMeniuPrincipal() {
    cout << "\n========== FixItNow - Service Electrocasnice ==========\n";
    cout << "1. Afiseaza angajati\n";
    cout << "2. Adauga angajat\n";
    cout << "3. Afiseaza cereri reparatie\n";
    cout << "4. Adauga cerere reparatie\n";
    cout << "5. Ruleaza simulare\n";
    cout << "6. Genereaza rapoarte\n";
    cout << "7. Incarca date din fisiere\n";
    cout << "0. Iesire\n";
    cout << "======================================================\n";
    cout << "Optiune: ";
}

void Menu::ruleaza() {
    int optiune;
    do {
        afiseazaMeniuPrincipal();
        optiune = citesteOptiune(0, 7);
        
        switch(optiune) {
            case 1:
                afiseazaAngajati();
                break;
            case 2:
                adaugaAngajat();
                break;
            case 3:
                afiseazaCereri();
                break;
            case 4:
                adaugaCerere();
                break;
            case 5:
                ruleazaSimulare();
                break;
            case 6:
                genereazaRapoarte();
                break;
            case 7:
                incarcaDate();
                break;
            case 0:
                cout << "La revedere!\n";
                break;
        }
    } while(optiune != 0);
}

void Menu::afiseazaAngajati() {
    clearScreen();
    const auto& angajati = ServiceManager::getInstance()->getAngajati();
    if (angajati.empty()) {
        cout << "Nu exista angajati inregistrati." << '\n';
    } else {
        cout << "\n-- Lista Angajati --\n";
        for (auto angajat : angajati) {
            if (angajat == nullptr) continue;
            cout << "ID: " << angajat->getId()
                 << ", Tip: " << angajat->getTip()
                 << ", Nume: " << angajat->getNume()
                 << ", CNP: " << angajat->getCnp()
                 << ", Salariu: " << angajat->getSalariu() << '\n';
        }
    }
    pausaConsola();
}

void Menu::adaugaAngajat() {
    clearScreen();
    cout << "\n-- Adauga Angajat --\n";
    cout << "Tip (1-Receptioner, 2-Tehnician, 3-Supervizor): ";
    int tipOpt = citesteOptiune(1, 3);

    cout << "ID: ";
    int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nume: ";
    string nume; getline(cin, nume);
    cout << "CNP: ";
    string cnp; getline(cin, cnp);

    Angajat* angajat = nullptr;
    if (tipOpt == 1) {
        angajat = new Receptioner(id, nume, cnp);
    } else if (tipOpt == 2) {
        cout << "Specializare: ";
        string spec; getline(cin, spec);
        angajat = new Tehnician(id, nume, cnp, spec);
    } else {
        cout << "Spor conducere (0.0 - 1.0): ";
        double spor; cin >> spor; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        angajat = new Supervizor(id, nume, cnp, spor);
    }

    if (angajat != nullptr) {
        ServiceManager::getInstance()->adaugaAngajat(angajat);
        cout << "Angajat adaugat cu succes." << '\n';
    }
    pausaConsola();
}

void Menu::afiseazaCereri() {
    clearScreen();
    const auto& cereri = ServiceManager::getInstance()->getCereri();
    if (cereri.empty()) {
        cout << "Nu exista cereri." << '\n';
    } else {
        cout << "\n-- Lista Cereri --\n";
        for (auto cerere : cereri) {
            if (cerere == nullptr) continue;
            auto aparat = cerere->getAparat();
            cout << "ID: " << cerere->getId()
                 << ", Aparat: " << (aparat ? aparat->getTip() : "-")
                 << " " << (aparat ? aparat->getMarca() : "")
                 << " " << (aparat ? aparat->getModel() : "")
                 << ", Status: " << (int)cerere->getStatus()
                 << ", Cost total: " << cerere->getCostTotal() << '\n';
        }
    }
    pausaConsola();
}

void Menu::adaugaCerere() {
    clearScreen();
    cout << "\n-- Adauga Cerere Reparatie --\n";
    cout << "ID cerere: ";
    int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Tip aparat (frg/ts/masina): ";
    string tip; getline(cin, tip);
    cout << "Marca: ";
    string marca; getline(cin, marca);
    cout << "Model: ";
    string model; getline(cin, model);
    cout << "An fabricatie: ";
    int an; cin >> an; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Parametri extra (separati prin ';'): ";
    string param; getline(cin, param);

    Electrocasnic* aparat = Factory::creeazaElectrocasnic(tip, marca, model, an, param);
    if (aparat != nullptr) {
        ServiceManager::getInstance()->adaugaElectrocasnic(aparat);
    }

    cout << "Descriere defect: ";
    string descriere; getline(cin, descriere);

    CerereReparatie* cerere = new CerereReparatie(id, aparat, descriere);
    ServiceManager::getInstance()->adaugaCerere(cerere);
    cout << "Cerere adaugata." << '\n';
    pausaConsola();
}

void Menu::ruleazaSimulare() {
    clearScreen();
    cout << "Numar de tick-uri de rulat: ";
    int ticks = citesteOptiune(1, 1000000);
    Simulator simulator;
    simulator.ruleazaSimulare(ticks);
    cout << "Simulare finalizata." << '\n';
    pausaConsola();
}

void Menu::genereazaRapoarte() {
    clearScreen();
    ReportGenerator generator;
    generator.genereazaRaportAngajati("reports/angajati.csv");
    generator.genereazaRaportCereri("reports/cereri.csv");
    generator.genereazaRaportFinanciar("reports/financiar.csv");
    generator.genereazaRaportPerformanta("reports/performanta.csv");
    cout << "Rapoarte generate in folderul reports." << '\n';
    pausaConsola();
}

void Menu::incarcaDate() {
    clearScreen();
    auto manager = ServiceManager::getInstance();
    manager->incarcaAngajatiDinCSV("tests/angajati.csv");
    manager->incarcaElectrocasniceDinCSV("tests/electrocasnice.csv");
    manager->incarcaCereriDinCSV("tests/cereri.csv");
    cout << "Date incarcate din fisierele din folderul tests." << '\n';
    pausaConsola();
}

void Menu::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Menu::pausaConsola() {
    cout << "\nApasati ENTER pentru a continua...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int Menu::citesteOptiune(int min, int max) {
    int optiune;
    while(!(cin >> optiune) || optiune < min || optiune > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Optiune invalida! Introduceti un numar intre " 
                  << min << " si " << max << ": ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return optiune;
}
