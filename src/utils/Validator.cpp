#include "../../include/utils/Validator.h"
#include <algorithm>
#include <cctype>

using namespace std;

bool Validator::valideazaCNP(const string& cnp) {
    //! TODO: Implement CNP validation logic
    if (cnp.length() != 13) {
        return false;
    }
    
    for (char c : cnp) {
        if (!isdigit(c)) {
            return false;
        }
    }
    
    return true;
}

bool Validator::valideazaNume(const string& nume) {
    //! TODO: Implement name validation logic
    if (nume.empty()) {
        return false;
    }

    for (char c : nume) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    
    return true;
}

bool Validator::valideazaNumarPositiv(int numar) {
    return numar > 0;
}

bool Validator::valideazaNumarPositiv(double numar) {
    return numar > 0.0;
}

bool Validator::valideazaString(const string& str) {
    return !str.empty();
}
