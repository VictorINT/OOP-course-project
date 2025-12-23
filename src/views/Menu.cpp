#include "../../include/views/Menu.h"
#include "../../include/managers/ServiceManager.h"
#include "../../include/managers/Simulator.h"
#include "../../include/managers/ReportGenerator.h"
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
    //! TODO: Implement display logic
    pausaConsola();
}

void Menu::adaugaAngajat() {
    //! TODO: Implement add logic
    pausaConsola();
}

void Menu::afiseazaCereri() {
    //! TODO: Implement display logic
    pausaConsola();
}

void Menu::adaugaCerere() {
    //! TODO: Implement add logic
    pausaConsola();
}

void Menu::ruleazaSimulare() {
    //! TODO: Implement simulation logic
    pausaConsola();
}

void Menu::genereazaRapoarte() {
    //! TODO: Implement report generation logic
    pausaConsola();
}

void Menu::incarcaDate() {
    //! TODO: Implement data loading logic
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
