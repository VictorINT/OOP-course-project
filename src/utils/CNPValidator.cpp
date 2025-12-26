#include "CNPValidator.h"
#include <algorithm>
#include <cctype>

using namespace std;

bool CNPValidator::valideaza(const string& cnp) {
    if (!verificaLungime(cnp)) return false;
    if (!verificaCifre(cnp)) return false;
    if (!verificaData(cnp)) return false;
    if (!verificaCifraControl(cnp)) return false;
    return true;
}

bool CNPValidator::verificaLungime(const string& cnp) {
    return cnp.length() == 13;
}

bool CNPValidator::verificaCifre(const string& cnp) {
    return all_of(cnp.begin(), cnp.end(), ::isdigit);
}

bool CNPValidator::verificaData(const string& cnp) {
    // Extrage sexul si data
    int sex = cnp[0] - '0';
    if (sex < 1 || sex > 9) return false;
    
    // Extrage anul, luna, ziua
    int an = (cnp[1] - '0') * 10 + (cnp[2] - '0');
    int luna = (cnp[3] - '0') * 10 + (cnp[4] - '0');
    int zi = (cnp[5] - '0') * 10 + (cnp[6] - '0');
    
    // Verifica luna
    if (luna < 1 || luna > 12) return false;
    
    // Verifica ziua
    if (zi < 1 || zi > 31) return false;
    
    // Verifica zile pentru fiecare luna
    int zileInLuna[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Calculeaza anul complet
    int anComplet = an;
    if (sex == 1 || sex == 2) anComplet += 1900;
    else if (sex == 3 || sex == 4) anComplet += 1800;
    else if (sex == 5 || sex == 6) anComplet += 2000;
    
    // Verifica an bisect pentru februarie
    if (luna == 2) {
        bool bisect = (anComplet % 4 == 0 && anComplet % 100 != 0) || 
                      (anComplet % 400 == 0);
        if (bisect) zileInLuna[1] = 29;
    }
    
    if (zi > zileInLuna[luna - 1]) return false;
    
    return true;
}

bool CNPValidator::verificaCifraControl(const string& cnp) {
    const string cheie = "279146358279";
    int suma = 0;
    
    for (int i = 0; i < 12; i++) {
        suma += (cnp[i] - '0') * (cheie[i] - '0');
    }
    
    int cifraControl = suma % 11;
    if (cifraControl == 10) cifraControl = 1;
    
    return (cnp[12] - '0') == cifraControl;
}

