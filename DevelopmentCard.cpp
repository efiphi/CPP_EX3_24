// efiphi10@gmail.com
#include "DevelopmentCard.hpp"
#include "Player.hpp"
#include "Catan.hpp"
#include <iostream>

namespace ariel {


    void DevelopmentCard::apply_effect(Player &player, Catan &game) {
        if (type == "knight") {
            std::cout << player.getName() << " played a Knight card." << std::endl;
            player.addVictoryPoint();
        } else if (type == "victory point") {
            std::cout << player.getName() << " gained a Victory Point card." << std::endl;
            player.addVictoryPoint();
        } else if (type == "road building") {
            std::cout << player.getName() << " played a Road Building card. Add roads manually for now." << std::endl;
        } else if (type == "year of plenty") {
            std::cout << player.getName() << " played a Year of Plenty card. Add resources manually for now." << std::endl;
        } else if (type == "monopoly") {
            std::cout << player.getName() << " played a Monopoly card. Implement resource collection manually." << std::endl;
        }
    }

}
