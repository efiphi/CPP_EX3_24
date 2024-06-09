#include "DevelopmentCard.hpp"
#include "Player.hpp"
#include "Catan.hpp"

DevelopmentCard::DevelopmentCard(const std::string &type) : type(type) {}

void DevelopmentCard::apply_effect(Player &player, Catan &game) {
     if (type == "knight") {
        player.number_of_knights++;
        if (player.number_of_knights == 3) {
            player.victory_points += 2;
        }
    } else if (type == "victory point") {
        player.victory_points++;
    } else if (type == "road building") {
        // Allow the player to build two roads immediately
    } else if (type == "year of plenty") {
        // Allow the player to choose two resources from the bank
    } else if (type == "monopoly") {
        // Allow the player to choose a resource and take all of that resource from other players
    }
}

