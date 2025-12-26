#ifndef TIMESTAMP_UTIL_H
#define TIMESTAMP_UTIL_H

#include <string>
#include <chrono>

using namespace std;

class TimestampUtil {
public:
    // Genereaza timestamp curent
    static string genereazaTimestamp();
    
    // Parseaza timestamp din string (format: YYYY-MM-DD HH:MM:SS)
    static chrono::system_clock::time_point parseazaTimestamp(const string&);
    
    // Compara doua timestampuri
    static bool esteInainte(const string&, const string&);
    
    // Valideaza format timestamp
    static bool valideazaTimestamp(const string&);
};

#endif

