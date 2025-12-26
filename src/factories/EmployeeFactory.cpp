#include "EmployeeFactory.h"
#include "../models/Receptioner.h"
#include "../models/Tehnician.h"
#include "../models/Supervizor.h"
#include "../exceptions/ServiceException.h"

using namespace std;

shared_ptr<Employee> EmployeeFactory::creeazaAngajat(
    const string& tip,
    const string& nume,
    const string& prenume,
    const string& cnp,
    const string& dataAngajarii,
    const string& oras) {
    
    // Valideaza varsta la angajare
    if (!valideazaVarstaAngajare(cnp, dataAngajarii)) {
        throw InvalidAgeException("Angajatul trebuie sa aiba minim 16 ani la angajare");
    }
    
    if (tip == "Receptioner") {
        return make_shared<Receptioner>(nume, prenume, cnp, dataAngajarii, oras);
    } else if (tip == "Tehnician") {
        return make_shared<Tehnician>(nume, prenume, cnp, dataAngajarii, oras);
    } else if (tip == "Supervizor") {
        return make_shared<Supervizor>(nume, prenume, cnp, dataAngajarii, oras);
    } else {
        throw InvalidDataException("Tip angajat invalid: " + tip);
    }
}

bool EmployeeFactory::valideazaVarstaAngajare(const string& cnp, 
                                               const string& dataAngajarii) {
    int anNastere = extrageAnNastere(cnp);
    int anAngajare = stoi(dataAngajarii.substr(0, 4));
    
    return (anAngajare - anNastere) >= 16;
}

int EmployeeFactory::extrageAnNastere(const string& cnp) {
    int sex = cnp[0] - '0';
    int an = (cnp[1] - '0') * 10 + (cnp[2] - '0');
    
    // Determina secolul
    if (sex == 1 || sex == 2) an += 1900;
    else if (sex == 3 || sex == 4) an += 1800;
    else if (sex == 5 || sex == 6) an += 2000;
    else if (sex == 7 || sex == 8) an += 2000;  // rezidenti
    else if (sex == 9) an += 2000;  // straini
    
    return an;
}

