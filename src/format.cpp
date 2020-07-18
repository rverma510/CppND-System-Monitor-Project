#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long sec = seconds % 60;
    long min = (seconds / 60) % 60;
    long hrs = (seconds / 3600);
    string s = sec < 10 ? '0' + to_string(sec) : to_string(sec);
    string m = min < 10 ? '0' + to_string(min) : to_string(min);
    string h = hrs < 10 ? '0' + to_string(hrs) : to_string(hrs);
    return h + ":" + m + ":" + s;
}