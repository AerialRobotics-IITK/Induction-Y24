CXX = g++
CXXFLAGS = -std=c++17 -Wall
SOURCES = main.cpp user.cpp admin.cpp content.cpp persistence.cpp init_content.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = Netflix

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
