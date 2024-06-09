#include "Player.hpp"
#include "Board.hpp"
#include <iostream>
#include <stdexcept>
#include <random>

Player::Player(const std::string &name) : name(name), victory_points(0), number_of_knights(0) {}

void Player::placeSettlement(const std::vector<std::string> &places, const std::vector<int> &placesNum, Board &board) {
    // Ensure the places and placesNum vectors have the same size
    if (places.size() != placesNum.size()) {
        throw std::invalid_argument("Places and placesNum vectors must be of the same size.");
    }

    // Place settlements on the board
    for (size_t i = 0; i < places.size(); ++i) {
        // Implementation logic to place settlement on the board
        // This could involve checking if the tile is available and then placing the settlement
        settlements.push_back(places[i] + std::to_string(placesNum[i]));
        board.addSettlement(places[i], placesNum[i], *this);
    }

    // Increase victory points for placing a settlement
    victory_points += places.size();
}

void Player::placeRoad(const std::vector<std::string> &places, const std::vector<int> &placesNum, Board &board) {
    // Ensure the places and placesNum vectors have the same size
    if (places.size() != placesNum.size()) {
        throw std::invalid_argument("Places and placesNum vectors must be of the same size.");
    }

    // Place roads on the board
    for (size_t i = 0; i < places.size(); ++i) {
        // Implementation logic to place road on the board
        // This could involve checking if the road placement is valid and then placing the road
        roads.push_back(places[i] + std::to_string(placesNum[i]));
        board.addRoad(places[i], placesNum[i], *this);
    }
}

void Player::rollDice(Board &board) {
    // Simulate rolling two six-sided dice
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    int roll_result = dis(gen) + dis(gen);
    std::cout << name << " rolled a " << roll_result << std::endl;

    // Distribute resources based on the roll result
    board.distribute_resources(roll_result);
}

void Player::trade(Player &other, const std::string &give, const std::string &receive, int give_amount, int receive_amount) {
    if (resources[give] < give_amount || other.resources[receive] < receive_amount) {
        throw std::invalid_argument("Not enough resources for trade.");
    }

    resources[give] -= give_amount;
    resources[receive] += receive_amount;

    other.resources[give] += give_amount;
    other.resources[receive] -= receive_amount;

    std::cout << name << " traded " << give_amount << " " << give << " for " << receive_amount << " " << receive << " with " << other.name << std::endl;
}

void Player::buyDevelopmentCard() {
    if (resources["wheat"] < 1 || resources["wool"] < 1 || resources["iron"] < 1) {
        throw std::invalid_argument("Not enough resources to buy a development card.");
    }

    resources["wheat"]--;
    resources["wool"]--;
    resources["iron"]--;

    // Assume we have a function to randomly select a development card
    DevelopmentCard card = getRandomDevelopmentCard();
    development_cards.push_back(card);

    std::cout << name << " bought a development card: " << card.type << std::endl;

    // Use the development card immediately
    useDevelopmentCard(card);
}

void Player::useDevelopmentCard(DevelopmentCard &card) {
    card.apply_effect(*this, *game); // Apply the card's effect
}

void Player::endTurn() {
   std::cout << name << " ends their turn." << std::endl;
}

void Player::printPoints() const {
    std::cout << name << " has " << victory_points << " points." << std::endl;
}
