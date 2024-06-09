#ifndef BOARD_HPP
#define BOARD_HPP

#include "Tile.hpp"
#include <vector>

class Board {
private:
    std::vector<std::vector<Tile>> tiles;

public:
    Board();
    void setup_board();
    void distribute_resources(int roll_result);
    void printBoard();
};

#endif // BOARD_HPP
