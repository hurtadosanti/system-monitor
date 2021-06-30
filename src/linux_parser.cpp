#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
    string line;
    string key;
    string value;
    std::ifstream filestream(kOSPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ' ', '_');
            std::replace(line.begin(), line.end(), '=', ' ');
            std::replace(line.begin(), line.end(), '"', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "PRETTY_NAME") {
                    std::replace(value.begin(), value.end(), '_', ' ');
                    return value;
                }
            }
        }
    }
    return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
    string os, version, kernel;
    string line;
    std::ifstream stream(kProcDirectory + kVersionFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> version >> kernel;
    }
    return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
    vector<int> pids;
    DIR *directory = opendir(kProcDirectory.c_str());
    struct dirent *file;
    while ((file = readdir(directory)) != nullptr) {
        // Is this a directory?
        if (file->d_type == DT_DIR) {
            // Is every character of the name a digit?
            string filename(file->d_name);
            if (std::all_of(filename.begin(), filename.end(), isdigit)) {
                int pid = stoi(filename);
                pids.push_back(pid);
            }
        }
    }
    closedir(directory);
    return pids;
}

float LinuxParser::MemoryUtilization() {
    string line;
    string key;
    string value;
    float mem_total = 0.0;
    float mem_free = 0.0;
    std::ifstream filestream(kProcDirectory + kMeminfoFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "MemTotal:") {
                    value = std::regex_replace(value, std::regex(" kb"), "");
                    mem_total = std::stof(value);
                }
                if (key == "MemFree:") {
                    value = std::regex_replace(value, std::regex(" kb"), "");
                    mem_free = std::stof(value);
                }
            }
        }
        return (mem_total - mem_free)/mem_total;
    }
    return 0;

}

long LinuxParser::UpTime() {
    string up_time, cores_up_time;
    string line;
    std::ifstream stream(kProcDirectory + kUptimeFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> up_time;
    }
    return std::stol(up_time);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

//Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) {
    string line;
    string key,value;
    std::ifstream stream(kProcDirectory +std::to_string(pid)+kStatFilename);
    long total=0;
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream line_stream(line);
        long val=0;
        for (int n = 0; n < 17; n++) {
            line_stream >> val;
            if(n>12){
                total+=val;
            }
        }
    }
    return total;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

//user,nice,system,idle,iowait,irq,sirq,steal,guest,guest_nice;
vector<float> LinuxParser::CpuUtilization() {
    string line, key;
    vector<float> cpu_data;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream line_stream(line);
        line_stream >> key;
        for (int n = 0; n < 10; n++) {
            float val;
            line_stream >> val;
            cpu_data.push_back(val);
        }
    }
    return cpu_data;
}

int LinuxParser::TotalProcesses() {
    string line, key, value;
    int processes;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key) {
                if (key == "processes") {
                    linestream >> processes;
                    return processes;
                }
            }
        }
    }
    return 0;
}

int LinuxParser::RunningProcesses() {
    string line, key, value;
    int processes;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key) {
                if (key == "procs_running") {
                    linestream >> processes;
                    return processes;
                }
            }
        }
    }
    return 0;
}

//Read and return the command associated with a process
string LinuxParser::Command(int pid) {
    string line;
    std::ifstream filestream(kProcDirectory +std::to_string(pid)+kCmdlineFilename);
    if (filestream.is_open()) {
        std::getline(filestream, line);
        return line;
    }
    return "";
}

string LinuxParser::Ram(int pid) {
    string line;
    string key,value;
    std::ifstream filestream(kProcDirectory +std::to_string(pid)+kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "VmSize:") {
                    value = std::regex_replace(value, std::regex(" kb"), "");
                    return std::to_string(stoi(value)/1024);
                }
            }
        }
    }
    return "";
}

string LinuxParser::Uid(int pid) {
    string line;
    string key,value;
    std::ifstream filestream(kProcDirectory+ std::to_string(pid)+kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if(key=="Uid:"){
                    return value;
                }
            }
        }
    }
    return "";
}

string LinuxParser::User(int pid) {
    auto uid = Uid(pid);
    string line;
    string key,value;
    std::ifstream filestream(kPasswordPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::replace(line.begin(), line.end(), 'x', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if(uid==value){
                    return key;
                }
            }
        }
    }
    return "";
}
long LinuxParser::UpTime(int pid) {
    string line;
    string key,value;
    long uptime=0;
    std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatFilename);
    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        for(auto i=0;i<22;++i){
            linestream>>value;
        }
        uptime = std::stol(value);
    }
    return uptime;
}
