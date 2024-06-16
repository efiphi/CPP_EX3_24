#include "Board.hpp"
#include <iostream>

namespace ariel {

Board::Board() {
    setup_board();
}

void Board::setup_board() {
    tiles = {
        {Tile::WOOD, 5}, {Tile::BRICK, 3}, {Tile::WHEAT, 10},
        {Tile::WOOD, 6}, {Tile::WHEAT, 9}, {Tile::WOOL, 11},
        {Tile::ORE, 9}, {Tile::BRICK, 8}, {Tile::WOOD, 4},
        {Tile::ORE, 10}, {Tile::WOOL, 6}, {Tile::ORE, 4},
        {Tile::WOOL, 3}, {Tile::WHEAT, 2}, {Tile::BRICK, 5},
        {Tile::WOOD, 11}, {Tile::BRICK, 8}, {Tile::WHEAT, 10},
        {Tile::DESERT, 7}
    };

    for (int i = 0; i < tiles.size(); ++i) {
        resourceTiles[tiles[i].getResource()].push_back(i);
    }
}

void Board::addSettlement(int set_id, Player &player, Map &map) {
    const auto &set = map.getSettlement(set_id);
    for (const auto &hex : set.hexagons) {
        // Log the settlement addition to the tile
        std::cout << "Settlement added to tile: " << hex.first << " " << hex.second << std::endl;
        // You may want to keep any other relevant logic here
    }
}





void Board::addRoad(const std::string &resource, int number, Player &player) {
    std::cout << "Road added to tile: " << resource << " " << number << std::endl;
}

void Board::distribute_resources(int roll) {
    for (auto &tile : tiles) {
        if (tile.getNumber() == roll) {
            for (auto *player : tile.getPlayers()) {
                player->addResource(tile.getResource(), 1);
            }
        }
    }
}

void Board::upgradeSettlementToCity(int settlementId) {
    // Logic to upgrade a settlement to a city on the board
    // This might involve updating the internal representation of the board
    std::cout << "Settlement " << settlementId << " upgraded to city." << std::endl;
}


}
