CXX=g++
VER=-std=c++20
CFLAGS=
LIBS=-lcurl
SRC=$(wildcard *.cpp)
OBJS=$(SRC:%.cpp=%.o)
EXE=fenParser

$(EXE) : $(OBJS)
	$(CXX) $(VER) $(CFLAGS) $(OBJS) -o $(EXE) $(LIBS)

%.o : %.cpp
	$(CXX) $(VER) $(CFLAGS) -c $< -o $@ $(LIBS)

clean :
	rm -f $(EXE) $(OBJS)


