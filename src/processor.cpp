#include <linux_parser.h>
#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    //user,nice,system,idle,io wait,irq,soft irq,steal,guest,guest_nice;
    auto data = LinuxParser::CpuUtilization();
    auto user_time = data[0] - data[8];
    auto nice_time = data[1] - data[9];
    auto idle_all_time = data[3] + data[4];
    auto system_all_time = data[2] + data[5] + data[6];
    auto virtual_time = data[8] + data[9];

    auto total_time = user_time + nice_time + system_all_time + idle_all_time + data[7] + virtual_time;

    this->total = total_time - this->total;
    this->idle = idle_all_time - this->idle;

    return (this->total- this->idle)/this->total;
}