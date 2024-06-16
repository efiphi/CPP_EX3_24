// efiphi10@gmail.com
#include "Tile.hpp"

namespace ariel {

Tile::Tile(const Resource &res, int num) : resource(res), number(num) {}

void Tile::addPlayer(Player *player) {
    players.push_back(player);
}

Tile::Resource Tile::getResource() const {
    return resource;
}

int Tile::getNumber() const {
    return number;
}

const std::vector<Player*>& Tile::getPlayers() const { 
    return players;
}

Tile::Resource Tile::convertToResource(const std::string &res) {
    if (res == "wood") return Tile::WOOD;
    if (res == "brick") return Tile::BRICK;
    if (res == "wheat") return Tile::WHEAT;
    if (res == "wool") return Tile::WOOL;
    if (res == "ore") return Tile::ORE;
    if (res == "desert") return Tile::DESERT;
    throw std::invalid_argument("Invalid resource: " + res);
}

std::string Tile::resourceToString(Resource res) {
    switch(res) {
        case WOOD: return "wood";
        case BRICK: return "brick";
        case WHEAT: return "wheat";
        case WOOL: return "wool";
        case ORE: return "ore";
        case DESERT: return "desert";
        default: throw std::invalid_argument("Invalid resource");
    }
}

}
