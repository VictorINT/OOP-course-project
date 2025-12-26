#ifndef CNP_VALIDATOR_H
#define CNP_VALIDATOR_H

#include <string>

using namespace std;

class CNPValidator {
public:
    // Valideaza CNP conform specificatiilor romane
    static bool valideaza(const string&);
    
private:
    static bool verificaLungime(const string&);
    static bool verificaCifre(const string&);
    static bool verificaData(const string&);
    static bool verificaCifraControl(const string&);
};

#endif

