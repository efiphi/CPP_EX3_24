#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Tile.hpp"
#include "DevelopmentCard.hpp"
#include "Map.hpp"
#include <string>
#include <vector>
#include <unordered_map>

namespace ariel {

class Board;
class Catan;

class Player {
private:
    std::string name;
    int victory_points;
    int number_of_knights;
    std::unordered_map<std::string, int> resources;
    std::vector<int> settlements; // Store settlement IDs instead of resource strings
    std::vector<std::string> roads;
    std::vector<DevelopmentCard> development_cards;
    bool initialPlacement;

public:
    Player(const std::string &name);
    
    void addResource(ariel::Tile::Resource resource, int quantity);
    bool removeResource(ariel::Tile::Resource resource, int quantity);
    int getResourceCount(ariel::Tile::Resource resource) const;
    std::string getName() const;
    void placeSettlement(int set_id, Map &map, Board &board);
    void placeRoad(const std::vector<std::pair<std::string, int>> &places, Board &board);
    void rollDice(Board &board);
    void trade(Player &other, const std::string &give, const std::string &receive, int give_amount, int receive_amount);
    void buyDevelopmentCard(Catan &game);
    void useDevelopmentCard(DevelopmentCard &card, Catan &game);
    void endTurn();
    void printPoints() const;
    void displayResources() const;
    DevelopmentCard getRandomDevelopmentCard();
    std::vector<int> getSettlements() const;
    bool hasAdjacentRoad(const std::string &place, int placeNum);
    ariel::Tile::Resource convertToResource(const std::string &resource);
    void addVictoryPoint();
    int getVictoryPoints() const;
    void displaySettlements(const Map &map) const; // New method to display settlements
};

}

#endif // PLAYER_HPP
