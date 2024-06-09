// Board.cpp
#include "Board.hpp"
#include <iostream>
#include <algorithm>
#include <random>

Board::Board() {
    setup_board();
}

void Board::setup_board() {
    // Define the tiles with resources and numbers
    std::vector<Tile> all_tiles = {
        {"wood", 8}, {"wood", 2}, {"wood", 9}, {"wood", 11},
        {"brick", 3}, {"brick", 6}, {"brick", 12},
        {"wheat", 5}, {"wheat", 8}, {"wheat", 10}, {"wheat", 5},
        {"wool", 4}, {"wool", 6}, {"wool", 4}, {"wool", 11},
        {"iron", 9}, {"iron", 3}, {"iron", 10},
        {"desert", 0} // Desert does not have a number
    };

    // Shuffle the tiles
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(all_tiles.begin(), all_tiles.end(), g);

    // Assign the shuffled tiles to the board
    tiles = {
        {{"sea", 0}, {"sea", 0}, {"sea", 0}, {"sea", 0}, {"sea", 0}},
        {{"sea", 0}, all_tiles[0], all_tiles[1], all_tiles[2], {"sea", 0}},
        {{"sea", 0}, all_tiles[3], all_tiles[4], all_tiles[5], all_tiles[6], {"sea", 0}},
        {{"sea", 0}, all_tiles[7], all_tiles[8], all_tiles[9], all_tiles[10], all_tiles[11], {"sea", 0}},
        {{"sea", 0}, all_tiles[12], all_tiles[13], all_tiles[14], all_tiles[15], {"sea", 0}},
        {{"sea", 0}, all_tiles[16], all_tiles[17], all_tiles[18], {"sea", 0}},
        {{"sea", 0}, {"sea", 0}, {"sea", 0}, {"sea", 0}, {"sea", 0}}
    };
}

void Board::distribute_resources(int roll_result) {
    for (auto &row : tiles) {
        for (auto &tile : row) {
            if (tile.number == roll_result) {
                // Distribute resources to players with settlements on this tile
                for (auto &settlement : tile.adjacent_settlements) {
                    settlement->owner->resources[tile.resource_type]++;
                    std::cout << settlement->owner->name << " receives " << tile.resource_type << std::endl;
                }
            }
        }
    }
}

void Board::printBoard() {
    std::cout << "********** CATAN BOARD **********\n";
    for (const auto &row : tiles) {
        for (const auto &tile : row) {
            if (tile.resource_type == "sea") {
                std::cout << " sea ";
            } else {
                std::cout << tile.resource_type << " " << tile.number << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "*********************************\n";
}
