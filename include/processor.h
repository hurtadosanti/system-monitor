#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
public:
    float Utilization();

private:
    float total=0.0;
    float idle=0.0;
};

#endif