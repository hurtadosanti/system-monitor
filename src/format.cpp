#include <string>

#include "format.h"

using std::string;
using namespace std::chrono;
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long value) {
    seconds sec(value);
    auto h = duration_cast<hours>(sec).count();
    auto m = duration_cast<minutes>(sec).count()%60;
    auto s = sec.count()%60;
    return std::to_string(h)+":"+std::to_string(m)+":"+std::to_string(s);
}