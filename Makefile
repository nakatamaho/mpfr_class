CXX = g++-12
CXXFLAGS = -Wall -Wextra
LDFLAGS = -L/home/docker/mpfr_class/i/GMP-6.3.0/lib -L/home/docker/mpfr_class/i/MPFR-4.2.1/lib -lgmp -lmpfr -Wl,-rpath=/home/docker/mpfr_class/i/MPFR-4.2.1/lib -Wl,-rpath=/home/docker/mpfr_class/i/GMP-6.3.0/lib
INCLUDES = -I/home/docker/mpfr_class/i/GMP-6.3.0/include -I/home/docker/mpfr_class/i/MPFR-4.2.1/include -I/home/docker/mpfr_class/i/MPC-1.3.1/include

TARGET = test_mpfr_class
EXAMPLES_DIR = examples
EXAMPLES = $(addprefix $(EXAMPLES_DIR)/,example01 example02 example03 example04)

SOURCES = test_mpfr_class.cpp
HEADERS = mpfr_class.h
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET) $(EXAMPLES)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

$(EXAMPLES_DIR)/%: $(EXAMPLES_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LDFLAGS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TARGET) $(EXAMPLES) $(OBJECTS) $(EXAMPLES_DIR)/*~ *~

.PHONY: all clean
