.PHONY: clean

CXX=g++
CXXFLAGS=-std=c++11
SRC=various_statistical.cpp

all: various_statistical

various_statistical: $(SRC)
	$(CXX) $(CXXFLAGS) -pthread $< -o $@
	
clean:
	rm -f various_statistical
