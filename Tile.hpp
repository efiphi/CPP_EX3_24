#ifndef TILE_HPP
#define TILE_HPP

#include <string>
#include <vector>

namespace ariel {

class Player; 

class Tile {
public:
    std::string resource_type;
    int number;
    std::vector<Player*> adjacent_settlements;

    Tile(const std::string &resource, int number);
    void addSettlement(Player* player);
};

}
 
#endif // TILE_HPP