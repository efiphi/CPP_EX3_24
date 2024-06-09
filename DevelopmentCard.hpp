#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>

class Player;
class Catan;

class DevelopmentCard {
public:
    std::string type;

    DevelopmentCard(const std::string &type);
    void apply_effect(Player &player, Catan &game);
};

#endif // DEVELOPMENTCARD_HPP
