# Makefile
# Build rules for EECS 280 project 5

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++11 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

main.exe: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -lncurses -o $@

# Remove automatically generated files
clean :
	rm -rvf *.exe *~ *.out *.dSYM *.stackdump

