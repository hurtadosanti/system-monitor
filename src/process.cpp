#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

int Process::Pid() { return pid; }


float Process::CpuUtilization() const {
    auto jiffies = LinuxParser::ActiveJiffies(pid);
    if(jiffies>0){
        return (jiffies/ sysconf(_SC_CLK_TCK))/UpTime();
    }
    return 0.0;
}

string Process::Command() { return LinuxParser::Command(pid); }


string Process::Ram() {
    return LinuxParser::Ram(pid);
}

string Process::User() {
    return LinuxParser::User(pid);
}

long int Process::UpTime() const{
    return LinuxParser::UpTime()-(LinuxParser::UpTime(pid)/ sysconf(_SC_CLK_TCK));
}

bool Process::operator<(Process const &a) const {
    return CpuUtilization()<a.CpuUtilization();
}