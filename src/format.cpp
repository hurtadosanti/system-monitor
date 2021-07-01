#include <string>

#include "format.h"

using std::string;
using namespace std::chrono;
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
    auto h = seconds/(60*60);
    auto m = (seconds/60)%60;
    auto s = seconds%60;
    return std::to_string(h)+":"+std::to_string(m)+":"+std::to_string(s);
}