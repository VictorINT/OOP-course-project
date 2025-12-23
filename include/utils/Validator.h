#pragma once
#include <string>

using namespace std;

class Validator {
public:
    static bool valideazaCNP(const string&);
    static bool valideazaNume(const string&);
    static bool valideazaNumarPositiv(int);
    static bool valideazaNumarPositiv(double);
    static bool valideazaString(const string&);
};
