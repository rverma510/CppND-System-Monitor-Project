#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include <linux_parser.h>
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid): pid_(pid) {};

int Process::Pid() { return pid_; }

float Process::CpuUtilization() const{ 
    long activeJiffies = LinuxParser::ActiveJiffies(pid_) / sysconf(_SC_CLK_TCK);
    long processUptime = LinuxParser::UpTime(pid_);
    if(processUptime <= 0) return 0.0;
    return (float) (1.0*activeJiffies / processUptime);   
 }

string Process::Command() { return LinuxParser::Command(Pid()); }

string Process::Ram() { return LinuxParser::Ram(Pid()); }

string Process::User() { return LinuxParser::User(Pid()); }

long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

bool Process::operator>(const Process &a) const { 
    return CpuUtilization() > a.CpuUtilization();
 }