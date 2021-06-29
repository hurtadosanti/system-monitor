#include "system.h"

#include <linux_parser.h>
#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include <iostream>

using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() {
    return cpu_;
}

vector<Process>& System::Processes() {
    processes_.clear();
    for(auto p :LinuxParser::Pids()){
        processes_.emplace_back(Process(p));
    }
    std::sort(processes_.begin(),processes_.end());
    return processes_;
}

std::string System::Kernel() { return LinuxParser::Kernel(); }

float System::MemoryUtilization() {
    auto mem = LinuxParser::MemoryUtilization();
    return mem;
}

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses();}

long int System::UpTime() {
  auto time =  LinuxParser::UpTime();
  return time;}