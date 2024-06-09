CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

TARGET = catan
SOURCES = main.cpp Board.cpp Tile.cpp Player.cpp DevelopmentCard.cpp Catan.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

demo: Demo.cpp Board.cpp Tile.cpp Player.cpp DevelopmentCard.cpp Catan.cpp
	$(CXX) $(CXXFLAGS) Demo.cpp Board.cpp Tile.cpp Player.cpp DevelopmentCard.cpp Catan.cpp -o demo

clean:
	rm -f $(TARGET) demo *.o
