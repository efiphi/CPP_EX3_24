#ifndef TILE_HPP
#define TILE_HPP

#include <string>
#include <vector>

class Player; // Forward declaration of Player class

class Tile {
public:
    std::string resource_type;
    int number;
    std::vector<Player*> adjacent_settlements; // Add adjacent_settlements

    Tile(const std::string &resource, int number);
    void addSettlement(Player* player);
};

#endif // TILE_HPP
