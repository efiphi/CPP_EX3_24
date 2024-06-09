#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <map>
#include <vector>
#include "DevelopmentCard.hpp"

namespace ariel {

class Board; 
class Catan;

class Player {
public:
    std::string name;
    std::map<std::string, int> resources;
    int victory_points;
    int number_of_knights;
    std::vector<std::string> settlements;
    std::vector<std::string> cities;
    std::vector<std::string> roads;
    std::vector<DevelopmentCard> development_cards;

    Player(const std::string &name);

    void placeSettlement(const std::vector<std::string> &places, const std::vector<int> &placesNum, Board &board);
    void placeRoad(const std::vector<std::string> &places, const std::vector<int> &placesNum, Board &board);
    void rollDice(Board &board);
    void trade(Player &other, const std::string &give, const std::string &receive, int give_amount, int receive_amount);
    void buyDevelopmentCard(Catan &game);
    void useDevelopmentCard(DevelopmentCard &card, Catan &game);
    void endTurn();
    void printPoints() const;
 
private:
    DevelopmentCard getRandomDevelopmentCard();
};

}

#endif // PLAYER_HPP