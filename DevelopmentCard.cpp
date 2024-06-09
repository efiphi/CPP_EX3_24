// DevelopmentCard.cpp
#include "DevelopmentCard.hpp"
#include "Player.hpp"
#include "Catan.hpp"
#include <iostream>

namespace ariel{

DevelopmentCard::DevelopmentCard(const std::string &type) : type(type) {}

void DevelopmentCard::apply_effect(Player &player, Catan &game) {
    if (type == "knight") {
        DevelopmentCard :: apply_knight(player, game);
    } else if (type == "victory point") {
        apply_victory_point(player);
    } else if (type == "road building") {
        apply_road_building(player, game);
    } else if (type == "year of plenty") {
        apply_year_of_plenty(player);
    } else if (type == "monopoly") {
        apply_monopoly(player, game);
    }
}

void DevelopmentCard::apply_knight(Player &player, Catan & /*game*/) {
    player.number_of_knights++;
    if (player.number_of_knights == 3) {
        player.victory_points += 2;
    }
    std::cout << player.name << " played a Knight card." << std::endl;
}

void DevelopmentCard::apply_victory_point(Player &player) {
    player.victory_points++;
    std::cout << player.name << " gained a Victory Point card." << std::endl;
}

void DevelopmentCard::apply_road_building(Player &player, Catan & /*game*/) {
    // Allow the player to build two roads immediately
    std::cout << player.name << " played a Road Building card." << std::endl;
    // Logic to build two roads
}

void DevelopmentCard::apply_year_of_plenty(Player &player) {
    // Allow the player to choose two resources from the bank
    std::cout << player.name << " played a Year of Plenty card." << std::endl;
    // Logic to choose two resources
}

void DevelopmentCard::apply_monopoly(Player &player, Catan & /*game*/) {
    // Allow the player to choose a resource and take all of that resource from other players
    std::cout << player.name << " played a Monopoly card." << std::endl;
    // Logic to take all of a chosen resource from other players
}
}
