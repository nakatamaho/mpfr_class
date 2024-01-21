CXX = g++-12
CXXFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lmpfr
INCLUDES = -I/usr/include

TARGET = mpfr_test

SOURCES = test_mpfr_class.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
