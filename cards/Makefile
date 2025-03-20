
# Simple Makefile to build main using Card.cpp and main.cpp

CXX = g++
CXXFLAGS = -Wall -std=c++17
LIBS = -lncursesw

# Default target
all: main

# Link main
main: main.o Card.o
	$(CXX) $(CXXFLAGS) -o main main.o Card.o $(LIBS)

# Compile main.cpp
main.o: main.cpp Card.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile Card.cpp
Card.o: Card.cpp Card.h
	$(CXX) $(CXXFLAGS) -c Card.cpp

# Clean up build artifacts
clean:
	rm -f *.o main

