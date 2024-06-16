#include "Map.hpp"
#include <iomanip>

namespace ariel {

Map::Map() {
    settlements = {
        {1, { {{"wood", 5}, {"brick", 3}}, {5} }},
        {2, { {{"brick", 3}, {"wheat", 10}}, {7} }},
        {3, { {{"wood", 5}, {"wood", 4}}, {4} }},
        {4, { {{"wood", 5}, {"wood", 4}, {"wheat", 10}}, {3, 5, 12} }},
        {5, { {{"wood", 5}, {"brick", 3}, {"wheat", 10}}, {1, 4, 6} }},
        {6, { {{"brick", 3}, {"wheat", 10}, {"ore", 9}}, {5, 7, 14} }},
        {7, { {{"brick", 3}, {"wheat", 10}, {"wool", 6}}, {2, 6, 8} }},
        {8, { {{"wheat", 10}, {"wool", 6}, {"ore", 10}}, {7, 9, 16} }},
        {9, { {{"wheat", 10}, {"ore", 10}}, {8} }},
        {10, { {{"wood", 4}, {"wood", 5}}, {11} }},
        {11, { {{"wood", 4}, {"wood", 5}, {"wheat", 9}}, {10, 12, 20} }},
        {12, { {{"wood", 5}, {"brick", 3}, {"wheat", 9}}, {4, 11, 13} }},
        {13, { {{"brick", 3}, {"wheat", 9}, {"ore", 10}}, {12, 14, 22} }},
        {14, { {{"brick", 3}, {"ore", 10}, {"wood", 6}}, {6, 13, 15} }},
        {15, { {{"ore", 10}, {"wood", 6}, {"ore", 4}}, {14, 16, 24} }},
        {16, { {{"wood", 6}, {"ore", 4}, {"wool", 6}}, {8, 15, 17} }},
        {17, { {{"ore", 4}, {"wool", 6}}, {16, 18, 26} }},
        {18, { {{"ore", 4}, {"wool", 6}}, {17} }},
        {19, { {{"brick", 8}, {"wheat", 2}}, {20} }},
        {20, { {{"brick", 8}, {"wheat", 2}, {"wood", 11}}, {11, 19, 21} }},
        {21, { {{"brick", 8}, {"wood", 11}, {"wheat", 9}}, {20, 22, 29} }},
        {22, { {{"wood", 11}, {"wheat", 9}, {"brick", 8}}, {13, 21, 23} }},
        {23, { {{"wheat", 9}, {"brick", 8}, {"wood", 4}}, {22, 24, 31} }},
        {24, { {{"brick", 8}, {"wood", 4}, {"wood", 11}}, {15, 23, 25} }},
        {25, { {{"wood", 4}, {"wood", 11}, {"brick", 8}}, {24, 26, 33} }},
        {26, { {{"wood", 11}, {"brick", 8}}, {17, 25, 27} }},
        {27, { {{"brick", 8}}, {26} }},
        {28, { {{"wheat", 2}, {"wood", 11}}, {29} }},
        {29, { {{"wheat", 2}, {"wood", 11}, {"brick", 8}}, {21, 28, 30} }},
        {30, { {{"wood", 11}, {"brick", 8}, {"ore", 10}}, {29, 31, 35} }},
        {31, { {{"brick", 8}, {"ore", 10}, {"wheat", 9}}, {23, 30, 32} }},
        {32, { {{"ore", 10}, {"wheat", 9}, {"ore", 4}}, {31, 33, 36} }},
        {33, { {{"wheat", 9}, {"ore", 4}}, {25, 32, 34} }},
        {34, { {{"ore", 4}}, {33} }},
        {35, { {{"wheat", 9}, {"ore", 4}}, {30} }},
        {36, { {{"ore", 4}}, {32} }},
    };
}

Settlement Map::getSettlement(int id) const {
    auto it = settlements.find(id);
    if (it != settlements.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid settlement ID");
}

void Map::printBoard() const {
    std::vector<std::string> board_representation(7, std::string(50, ' '));

    // Helper function to format tiles
    auto format_tile = [](const std::string& type, int roll) {
        return type + " " + (roll < 10 ? " " + std::to_string(roll) : std::to_string(roll));
    };

    // Initialize hexMap with the provided hex locations
    std::map<int, std::pair<std::string, int>> hexMap = {
        {1, {"Wheat", 5}}, {2, {"Wood", 2}}, {3, {"Brick", 6}}, {4, {"Wool", 3}}, {5, {"Wood", 8}},
        {6, {"Brick", 10}}, {7, {"Wheat", 9}}, {8, {"Ore", 12}}, {9, {"Wool", 11}}, {10, {"Desert", 7}},
        {11, {"Wool", 6}}, {12, {"Ore", 4}}, {13, {"Wood", 8}}, {14, {"Wheat", 10}}, {15, {"Wood", 9}},
        {16, {"Wheat", 11}}, {17, {"Wool", 3}}, {18, {"Wood", 4}}, {19, {"Ore", 5}}
    };

    // Prepare the formatted hexMap
    std::vector<std::string> formattedHexMap(20, "       ");
    for (const auto& hex : hexMap) {
        int hexId = hex.first;
        std::string resource = hex.second.first;
        int roll = hex.second.second;
        formattedHexMap[hexId] = format_tile(resource, roll);
    }

    // Fill in the board representation with the formatted hexes
    board_representation[0] = "       sea   sea   sea   sea   sea       ";
    board_representation[1] = "    sea " + formattedHexMap[1] + " " + formattedHexMap[2] + " " + formattedHexMap[3] + " sea    ";
    board_representation[2] = "  sea " + formattedHexMap[4] + " " + formattedHexMap[5] + " " + formattedHexMap[6] + " " + formattedHexMap[7] + " sea  ";
    board_representation[3] = "sea " + formattedHexMap[8] + " " + formattedHexMap[9] + " " + formattedHexMap[10] + " " + formattedHexMap[11] + " " + formattedHexMap[12] + " sea";
    board_representation[4] = "  sea " + formattedHexMap[13] + " " + formattedHexMap[14] + " " + formattedHexMap[15] + " " + formattedHexMap[16] + " sea  ";
    board_representation[5] = "    sea " + formattedHexMap[17] + " " + formattedHexMap[18] + " " + formattedHexMap[19] + " sea    ";
    board_representation[6] = "       sea   sea   sea   sea   sea       ";

    std::cout << "************ CATAN BOARD ************\n";
    for (const auto& line : board_representation) {
        std::cout << line << std::endl;
    }
    std::cout << "*************************************\n";
}







}
