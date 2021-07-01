#include <string>

#include "format.h"

using std::string;
using namespace std::chrono;

//Verify length and convert to string
string to_string(long value){
    string string_value = std::to_string(value);
    if(string_value.length()==1){
        string_value = "0"+string_value;
    }
    return string_value;
}
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long value) {
    seconds sec(value);
    auto h = duration_cast<hours>(sec).count();
    auto m = duration_cast<minutes>(sec).count()%60;
    auto s = sec.count()%60;
    return to_string(h)+":"+to_string(m)+":"+to_string(s);
}

