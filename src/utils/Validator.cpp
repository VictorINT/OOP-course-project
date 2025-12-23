#include "../../include/utils/Validator.h"
#include <algorithm>
#include <cctype>
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;

bool Validator::valideazaCNP(const string& cnp) {
    if (cnp.length() != 13) {
        return false;
    }

    if (!all_of(cnp.begin(), cnp.end(), ::isdigit)) {
        return false;
    }

    int s = cnp[0] - '0';
    int yy = stoi(cnp.substr(1, 2));
    int mm = stoi(cnp.substr(3, 2));
    int dd = stoi(cnp.substr(5, 2));

    int yearPrefix = 1900;
    if (s == 1 || s == 2) yearPrefix = 1900;
    else if (s == 3 || s == 4) yearPrefix = 1800;
    else if (s == 5 || s == 6) yearPrefix = 2000;
    else if (s == 7 || s == 8 || s == 9) yearPrefix = 2000;
    else return false;

    int year = yearPrefix + yy;

    if (mm < 1 || mm > 12 || dd < 1 || dd > 31) {
        return false;
    }

    tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon = mm - 1;
    t.tm_mday = dd;
    t.tm_isdst = -1;
    time_t timeValue = mktime(&t);
    if (timeValue == -1) {
        return false;
    }

    tm* normalized = localtime(&timeValue);
    if (normalized->tm_year != t.tm_year || normalized->tm_mon != t.tm_mon || normalized->tm_mday != t.tm_mday) {
        return false;
    }

    static const int controlWeights[12] = {2,7,9,1,4,6,3,5,8,2,7,9};
    int controlSum = 0;
    for (int i = 0; i < 12; i++) {
        controlSum += (cnp[i] - '0') * controlWeights[i];
    }
    int controlDigit = controlSum % 11;
    if (controlDigit == 10) controlDigit = 1;

    return controlDigit == (cnp[12] - '0');
}

bool Validator::valideazaNume(const string& nume) {
    if (nume.empty()) {
        return false;
    }

    auto isValidChar = [](char c) {
        return isalpha(static_cast<unsigned char>(c)) || c == ' ' || c == '-';
    };

    if (!all_of(nume.begin(), nume.end(), isValidChar)) {
        return false;
    }

    string token;
    stringstream ss(nume);
    while (ss >> token) {
        if (token.size() < 3 || token.size() > 30) {
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
