#include "../../include/utils/DateUtils.h"
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

long long DateUtils::getTimpCurent() {
    auto now = chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return chrono::duration_cast<chrono::seconds>(duration).count();
}

string DateUtils::formatTimestamp(long long timestamp) {
    time_t time = static_cast<time_t>(timestamp);
    tm* tm = localtime(&time);
    ostringstream oss;
    oss << put_time(tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

long long DateUtils::parseTimestamp(const string& dateStr) {
    tm t = {};
    istringstream iss(dateStr);
    iss >> get_time(&t, "%Y-%m-%d %H:%M:%S");
    if (iss.fail()) {
        return 0;
    }
    t.tm_isdst = -1;
    time_t timeValue = mktime(&t);
    if (timeValue == -1) {
        return 0;
    }
    return static_cast<long long>(timeValue);
}

int DateUtils::diferentaOre(long long timestamp1, long long timestamp2) {
    long long diff = timestamp2 - timestamp1;
    return static_cast<int>(diff / 3600);
}

int DateUtils::diferentaZile(long long timestamp1, long long timestamp2) {
    long long diff = timestamp2 - timestamp1;
    return static_cast<int>(diff / 86400);
}

string DateUtils::timestampToString(long long timestamp) {
    return formatTimestamp(timestamp);
}
