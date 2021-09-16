GXX = g++
GXXFLAGS = -g -O0 -std=c++17 -Wall

SOURCE = read.cc eval.cc main.cc $(wildcard asmjit/x86/*.cpp) $(wildcard asmjit/core/*.cpp)
OBJS = $(SOURCE=.cc.o)
HEADER = ischeme.hh

main : $(SOURCE) $(HEADER)
	$(GXX) $(GXXFLAGS) -DASMJIT_EMBED -o $@ $(SOURCE) -lrt

readertest : testreader.cc $(SOURCE) $(HEADER)
	$(GXX) $(GXXFLAGS) -o $@ testreader.cc $(SOURCE)
