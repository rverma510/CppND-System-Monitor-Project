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

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const{ 
    long activeJiffies = LinuxParser::ActiveJiffies(pid_);
    long processUptime = LinuxParser::Jiffies() - LinuxParser::UpTime(pid_);
    if(processUptime <= 0) return 0.0;
    return (float) (1.0*activeJiffies / processUptime);   
 }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator>(const Process &a) const { 
    return CpuUtilization() > a.CpuUtilization();
 }