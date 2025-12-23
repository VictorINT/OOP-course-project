#include "../../include/utils/Factory.h"
#include "../../include/models/Receptioner.h"
#include "../../include/models/Tehnician.h"
#include "../../include/models/Supervizor.h"
#include "../../include/models/Frigider.h"
#include "../../include/models/Televizor.h"
#include "../../include/models/MasinaSpalat.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

Angajat* Factory::creeazaAngajat(const string& tip, int id, 
                                 const string& nume, 
                                 const string& cnp,
                                 const string& parametruExtra) {
    if (tip == "Receptioner") {
        return new Receptioner(id, nume, cnp);
    } else if (tip == "Tehnician") {
        return new Tehnician(id, nume, cnp, parametruExtra);
    } else if (tip == "Supervizor") {
        double spor = 0.2; // default leadership bonus 20%
        if (!parametruExtra.empty()) {
            try {
                spor = stod(parametruExtra);
            } catch (...) {
                spor = 0.2;
            }
        }
        return new Supervizor(id, nume, cnp, spor);
    }
    return nullptr;
}

Electrocasnic* Factory::creeazaElectrocasnic(const string& tip,
                                             const string& marca,
                                             const string& model,
                                             int anFabricatie,
                                             const string& parametri) {
    vector<string> tokens;
    string token;
    stringstream ss(parametri);
    while (getline(ss, token, ';')) {
        tokens.push_back(token);
    }

    auto toBool = [](const string& value) {
        string lower;
        lower.resize(value.size());
        transform(value.begin(), value.end(), lower.begin(), ::tolower);
        return lower == "1" || lower == "true" || lower == "da" || lower == "yes";
    };

    auto toIntSafe = [](const string& value, int fallback) {
        try {
            return stoi(value);
        } catch (...) {
            return fallback;
        }
    };

    auto toDoubleSafe = [](const string& value, double fallback) {
        try {
            return stod(value);
        } catch (...) {
            return fallback;
        }
    };

    if (tip == "Frigider") {
        bool areCongelator = tokens.size() > 0 ? toBool(tokens[0]) : false;
        int capacitate = tokens.size() > 1 ? toIntSafe(tokens[1], 0) : 0;
        return new Frigider(marca, model, anFabricatie, areCongelator, capacitate);
    }

    if (tip == "Televizor") {
        double diagonala = tokens.size() > 0 ? toDoubleSafe(tokens[0], 0.0) : 0.0;
        bool smart = tokens.size() > 1 ? toBool(tokens[1]) : false;
        return new Televizor(marca, model, anFabricatie, diagonala, smart);
    }

    if (tip == "MasinaSpalat") {
        int capacitate = tokens.size() > 0 ? toIntSafe(tokens[0], 0) : 0;
        int turatie = tokens.size() > 1 ? toIntSafe(tokens[1], 0) : 0;
        return new MasinaSpalat(marca, model, anFabricatie, capacitate, turatie);
    }

    return nullptr;
}
