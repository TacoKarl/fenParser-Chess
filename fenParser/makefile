CXX=g++
VER=-std=c++20
CFLAGS=-Iinclude
LIBS=-lcurl
SRC=$(wildcard src/*.cpp)
OBJS=$(SRC:src/%.cpp=build/%.o)
EXE=bin/fenParser

$(EXE) : $(OBJS) | bin
	$(CXX) $(VER) $(CFLAGS) $(OBJS) -o $(EXE) $(LIBS)

build/%.o : src/%.cpp include/*.h | build
	$(CXX) $(VER) $(CFLAGS) -c $< -o $@ $(LIBS)

build :
	mkdir -p build

bin :
	mkdir -p bin

clean :
	rm -rf $(EXE) build
