#ifndef BOARD_HPP
#define BOARD_HPP

#include "Tile.hpp"
#include <vector>

namespace ariel {

class Player; 

class Board {
private:
    std::vector<std::vector<Tile>> tiles;

public:
    Board();
    void setup_board();
    void distribute_resources(int roll_result);
    void addSettlement(const std::string &resource, int number, Player &player);
    void addRoad(const std::string &resource, int number, Player &player);
    void printBoard();
};

}

#endif // BOARD_HPP
