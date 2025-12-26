#include "TimestampUtil.h"
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

string TimestampUtil::genereazaTimestamp() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm* now_tm = localtime(&now_time);
    
    ostringstream oss;
    oss << put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

chrono::system_clock::time_point 
TimestampUtil::parseazaTimestamp(const string& timestamp) {
    tm tm = {};
    istringstream ss(timestamp);
    ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
    
    return chrono::system_clock::from_time_t(mktime(&tm));
}

bool TimestampUtil::esteInainte(const string& ts1, const string& ts2) {
    auto t1 = parseazaTimestamp(ts1);
    auto t2 = parseazaTimestamp(ts2);
    return t1 < t2;
}

bool TimestampUtil::valideazaTimestamp(const string& timestamp) {
    if (timestamp.length() != 19) return false;
    
    try {
        parseazaTimestamp(timestamp);
        return true;
    } catch (...) {
        return false;
    }
}

