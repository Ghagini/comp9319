CXXFLAGS = -std=c++14 -pthread -Wall -Wno-dangling-else -O3

CXX := /usr/bin/clang++

all: bwtdecode bwtsearch

bwtencode: bwtdecode.cpp 
	$(CXX) $(CXXFLAGS) -o bwtdecode bwtdecode.cpp
bwtsearch: bwtsearch.cpp
	$(CXX) $(CXXFLAGS) -o bwtsearch bwtsearch.cpp search.cpp
