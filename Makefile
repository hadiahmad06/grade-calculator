# Define variables
TARGET = main
SRC = main.cpp objects.cpp
CXXFLAGS = -std=c++11

# Default rule to build the program
all: $(TARGET)

# Rule to compile the program
$(TARGET): $(SRC)
	g++ $(CXXFLAGS) -o $(TARGET) $(SRC)

# Rule to run the compiled program
test: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET)