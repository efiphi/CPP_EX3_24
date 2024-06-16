// efiphi10@gmail.com
#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>

namespace ariel {

    class Player;
    class Catan;

    class DevelopmentCard {
    public:
        std::string type;

        DevelopmentCard(const std::string &type) : type(type) {}
        void apply_effect(Player &player, Catan &game);
    };

}

#endif // DEVELOPMENTCARD_HPP
