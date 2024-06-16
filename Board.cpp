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
        Tile::Resource res_enum = Tile::convertToResource(hex.first);
        for (auto &tile : tiles) {
            if (tile.getResource() == res_enum && tile.getNumber() == hex.second) {
                tile.addPlayer(&player);
                player.addResource(res_enum, 1);
            }
        }
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

}
