# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Werror

# Target executable
TARGET = loadbalancer

# Source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
HEADERS = loadbalancer.h webserver.h

# Build executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile .cpp to .o
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony target to clean the build files
clean:
	rm -f $(OBJS) $(TARGET)

# Dependencies
$(OBJS): $(HEADERS)