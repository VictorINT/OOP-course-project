#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<string> FileReader::citesteFisier(const string& numeFisier) {
    vector<string> linii;
    ifstream fisier(numeFisier);
    
    if (!fisier.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide fisierul " << numeFisier << "\n";
        return linii;
    }
    
    string linie;
    while (getline(fisier, linie)) {
        if (!linie.empty()) {
            linii.push_back(linie);
        }
    }
    
    fisier.close();
    return linii;
}

vector<string> FileReader::parseazaLinieCSV(const string& linie) {
    vector<string> elemente;
    stringstream ss(linie);
    string element;
    
    while (getline(ss, element, ',')) {
        // Elimina spatii de la inceput si sfarsit
        size_t start = element.find_first_not_of(" \t\r\n");
        size_t end = element.find_last_not_of(" \t\r\n");
        
        if (start != string::npos) {
            element = element.substr(start, end - start + 1);
        } else {
            element = "";
        }
        
        elemente.push_back(element);
    }
    
    return elemente;
}

void FileReader::raporteazaEroare(int numarLinie, const string& mesaj) {
    cerr << "Eroare la citire: linia " << numarLinie << " - " << mesaj << "\n";
}

