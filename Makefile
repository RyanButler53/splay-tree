CXX = clang++
CXXFLAGS = -std=c++2a -g -Wall -pedantic
SRC = $(wildcard splayTree*.hpp)
EXECS = $(wildcard *.cpp)
TARGET = $(EXECS:.cpp=)

all: $(TARGET)

$(EXECS:.cpp=): $(EXECS:.cpp=.o)
	$(CXX) -o $@ $<

$(EXECS:.cpp=.o): $(EXECS) $(SRC)
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -rf $(TARGET) *.o
	