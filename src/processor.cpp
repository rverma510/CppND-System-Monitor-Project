#include "linux_parser.h"
#include "processor.h"
#include <string>
using std::stof;
using std::string;
using std::vector;

float Processor::Utilization() { 
    vector<string> values = LinuxParser::CpuUtilization();
    float prevIdle = idle + iowait;
    float idle = stof(values[3]) + stof(values[4]);

    float prevNonIdle = user + nice + system + irq + softirq + steal;
    float nonIdle = stof(values[0]) + stof(values[1]) + stof(values[2]) +
                    stof(values[5]) + stof(values[6]) + stof(values[7]);
    
    float prevTotal = prevIdle + prevNonIdle;
    float total = idle + nonIdle;
    
    float totalD = total - prevTotal;
    float idleD = idle - prevIdle;

    setPrevValues(values);

    return (totalD - idleD) / totalD;
}

void Processor::setPrevValues(vector<string> v) {
    user = stof(v[0]);
    nice = stof(v[1]);
    system = stof(v[2]);
    idle = stof(v[3]);
    iowait = stof(v[4]);
    irq = stof(v[5]);
    softirq = stof(v[6]);
    steal = stof(v[7]);
}