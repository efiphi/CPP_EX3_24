#include "Catan.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

namespace ariel {

Catan::Catan() : players{Player("Amit"), Player("Yossi"), Player("Dana")}, current_turn(0) {
    board.setup_board();
}

Catan::Catan(Player &p1, Player &p2, Player &p3) : players{p1, p2, p3}, current_turn(0) {
    board.setup_board();
}

void Catan::ChooseStartingPlayer() {
    std::cout << "Starting player: " << players[0].getName() << std::endl;
}

Board& Catan::getBoard() {
    return board;
}

void Catan::start_game() {
    std::cout << "Starting the game..." << std::endl;
    ChooseStartingPlayer();
}

void Catan::play_turn() {
    Player& player = players[current_turn];
    std::cout << "Turn " << current_turn + 1 << ": " << player.getName() << "'s turn." << std::endl;
    int roll = rollDice();
    std::cout << player.getName() << " rolled a " << roll << std::endl;
    board.distribute_resources(roll);
    performPlayerActions(player);
    check_winner();
    current_turn = (current_turn + 1) % players.size();
}

void Catan::check_winner() {
    for (const auto& player : players) {
        if (player.getVictoryPoints() >= 10) {
            printWinner();
            exit(0); // End game
        }
    }
}

void Catan::printWinner() {
    for (const auto& player : players) {
        if (player.getVictoryPoints() >= 10) {
            std::cout << player.getName() << " wins the game with " << player.getVictoryPoints() << " points!" << std::endl;
        }
    }
}

void Catan::handle_development_card(Player &player, DevelopmentCard &card) {
    // Handle development card logic
}

std::vector<Player>& Catan::getPlayers() {
    return players;
}

int Catan::rollDice() const {
    srand(static_cast<unsigned int>(time(0)));
    return (rand() % 6 + 1) + (rand() % 6 + 1); // Simulate rolling two six-sided dice
}

void Catan::performPlayerActions(Player &player) {
    // Implement actions a player can take on their turn
    // Example: buying development cards, placing settlements, etc.
    try {
        player.buyDevelopmentCard(*this);
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

}
