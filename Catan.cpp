#include "Catan.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <c++/11/bits/algorithmfwd.h>

namespace ariel{

Catan::Catan(Player &p1, Player &p2, Player &p3) : players({p1, p2, p3}), current_turn(0) {}

void Catan::ChooseStartingPlayer() {
    // Randomly choose a starting player
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(players.begin(), players.end(), g);
    std::cout << "Starting player: " << players[0].name << std::endl;
}

Board Catan::getBoard() const {
    return board;
}

void Catan::start_game() {
    ChooseStartingPlayer();
    for (auto &player : players) {
        // Example placements for the first settlement and road
        player.placeSettlement({"wood", "brick"}, {8, 3}, board);
        player.placeRoad({"wood", "brick"}, {8, 3}, board);
        
        // Example placements for the second settlement and road
        player.placeSettlement({"wheat", "wool"}, {5, 4}, board);
        player.placeRoad({"wheat", "wool"}, {5, 4}, board);
        
        // Give initial resources based on these placements
        player.resources["wood"]++;
        player.resources["brick"]++;
        player.resources["wheat"]++;
        player.resources["wool"]++;
        std::cout << player.name << " receives initial resources: 1 wood, 1 brick, 1 wheat, 1 wool" << std::endl;
    }
}


void Catan::play_turn() {
    Player &current_player = players[current_turn];
    std::cout << "It's " << current_player.name << "'s turn." << std::endl;
    current_player.rollDice(board);
    
    // Additional actions could be added here such as trading, building, etc.
    
    current_player.endTurn();
    current_turn = (current_turn + 1) % players.size();
    check_winner();
}


void Catan::check_winner() {
    for (const auto &player : players) {
        if (player.victory_points >= 10) {
            std::cout << "Winner: " << player.name << std::endl;
            exit(0); // End the game
        }
    }
}

void Catan::printWinner() {
    std::cout << "No winner yet." << std::endl;
}

void Catan::handle_development_card(Player &player, DevelopmentCard &card) {
    card.apply_effect(player, *this);
}
}