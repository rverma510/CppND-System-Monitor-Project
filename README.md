# CppND-System-Monitor

This C++ project is the second project of Udacity C++ Nanodegree. The source code has been heavily adapted from the provided starter code located at (Udacity's repo)[https://github.com/udacity/CppND-System-Monitor-Project-Updated]. This project is implemented for Linux Operating System and can be used to list various information regarding the OS like total CPU and memory utilization, listing total and running processes, uptime and details about different processes running sorted based on cpu utilization in decreasing order.

![System Monitor](images/monitor.png)

## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

Install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions to Run

1. Clone the project repository: `git clone https://github.com/rverma510/CppND-System-Monitor-Project.git`

2. Build the project: `make build`

3. Run the resulting executable: `./build/monitor`
