#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::stol;
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
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float memTotal{1}, memFree{0}, buffers{0}, cached{0}, sReclaimable{0}, shmem{0};
  std::string tmp;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (stream >> tmp) {
      if (tmp.compare("MemTotal:") == 0) {
        if (stream >> tmp) memTotal = stof(tmp);
      }
      else if (tmp.compare("MemFree:") == 0) {
        if (stream >> tmp) memFree = stof(tmp);
      }
      else if (tmp.compare("Buffers:") == 0) {
        if (stream >> tmp) buffers = stof(tmp);
      }
      else if (tmp.compare("Cached:") == 0) {
        if (stream >> tmp) cached = stof(tmp);
      }
      else if (tmp.compare("SReclaimable:") == 0) {
        if (stream >> tmp) sReclaimable = stof(tmp);
      }
      else if (tmp.compare("Shmem:") == 0) {
        if (stream >> tmp) shmem = stof(tmp);
      }
    }
  }
  float memUsed = memTotal - memFree - buffers - cached - sReclaimable + shmem;
  return memUsed / memTotal;
 }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  std::string tmp;
  if (stream.is_open()) {
    if (stream >> tmp) {
      return stol(tmp);
    }
  }
  return 0;
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpu;
  string token, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) { 
      std::istringstream stringStream(line);
      if (stringStream >> token) {
        if (token.compare("cpu") == 0) {
          while (stringStream >> token) cpu.push_back(token);
          return cpu;
        }
      }
    }
  }
  return cpu;
 }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::ifstream stream(kProcDirectory + kStatFilename);
  string token;
  if (stream.is_open()) {
    while (stream >> token) {
      if (token.compare("processes") == 0) {
        if (stream >> token) return stoi(token);
      }
    }
  }
  return 0;
 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::ifstream stream(kProcDirectory + kStatFilename);
  string token;
  if (stream.is_open()) {
    while (stream >> token) {
      if (token.compare("procs_running") == 0) {
        if (stream >> token) return stoi(token);
      }
    }
  }
  return 0;
 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  string token;
  if (stream.is_open()) {
    std::getline(stream, token);
    return token;
  }
  return "";
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  string token;
  if (stream.is_open()) {
    while (stream >> token) {
      if (token.compare("VmSize:") == 0) {
        if (stream >> token) return token;
      }
    }
  }
  return "0";
 }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  string token;
  if (stream.is_open()) {
    while (stream >> token) {
      if (token.compare("Uid:") == 0) {
        if (stream >> token) return token;
      }
    }
  }
  return "";
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string Uid = LinuxParser::Uid(pid);
  if (Uid == "")
    return "";
  string username, password, userId;
  string line;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::replace(line.begin(), line.end(), ':', ' ');
    std::istringstream stringStream(line);
    if (stringStream >> username >> password >> userId) {
      if (userId.compare(Uid) == 0) return username;
    }
  }
  return "";
 }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  string token;
  if (stream.is_open()) {
    int i = 0;
    while(stream >> token) {
      if (i == 13) {
        long time = stol(token);
        time /= sysconf(_SC_CLK_TCK);
        return time;
      }
      i++;
    }
  }
  return 0;
 }