#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include "Tile.hpp"
#include "Player.hpp"
#include "Map.hpp"

namespace ariel {

class Board {
private:
    std::vector<Tile> tiles;
    std::map<Tile::Resource, std::vector<int>> resourceTiles;

public:
    Board();
    void setup_board();
    void addSettlement(int set_id, Player &player, Map &map);
    void addRoad(const std::string &resource, int number, Player &player);
    void distribute_resources(int roll);
    void upgradeSettlementToCity(int settlementId);
};

}

#endif // BOARD_HPP
