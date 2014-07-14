##
# Define all the compiler and platform specific flags
CXX = g++
CXXFLAGS = -Wall -c -std=c++11
OFLAGS = -o
LDFLAGS = -lm

# set up extra flags for explicitly setting mode
debug:	  	CXXFLAGS  += -g
release:	CXXFLAGS  += -O3

##
# Define the source and object files for the executable
SRC = $(wildcard *.cpp)
DEPS = $(wildcard *.h)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

##
# Rules for generating different objects
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $< $(OFLAGS) $@

# Link all the objects into an executable
Play: $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(OFLAGS) $@

##
# define various build modes
debug:		Play
release:	Play

clean:
	rm -f $(OBJ) Play
