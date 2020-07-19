#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void setPrevValues(vector<string>);
  // TODO: Declare any necessary private members
 private:
 float user{0};
 float nice{0};
 float system{0};
 float idle{0};
 float iowait{0};
 float irq{0};
 float softirq{0};
 float steal{0};
};

#endif