#include "Board.hpp"
#include "Player.hpp"
#include <iostream>
#include <algorithm>
#include <random>

namespace ariel {

Board::Board() {
    setup_board();
}

void Board::setup_board() {
    std::vector<Tile> all_tiles = {
        {"wood", 8}, {"wood", 2}, {"wood", 9}, {"wood", 11},
        {"brick", 3}, {"brick", 6}, {"brick", 12},
        {"wheat", 5}, {"wheat", 8}, {"wheat", 10}, {"wheat", 5},
        {"wool", 4}, {"wool", 6}, {"wool", 4}, {"wool", 11},
        {"iron", 9}, {"iron", 3}, {"iron", 10},
        {"desert", 0}
    };

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(all_tiles.begin(), all_tiles.end(), g);

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
                for (auto &settlement : tile.adjacent_settlements) {
                    settlement->resources[tile.resource_type]++;
                    std::cout << settlement->name << " receives " << tile.resource_type << " from tile " << tile.number << std::endl;
                }
            }
        }
    }
}

void Board::addSettlement(const std::string &resource, int number, Player &player) {
    for (auto &row : tiles) {
        for (auto &tile : row) {
            if (tile.resource_type == resource && tile.number == number) {
                tile.addSettlement(&player);
                return;
            }
        }
    }
}
 
void Board::addRoad(const std::string &resource, int number, Player &player) {
    // Implementation for adding a road (simplified)
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

}
 