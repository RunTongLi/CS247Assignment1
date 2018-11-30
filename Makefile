CXX = g++ -std=c++14
CXXFLAGS = -Wall -O -g -MMD   `pkg-config --cflags gtkmm-3.0`    # -lasan -O -g -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer        # use -MMD to generate dependencies
IFLAGS = -I$(HOME)/.local/include
LDFLAGS=`pkg-config --libs gtkmm-3.0`
SOURCES = $(wildcard *.cpp)  # list of all .cpp files in the current directory
OBJECTS = $(SOURCES:.cpp=.o) # .o files depend upon .cpp files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cpp file
EXEC=straights

# First target in the makefile is the default target.
# Note that the LIBFLAGS must come last in the command
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(IFLAGS) $(LDFLAGS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
