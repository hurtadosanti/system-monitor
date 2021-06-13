#include <string>

#include "format.h"

using std::string;
using namespace std::chrono;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long value) {
    seconds sec(value);
    auto h = duration_cast<hours>(sec).count();
    auto m = duration_cast<minutes>(sec).count()%60;
    auto s = sec.count()%60;
    return std::to_string(h)+":"+std::to_string(m)+":"+std::to_string(s);
}