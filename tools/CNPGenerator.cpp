#include "CNPGenerator.h"
#include <sstream>
#include <iomanip>
#include <random>
#include <chrono>
#include <stdexcept>

using namespace std;

string CNPGenerator::genereazaCNP(int sex, int an, int luna, int zi, 
                                        int judet, int secventa) {
    // Valideaza parametrii
    if (sex < 1 || sex > 9) {
        throw invalid_argument("Sex invalid (trebuie sa fie intre 1 si 9)");
    }
    
    if (luna < 1 || luna > 12) {
        throw invalid_argument("Luna invalida");
    }
    
    int zileMax = zileLuna(luna, an);
    if (zi < 1 || zi > zileMax) {
        throw invalid_argument("Zi invalida pentru luna respectiva");
    }
    
    if (judet < 1 || judet > 52) {
        throw invalid_argument("Cod judet invalid (1-52)");
    }
    
    if (secventa < 1 || secventa > 999) {
        throw invalid_argument("Secventa invalida (1-999)");
    }
    
    // Determina cifra de sex bazat pe an si sex real
    int cifraSex = sex;
    if (sex == 1 || sex == 2) {  // M sau F
        if (an >= 1800 && an < 1900) {
            cifraSex = (sex == 1) ? 3 : 4;  // 1800-1899
        } else if (an >= 1900 && an < 2000) {
            cifraSex = (sex == 1) ? 1 : 2;  // 1900-1999
        } else if (an >= 2000) {
            cifraSex = (sex == 1) ? 5 : 6;  // 2000+
        }
    }
    
    // Extrage ultimele 2 cifre din an
    int anScurt = an % 100;
    
    // Construieste CNP (fara cifra de control)
    ostringstream cnp; // un fel de cout dar in memorie
    // setw seteaza latimea de 2, setfill pune 0 in caz ca e an scrut sau ceva de genul
    // si necesita un singur digit

    cnp << cifraSex
        << setfill('0') << setw(2) << anScurt
        << setfill('0') << setw(2) << luna
        << setfill('0') << setw(2) << zi
        << setfill('0') << setw(2) << judet
        << setfill('0') << setw(3) << secventa;
    
    string cnpPartial = cnp.str();
    
    // Calculeaza si adauga cifra de control
    int cifraControl = calculeazaCifraControl(cnpPartial);
    cnpPartial += to_string(cifraControl);
    
    return cnpPartial;
}

string CNPGenerator::genereazaCNPRandom() {
    // Seed pentru random, modern C++ 11. random_device ia nr random din hardware noise
    // iar mt19337 vine de la 2^19337-1 si produce flux de nr random bazat pe seed ul rd
    static random_device rd;
    static mt19937 gen(rd());
    
    // Genereaza componente random
    // uniform_int_distribution functor pentru limitele intervalului de random
    uniform_int_distribution<> sexDist(1, 2);  // 1=M, 2=F
    uniform_int_distribution<> anDist(1950, 2005);  // Ani rezonabili
    uniform_int_distribution<> lunaDist(1, 12);
    uniform_int_distribution<> judetDist(1, 52);
    uniform_int_distribution<> secventaDist(1, 999);
    
    int sex = sexDist(gen);
    int an = anDist(gen);
    int luna = lunaDist(gen);
    
    // Genereaza zi valida pentru luna respectiva
    int zileMax = zileLuna(luna, an);
    uniform_int_distribution<> ziDist(1, zileMax);
    int zi = ziDist(gen);
    
    int judet = judetDist(gen);
    int secventa = secventaDist(gen);
    
    return genereazaCNP(sex, an, luna, zi, judet, secventa);
}

vector<string> CNPGenerator::genereazaMultiple(int numar) {
    vector<string> rezultat;
    rezultat.reserve(numar);
    
    for (int i = 0; i < numar; i++) {
        rezultat.push_back(genereazaCNPRandom());
    }
    
    return rezultat;
}

int CNPGenerator::calculeazaCifraControl(const string& cnp) {
    // Cheia pentru calculul cifrei de control
    const string cheie = "279146358279";
    int suma = 0;
    
    // Calculeaza suma ponderata
    for (size_t i = 0; i < 12; i++) {
        suma += (cnp[i] - '0') * (cheie[i] - '0');
    }
    
    // Calculeaza cifra de control
    int cifraControl = suma % 11;
    if (cifraControl == 10) {
        cifraControl = 1;
    }
    
    return cifraControl;
}

bool CNPGenerator::esteAnBisect(int an) {
    return (an % 4 == 0 && an % 100 != 0) || (an % 400 == 0);
}

int CNPGenerator::zileLuna(int luna, int an) {
    const int zile[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (luna == 2 && esteAnBisect(an)) {
        return 29;
    }
    
    return zile[luna - 1];
}

