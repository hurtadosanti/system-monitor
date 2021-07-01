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
    string secs_string = std::to_string(s);
    if(secs_string.length()==1){
        secs_string = "0"+secs_string;
    }
    return std::to_string(h)+":"+std::to_string(m)+":"+secs_string;
}