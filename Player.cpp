#include "Player.hpp"
#include "Board.hpp"
#include <iostream>
#include <stdexcept>
#include <random>

namespace ariel {

Player::Player(const std::string &name) : name(name), victory_points(0), number_of_knights(0) {}

void Player::placeSettlement(const std::vector<std::string> &initialPlaces, const std::vector<int> &initialPlacesNum, Board &board) {
    if (initialPlaces.size() != initialPlacesNum.size()) {
        throw std::invalid_argument("Places and placesNum vectors must be of the same size.");
    }

    for (size_t i = 0; i < initialPlaces.size(); ++i) {
        std::string place = initialPlaces[i];
        int placeNum = initialPlacesNum[i];
        std::string settlement = place + std::to_string(placeNum);

        bool placed = false;
        while (!placed) {
            bool occupied = false;
            for (const auto& existing_settlement : settlements) {
                if (existing_settlement == settlement) {
                    occupied = true;
                    break;
                }
            }
            if (!occupied) {
                settlements.push_back(settlement);
                board.addSettlement(place, placeNum, *this);
                placed = true;
            } else {
                std::cout << "Tile " << place << " " << placeNum << " is already occupied. Choosing a different tile automatically." << std::endl;
                placeNum = (placeNum % 12) + 1;  // Automatically choose the next tile number
                settlement = place + std::to_string(placeNum);
            }
        }
    }

    victory_points += initialPlaces.size();
    std::cout << name << " chooses ";
    for (size_t i = 0; i < initialPlaces.size(); ++i) {
        std::cout << initialPlaces[i] << " " << initialPlacesNum[i];
        if (i != initialPlaces.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "." << std::endl;
}



void Player::placeRoad(const std::vector<std::string> &places, const std::vector<int> &placesNum, Board &board) {
    if (places.size() != placesNum.size()) {
        throw std::invalid_argument("Places and placesNum vectors must be of the same size.");
    }

    for (size_t i = 0; i < places.size(); ++i) {
        roads.push_back(places[i] + std::to_string(placesNum[i]));
        board.addRoad(places[i], placesNum[i], *this);
    }
}

void Player::rollDice(Board &board) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    int roll_result = dis(gen) + dis(gen);
    std::cout << name << " rolled a " << roll_result << std::endl;

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

void Player::buyDevelopmentCard(Catan &game) {
    if (resources["wheat"] < 1 || resources["wool"] < 1 || resources["iron"] < 1) {
        std::cout << name << " does not have enough resources to buy a development card." << std::endl;
        throw std::invalid_argument("Not enough resources to buy a development card.");
    }

    resources["wheat"]--;
    resources["wool"]--;
    resources["iron"]--;

    DevelopmentCard card = getRandomDevelopmentCard();
    development_cards.push_back(card);

    std::cout << name << " bought a development card: " << card.type << std::endl;

    useDevelopmentCard(card, game);
}


void Player::useDevelopmentCard(DevelopmentCard &card, Catan &game) {
    card.apply_effect(*this, game); // Apply the card's effect
}

void Player::endTurn() {
    std::cout << name << " ends their turn." << std::endl;
}

void Player::printPoints() const {
    std::cout << name << " has " << victory_points << " points." << std::endl;
}

DevelopmentCard Player::getRandomDevelopmentCard() {
    std::vector<std::string> card_types = {"knight", "victory point", "road building", "year of plenty", "monopoly"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, card_types.size() - 1);
    std::string type = card_types[dis(gen)];
    return DevelopmentCard(type);
}

}
