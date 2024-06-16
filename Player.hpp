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
    int victory_points=0;
    int number_of_knights=0;
    int roadCount=0;
    std::map<std::string, int> resources; 
    std::vector<int> settlements; 
    std::vector<int> cities;
    int cityCount=0;
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
    void buySettlement(int settlementId, Map& map, Board& board);
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
    void yearOfPlenty(ariel::Tile::Resource resource1, ariel::Tile::Resource resource2);
    void roadBuilding(const std::vector<std::pair<std::string, int>>& places1, const std::vector<std::pair<std::string, int>>& places2, Board& board);
    void gainVictoryPoint();
    void monopoly(ariel::Tile::Resource resource, std::vector<Player>& otherPlayers);
    void playKnight(std::vector<Player>& otherPlayers);
    

    int getKnightCount() const;
    int getRoadCount() const;
    void buyCity(int settlementId, Board& board);
    int getCityCount() const;
};

}

#endif // PLAYER_HPP
