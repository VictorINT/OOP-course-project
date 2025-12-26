#include "ElectrocasnicFactory.h"
#include "../models/Frigider.h"
#include "../models/TV.h"
#include "../models/MasinaSpalat.h"
#include "../exceptions/ServiceException.h"

using namespace std;

shared_ptr<Electrocasnic> ElectrocasnicFactory::creeazaElectrocasnic(
    const string& tip,
    const string& marca,
    const string& model,
    int anFabricatie,
    double pretCatalog,
    const string& detaliiSpecifice) {
    
    if (tip == "Frigider") {
        return creeazaFrigider(marca, model, anFabricatie, pretCatalog, detaliiSpecifice);
    } else if (tip == "TV") {
        return creeazaTV(marca, model, anFabricatie, pretCatalog, detaliiSpecifice);
    } else if (tip == "MasinaSpalat") {
        return creeazaMasinaSpalat(marca, model, anFabricatie, pretCatalog, detaliiSpecifice);
    } else {
        throw InvalidDataException("Tip electrocasnic invalid: " + tip);
    }
}

shared_ptr<Electrocasnic> ElectrocasnicFactory::creeazaFrigider(
    const string& marca,
    const string& model,
    int anFabricatie,
    double pretCatalog,
    const string& detaliiSpecifice) {
    
    // Format: "true" sau "false" pentru congelator
    bool areCongelator = (detaliiSpecifice == "true" || detaliiSpecifice == "1");
    return make_shared<Frigider>(marca, model, anFabricatie, pretCatalog, areCongelator);
}

shared_ptr<Electrocasnic> ElectrocasnicFactory::creeazaTV(
    const string& marca,
    const string& model,
    int anFabricatie,
    double pretCatalog,
    const string& detaliiSpecifice) {
    
    // Format: "diagonala:unitate" (ex: "55:inch" sau "140:cm")
    size_t pos = detaliiSpecifice.find(':');
    if (pos == string::npos) {
        throw InvalidDataException("Format invalid pentru TV: " + detaliiSpecifice);
    }
    
    double diagonala = stod(detaliiSpecifice.substr(0, pos));
    string unitate = detaliiSpecifice.substr(pos + 1);
    
    return make_shared<TV>(marca, model, anFabricatie, pretCatalog, diagonala, unitate);
}

shared_ptr<Electrocasnic> ElectrocasnicFactory::creeazaMasinaSpalat(
    const string& marca,
    const string& model,
    int anFabricatie,
    double pretCatalog,
    const string& detaliiSpecifice) {
    
    // Format: capacitatea in kg (ex: "7" sau "8.5")
    double capacitate = stod(detaliiSpecifice);
    return make_shared<MasinaSpalat>(marca, model, anFabricatie, pretCatalog, capacitate);
}

