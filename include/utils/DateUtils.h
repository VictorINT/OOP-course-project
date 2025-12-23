#pragma once
#include <string>
#include <ctime>

using namespace std;

class DateUtils {
public:
    static long long getTimpCurent();
    static string formatTimestamp(long long);
    static long long parseTimestamp(const string&);
    static int diferentaOre(long long, long long);
    static int diferentaZile(long long, long long);
    static string timestampToString(long long);
};
