#include "../../include/utils/Factory.h"
#include "../../include/models/Receptioner.h"
#include "../../include/models/Tehnician.h"
#include "../../include/models/Supervizor.h"
#include "../../include/models/Frigider.h"
#include "../../include/models/Televizor.h"
#include "../../include/models/MasinaSpalat.h"
#include <sstream>

using namespace std;

Angajat* Factory::creeazaAngajat(const string& tip, int id, 
                                 const string& nume, 
                                 const string& cnp,
                                 const string& parametruExtra) {
    //! TODO: Implement factory logic for creating employees
    if (tip == "Receptioner") {
        return new Receptioner(id, nume, cnp);
    } else if (tip == "Tehnician") {
        return new Tehnician(id, nume, cnp, parametruExtra);
    } else if (tip == "Supervizor") {
        double spor = 0.0;
        return new Supervizor(id, nume, cnp, spor);
    }
    return nullptr;
}

Electrocasnic* Factory::creeazaElectrocasnic(const string& tip,
                                             const string& marca,
                                             const string& model,
                                             int anFabricatie,
                                             const string& parametri) {
    //! TODO: Implement factory logic for creating appliances
    if (tip == "Frigider") {
        return new Frigider(marca, model, anFabricatie, false, 0);
    } else if (tip == "Televizor") {
        return new Televizor(marca, model, anFabricatie, 0.0, false);
    } else if (tip == "MasinaSpalat") {
        return new MasinaSpalat(marca, model, anFabricatie, 0, 0);
    }
    return nullptr;
}
