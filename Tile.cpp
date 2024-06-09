#include "Tile.hpp"

namespace ariel {

Tile::Tile(const std::string &resource, int number) : resource_type(resource), number(number) {}

void Tile::addSettlement(Player* player) {
    adjacent_settlements.push_back(player);
}

}
