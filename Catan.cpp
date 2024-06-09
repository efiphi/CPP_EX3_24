// Catan.cpp
#include "Catan.hpp"
#include <iostream>
#include <stdexcept>
#include <random>
#include <c++/11/bits/algorithmfwd.h>

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
    // Initial setup for the game
    ChooseStartingPlayer();
    // Each player places initial settlements and roads
    for (auto &player : players) {
        // Example placements; these would be determined by the players
        player.placeSettlement({"place1", "place2"}, {1, 2}, board);
        player.placeRoad({"place1", "place2"}, {1, 2}, board);
    }
}

void Catan::play_turn() {
    Player &current_player = players[current_turn];
    current_player.rollDice();
    // Player performs actions: trading, building, using development cards
    // Implementation of player actions
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
