CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -O2
SRC = src/main.cpp src/database.cpp src/queryparser.cpp src/table.cpp src/record.cpp src/bplustree.cpp
TARGET = minidb

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
