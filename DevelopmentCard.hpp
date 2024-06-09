#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>

namespace ariel{

class Player;
class Catan;

class DevelopmentCard {
public:
    std::string type;

    DevelopmentCard(const std::string &type);
    void apply_effect(Player &player, Catan &game);
private:
    void apply_knight(Player &player, Catan &game);
    void apply_victory_point(Player &player);
    void apply_road_building(Player &player, Catan &game);
    void apply_year_of_plenty(Player &player);
    void apply_monopoly(Player &player, Catan &game);
};
}
 
#endif // DEVELOPMENTCARD_HPP