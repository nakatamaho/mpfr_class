CXX = g++-12
CXXFLAGS = -Wall -Wextra
LDFLAGS = -L/home/docker/mpfr_class/i/GMP-6.3.0/lib -L/home/docker/mpfr_class/i/MPFR-4.2.1/lib -lgmp -lmpfr
INCLUDES = -I/home/docker/mpfr_class/i/GMP-6.3.0/include -I/home/docker/mpfr_class/i/MPFR-4.2.1/include -I/home/docker/mpfr_class/i/MPC-1.3.1/include

TARGET = test_mpfr_class
EXAMPLES = example01 example02

SOURCES = test_mpfr_class.cpp
HEADERS = mpfr_class.h
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET) $(EXAMPLES)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

$(EXAMPLES):
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ examples/$@.cpp $(LDFLAGS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

clean:
	rm -f $(TARGET) $(EXAMPLES) $(OBJECTS) *~

.PHONY: all clean
