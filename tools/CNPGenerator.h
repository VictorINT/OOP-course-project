#ifndef CNP_GENERATOR_H
#define CNP_GENERATOR_H

#include <string>
#include <vector>

using namespace std;

class CNPGenerator {
public:
    // Genereaza un CNP valid
    static string genereazaCNP(
        int sex,           // 1-9 (1=M 1900-1999, 2=F 1900-1999, 5=M 2000+, 6=F 2000+)
        int an,            // Anul nasterii (format complet: 1950, 2000, etc)
        int luna,          // 1-12
        int zi,            // 1-31
        int judet = 1,     // Codul judetului (1-52)
        int secventa = 1   // Numar secvential (1-999)
    );
    
    // Genereaza CNP random valid
    static string genereazaCNPRandom();
    
    // Genereaza mai multe CNP-uri
    static vector<string> genereazaMultiple(int numar);
    
private:
    static int calculeazaCifraControl(const string&);
    static bool esteAnBisect(int);
    static int zileLuna(int, int);
};

#endif

