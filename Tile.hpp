// efiphi10@gmail.com
#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <string>
#include <stdexcept> // For std::invalid_argument

namespace ariel {

class Player;

class Tile {
public:
    enum Resource { WOOD, BRICK, WHEAT, WOOL, ORE, DESERT };

private:
    Resource resource;
    int number;
    std::vector<Player*> players;

public:
    Tile(const Resource &res, int num);
    Resource getResource() const;
    int getNumber() const;
    void addPlayer(Player* player);
    const std::vector<Player*>& getPlayers() const;
    static Resource convertToResource(const std::string &res);
    static std::string resourceToString(Resource res); // Add this
};

}

#endif // TILE_HPP
