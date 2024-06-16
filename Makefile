CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJS = main.o Board.o Tile.o Player.o DevelopmentCard.o Catan.o Map.o

catan: $(OBJS)
	$(CXX) $(CXXFLAGS) -o catan $(OBJS)

test: test.o Board.o Tile.o Player.o DevelopmentCard.o Catan.o Map.o
	$(CXX) $(CXXFLAGS) -o catan_test test.o Board.o Tile.o Player.o DevelopmentCard.o Catan.o Map.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

Board.o: Board.cpp Board.hpp
	$(CXX) $(CXXFLAGS) -c Board.cpp

Tile.o: Tile.cpp Tile.hpp
	$(CXX) $(CXXFLAGS) -c Tile.cpp

Player.o: Player.cpp Player.hpp
	$(CXX) $(CXXFLAGS) -c Player.cpp

DevelopmentCard.o: DevelopmentCard.cpp DevelopmentCard.hpp
	$(CXX) $(CXXFLAGS) -c DevelopmentCard.cpp

Catan.o: Catan.cpp Catan.hpp
	$(CXX) $(CXXFLAGS) -c Catan.cpp

Map.o: Map.cpp Map.hpp
	$(CXX) $(CXXFLAGS) -c Map.cpp

clean:
	rm -f *.o catan catan_test
