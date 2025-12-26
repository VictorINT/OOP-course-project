#ifndef EMPLOYEE_FACTORY_H
#define EMPLOYEE_FACTORY_H

#include <memory>
#include <string>
#include "../models/Employee.h"

using namespace std;

class EmployeeFactory {
public:
    // Creeaza un angajat pe baza tipului specificat
    static shared_ptr<Employee> creeazaAngajat(
        const string&,  // tip: "Receptioner", "Tehnician", "Supervizor"
        const string&,  // nume
        const string&,  // prenume
        const string&,  // cnp
        const string&,  // data angajarii
        const string&   // oras
    );
    
private:
    // Valideaza varsta la angajare (minim 16 ani)
    static bool valideazaVarstaAngajare(const string&, const string&);
    static int extrageAnNastere(const string&);
};

#endif

