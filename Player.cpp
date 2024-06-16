#include "Player.hpp"
#include "Board.hpp"
#include "Catan.hpp"
#include "Tile.hpp"
#include <iostream>
#include <stdexcept>
#include <random>
#include <algorithm>

namespace ariel {

    Player::Player(const std::string &name) : name(name), victory_points(0), number_of_knights(0), initialPlacement(true) {
        resources["wood"] = 0;
        resources["brick"] = 0;
        resources["wheat"] = 0;
        resources["wool"] = 0;
        resources["ore"] = 0;
    }

   void Player::addResource(ariel::Tile::Resource resource, int quantity) {
    switch(resource) {
        case ariel::Tile::WOOD:
            resources["wood"] += quantity;
            break;
        case ariel::Tile::BRICK:
            resources["brick"] += quantity;
            break;
        case ariel::Tile::WHEAT:
            resources["wheat"] += quantity;
            break;
        case ariel::Tile::WOOL:
            resources["wool"] += quantity;
            break;
        case ariel::Tile::ORE:
            resources["ore"] += quantity;
            break;
        default:
            break;
        }
    }


   bool Player::removeResource(ariel::Tile::Resource resource, int quantity) {
    switch(resource) {
        case ariel::Tile::WOOD:
            if (resources["wood"] >= quantity) {
                resources["wood"] -= quantity;
                return true;
            }
            break;
        case ariel::Tile::BRICK:
            if (resources["brick"] >= quantity) {
                resources["brick"] -= quantity;
                return true;
            }
            break;
        case ariel::Tile::WHEAT:
            if (resources["wheat"] >= quantity) {
                resources["wheat"] -= quantity;
                return true;
            }
            break;
        case ariel::Tile::WOOL:
            if (resources["wool"] >= quantity) {
                resources["wool"] -= quantity;
                return true;
            }
            break;
        case ariel::Tile::ORE:
            if (resources["ore"] >= quantity) {
                resources["ore"] -= quantity;
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}



    int Player::getResourceCount(ariel::Tile::Resource resource) const {
        switch(resource) {
            case ariel::Tile::WOOD:
                return resources.at("wood");
            case ariel::Tile::BRICK:
                return resources.at("brick");
            case ariel::Tile::WHEAT:
                return resources.at("wheat");
            case ariel::Tile::WOOL:
                return resources.at("wool");
            case ariel::Tile::ORE:
                return resources.at("ore");
            default:
                return 0;
        }
    }

    std::string Player::getName() const {
        return name;
    }

    void Player::placeSettlement(int set_id, Map &map, Board &board) {
    const auto &set = map.getSettlement(set_id);
    for (const auto &hex : set.hexagons) {
        Tile::Resource res_enum = convertToResource(hex.first);
        addResource(res_enum, 1);  // Add the resource from each hex in the settlement
    }
    board.addSettlement(set_id, *this, map);  // Ensure the board adds the settlement correctly
    settlements.push_back(set_id);
    addVictoryPoint();
    }

    void Player::buySettlement(int settlementId, Map& map, Board& board) {
    // Check if the player has enough resources
    if (removeResource(Tile::BRICK, 1) && 
        removeResource(Tile::WOOD, 1) && 
        removeResource(Tile::WHEAT, 1) && 
        removeResource(Tile::WOOL, 1)) {
        
        // Place the settlement
        settlements.push_back(settlementId);
        victory_points++;
        std::cout << "Settlement added to tile: " << settlementId << std::endl;
    } else {
        // If the player does not have enough resources, revert the resource removal
        addResource(Tile::BRICK, 1);
        addResource(Tile::WOOD, 1);
        addResource(Tile::WHEAT, 1);
        addResource(Tile::WOOL, 1);
        std::cerr << "Not enough resources to buy a settlement." << std::endl;
    }
}




    void Player::placeRoad(const std::vector<std::pair<std::string, int>> &places, Board &board) {
        for (const auto &place : places) {
            std::string road = place.first + " " + std::to_string(place.second);
            roads.push_back(road);
            board.addRoad(place.first, place.second, *this);
            
        }
        roadCount++;
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
        if (resources["wheat"] < 1 || resources["wool"] < 1 || resources["ore"] < 1) {
            std::cerr << "Error: Not enough resources to buy a development card." << std::endl;
        return;

        resources["wheat"]--;
        resources["wool"]--;
        resources["ore"]--;

        DevelopmentCard card = getRandomDevelopmentCard();
        development_cards.push_back(card);

        std::cout << name << " bought a development card: " << card.type << std::endl;

        useDevelopmentCard(card, game);
    }
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

    void Player::displayResources() const {
        std::cout << name << "'s resources: ";
        for (const auto& resource : resources) {
            std::cout << resource.first << ": " << resource.second << " ";
        }
        std::cout << std::endl;
    }

    DevelopmentCard Player::getRandomDevelopmentCard() {
        std::vector<std::string> card_types = {"knight", "victory point", "road building", "year of plenty", "monopoly"};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, card_types.size() - 1);
        std::string type = card_types[dis(gen)];
        return DevelopmentCard(type);
    }

    std::vector<int> Player::getSettlements() const {
        return settlements;
    }

    bool Player::hasAdjacentRoad(const std::string &place, int placeNum) {
        std::string road = place + std::to_string(placeNum);
        for (const auto& existing_road : roads) {
            if (existing_road == road) {
                return true;
            }
        }
        return false;
    }

    ariel::Tile::Resource Player::convertToResource(const std::string &resource) {
        if (resource == "wood") return ariel::Tile::WOOD;
        if (resource == "brick") return ariel::Tile::BRICK;
        if (resource == "wheat") return ariel::Tile::WHEAT;
        if (resource == "wool") return ariel::Tile::WOOL;
        if (resource == "ore") return ariel::Tile::ORE;
        throw std::invalid_argument("Invalid resource: " + resource);
    }

    void Player::addVictoryPoint() {
        victory_points++;
    }

    int Player::getVictoryPoints() const {
        return victory_points;
    }

    void Player::displaySettlements(const Map &map) const {
        std::cout << name << "'s settlements:" << std::endl;
        for (const int set_id : settlements) {
            const auto &set = map.getSettlement(set_id);
            std::cout << "Settlement ID " << set_id << " includes hexagons: ";
            for (const auto &hex : set.hexagons) {
                std::cout << hex.first << " " << hex.second << ", ";
            }
            std::cout << std::endl;
        }
    }

    void Player::yearOfPlenty(ariel::Tile::Resource resource1, ariel::Tile::Resource resource2) {
    addResource(resource1, 1);
    addResource(resource2, 1);
    }

    void Player::roadBuilding(const std::vector<std::pair<std::string, int>>& places1, const std::vector<std::pair<std::string, int>>& places2, Board& board) {
    placeRoad(places1, board);
    placeRoad(places2, board);
    }

    void Player::gainVictoryPoint() {
    victory_points++;
    }

    void Player::monopoly(ariel::Tile::Resource resource, std::vector<Player>& otherPlayers) {
    int totalResource = 0;
        for (auto& player : otherPlayers) {
            if (player.getName() != this->name) {
            int playerResourceCount = player.getResourceCount(resource);
            std::cout << "Player " << player.getName() << " has " << playerResourceCount << " of resource " << resource << std::endl;
                if (playerResourceCount > 0) {
                bool result = player.removeResource(resource, playerResourceCount); // Use removeResource method
                    if (result) {
                    totalResource += playerResourceCount;
                    }
                std::cout << "Player " << player.getName() << " after removal has " << player.getResourceCount(resource) << " of resource " << resource << std::endl;
                }
            }
        }
    addResource(resource, totalResource);
    std::cout << "Total resources collected: " << totalResource << std::endl;
    }





    void Player::playKnight(std::vector<Player>& otherPlayers) {
    number_of_knights++;
    if (number_of_knights >= 3) {
        gainVictoryPoint();
        gainVictoryPoint();
    }
    }

    int Player::getKnightCount() const {
    return number_of_knights;
    }

    int Player::getRoadCount() const {
    return roadCount;
    }

    void Player::buyCity(int settlementId, Board& board) {
    // Check if the player has the settlement
    auto it = std::find(settlements.begin(), settlements.end(), settlementId);
    if (it != settlements.end()) {
        // Check if the player has enough resources to buy a city (e.g., 3 ore and 2 wheat)
        bool hasEnoughOre = removeResource(Tile::ORE, 3);
        bool hasEnoughWheat = removeResource(Tile::WHEAT, 2);

        if (hasEnoughOre && hasEnoughWheat) {
            // Upgrade settlement to city
            settlements.erase(it);
            cities.push_back(settlementId);
            cityCount++;
            victory_points++; // Increment victory points for the new city
            // Update the board with the new city
            board.upgradeSettlementToCity(settlementId);
        } else {
            // If the player does not have enough resources, revert the resource removal
            if (hasEnoughOre) addResource(Tile::ORE, 3);
            if (hasEnoughWheat) addResource(Tile::WHEAT, 2);
            std::cerr << "Not enough resources to buy a city." << std::endl;
        }
    } else {
        std::cerr << "Settlement not found." << std::endl;
    }
}


int Player::getCityCount() const {
    return cityCount;
}

}    

