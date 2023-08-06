# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -Wall -Wextra

# Source files
SRC := 0021_static_in_cpp.cpp 0021_static_in_cpp2.cpp
# Object files
# substitution reference $(text:pattern=replacement)
OBJ := $(SRC:.cpp=.o)
# Output executable name
EXEC := static_in_cpp

all: $(EXEC)

$(EXEC): $(OBJ) # linking rule used to create the final executable from the object file
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp      # compilation rule for generating object files from their corresponding C++ source files
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXEC)