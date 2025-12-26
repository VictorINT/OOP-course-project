// Tool pentru generarea de CNP-uri valide
// Compileaza cu: g++ -std=c++17 tools/cnp_generator_tool.cpp tools/CNPGenerator.cpp -o bin/cnp_generator

#include <iostream>
#include <string>
#include "CNPGenerator.h"

using namespace std;

void afiseazaAjutor() {
    cout << "=== Generator CNP-uri Valide ===\n\n";
    cout << "Utilizare:\n";
    cout << "  1. Genereaza CNP random: cnp_generator random\n";
    cout << "  2. Genereaza N CNP-uri: cnp_generator multiple <numar>\n";
    cout << "  3. Genereaza CNP specific: cnp_generator <sex> <an> <luna> <zi> [judet] [secventa]\n";
    cout << "\nParametrii:\n";
    cout << "  sex      - 1=Masculin, 2=Feminin\n";
    cout << "  an       - Anul nasterii (ex: 1990)\n";
    cout << "  luna     - Luna nasterii (1-12)\n";
    cout << "  zi       - Ziua nasterii (1-31)\n";
    cout << "  judet    - Codul judetului (1-52, optional, default=1)\n";
    cout << "  secventa - Numar secvential (1-999, optional, default=1)\n";
    cout << "\nExemple:\n";
    cout << "  cnp_generator random\n";
    cout << "  cnp_generator multiple 10\n";
    cout << "  cnp_generator 1 1990 5 15\n";
    cout << "  cnp_generator 2 1985 3 20 40 123\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        afiseazaAjutor();
        return 1;
    }
    
    string comanda = argv[1];
    
    try {
        if (comanda == "help" || comanda == "--help" || comanda == "-h") {
            afiseazaAjutor();
            return 0;
        }
        else if (comanda == "random") {
            string cnp = CNPGenerator::genereazaCNPRandom();
            cout << cnp << "\n";
        }
        else if (comanda == "multiple") {
            if (argc < 3) {
                cerr << "Eroare: Trebuie sa specifici numarul de CNP-uri\n";
                cerr << "Utilizare: cnp_generator multiple <numar>\n";
                return 1;
            }
            
            int numar = stoi(argv[2]);
            if (numar < 1 || numar > 1000) {
                cerr << "Eroare: Numarul trebuie sa fie intre 1 si 1000\n";
                return 1;
            }
            
            auto cnpuri = CNPGenerator::genereazaMultiple(numar);
            for (const auto& cnp : cnpuri) {
                cout << cnp << "\n";
            }
        }
        else {
            // Genereaza CNP specific
            if (argc < 5) {
                cerr << "Eroare: Parametrii insuficienti\n";
                cerr << "Utilizare: cnp_generator <sex> <an> <luna> <zi> [judet] [secventa]\n";
                return 1;
            }
            
            int sex = stoi(argv[1]);
            int an = stoi(argv[2]);
            int luna = stoi(argv[3]);
            int zi = stoi(argv[4]);
            int judet = (argc > 5) ? stoi(argv[5]) : 1;
            int secventa = (argc > 6) ? stoi(argv[6]) : 1;
            
            string cnp = CNPGenerator::genereazaCNP(sex, an, luna, zi, judet, secventa);
            cout << cnp << "\n";
        }
    }
    catch (const exception& e) {
        cerr << "Eroare: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}

