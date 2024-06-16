#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Map.hpp"
#include <iostream>
#include <sstream>
#include <map>

TEST_CASE("Test Player Creation") {
    ariel::Player p1("Amit");
    ariel::Player p2("Yossi");
    ariel::Player p3("Dana");
    CHECK(p1.getName() == "Amit");
    CHECK(p2.getName() == "Yossi");
    CHECK(p3.getName() == "Dana");
}


TEST_CASE("Test Initial Player Resources and Points") {
    ariel::Player p("Player");
    CHECK(p.getVictoryPoints() == 0);
    CHECK(p.getResourceCount(ariel::Tile::WOOD) == 0);
    CHECK(p.getResourceCount(ariel::Tile::BRICK) == 0);
    CHECK(p.getResourceCount(ariel::Tile::WHEAT) == 0);
    CHECK(p.getResourceCount(ariel::Tile::WOOL) == 0);
    CHECK(p.getResourceCount(ariel::Tile::ORE) == 0);
}

TEST_CASE("Test Board Setup and Resource Distribution") {
    ariel::Player p1("Player1");
    ariel::Player p2("Player2");
    ariel::Player p3("Player3");
    ariel::Board board;
    ariel::Map map;
    ariel::Catan game(p1, p2, p3);

    p1.placeSettlement(4, map, board);  // Hexes: wood 5, wood 4, wheat 10
    p1.placeSettlement(5, map, board);  // Hexes: wood 5, brick 3, wheat 10
    p2.placeSettlement(10, map, board); // Hexes: wood 4, wood 5
    p2.placeSettlement(11, map, board); // Hexes: wood 4, wood 5, wheat 9
    p3.placeSettlement(15, map, board); // Hexes: ore 10, wood 6, ore 4
    p3.placeSettlement(16, map, board); // Hexes: wood 6, ore 4, wool 6

    board.distribute_resources(3); // Test resource distribution for dice roll 3

    CHECK(p1.getResourceCount(ariel::Tile::BRICK) == 1);
    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 3);
    CHECK(p1.getResourceCount(ariel::Tile::WHEAT) == 2);
    CHECK(p2.getResourceCount(ariel::Tile::WOOD) == 4);
    CHECK(p2.getResourceCount(ariel::Tile::WHEAT) == 1);
    CHECK(p3.getResourceCount(ariel::Tile::ORE) == 3);
}

TEST_CASE("Test Catan Game Flow") {
    ariel::Player p1("Player1");
    ariel::Player p2("Player2");
    ariel::Player p3("Player3");
    ariel::Catan game(p1, p2, p3);

    game.start_game();

    auto players = game.getPlayers();
    CHECK(players.size() == 3);

}

TEST_CASE("Test Rolling Dice") {
    ariel::Player p1("Player1");
    ariel::Player p2("Player2");
    ariel::Player p3("Player3");
    ariel::Catan game(p1, p2, p3);

    for (int i = 0; i < 100; ++i) {
        int roll = game.rollDice();
        CHECK(roll >= 2);
        CHECK(roll <= 12);
    }
}


TEST_CASE("Test printBoard output") {
    // Redirect std::cout to a stringstream to capture the output
    std::ostringstream oss;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(oss.rdbuf());

    // Create a Map instance
    ariel::Map map;

    // Call the printBoard method
    map.printBoard();

    // Restore the original std::cout buffer
    std::cout.rdbuf(oldCoutBuf);

    // Expected output
    std::string expected_output =
        "************ CATAN BOARD ************\n"
        "       sea   sea   sea   sea   sea       \n"
        "    sea Wheat  5 Wood  2 Brick  6 sea    \n"
        "  sea Wool  3 Wood  8 Brick 10 Wheat  9 sea  \n"
        "sea Ore 12 Wool 11 Desert  7 Wool  6 Ore  4 sea\n"
        "  sea Wood  8 Wheat 10 Wood  9 Wheat 11 sea  \n"
        "    sea Wool  3 Wood  4 Ore  5 sea    \n"
        "       sea   sea   sea   sea   sea       \n"
        "*************************************\n";

    // Check if the captured output matches the expected output
    CHECK(oss.str() == expected_output);
}

TEST_CASE("Test Player Victory Points and Resources") {
    ariel::Player p1("Player1");
    ariel::Board board;
    ariel::Map map;

    // Check initial victory points
    CHECK(p1.getVictoryPoints() == 0);

    // Place a settlement and check victory points
   

    // Add resources to the player and check resource counts
    p1.addResource(ariel::Tile::WOOD, 3);
    p1.addResource(ariel::Tile::BRICK, 2);
    p1.addResource(ariel::Tile::WHEAT, 1);

    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 3);
    CHECK(p1.getResourceCount(ariel::Tile::BRICK) == 2);
    CHECK(p1.getResourceCount(ariel::Tile::WHEAT) == 1);

    p1.placeSettlement(4, map, board);
    CHECK(p1.getVictoryPoints() == 1);
}

TEST_CASE("Test Trade") {
    ariel::Player p1("Player1");
    ariel::Player p2("Player2");

    // Initial resource setup
    p1.addResource(ariel::Tile::WOOD, 3);
    p2.addResource(ariel::Tile::BRICK, 2);

    // Trade 1 wood for 1 brick
    p1.trade(p2, "wood","brick", 1, 1);

    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 2);
    CHECK(p1.getResourceCount(ariel::Tile::BRICK) == 1);
    CHECK(p2.getResourceCount(ariel::Tile::WOOD) == 1);
    CHECK(p2.getResourceCount(ariel::Tile::BRICK) == 1);
}

TEST_CASE("Test Place Road") {
    ariel::Player p1("Player1");
    ariel::Board board;
    ariel::Map map;

    // Initial road placements
    std::vector<std::pair<std::string, int>> places1 = {{"Wood", 1}, {"Brick", 2}};
    p1.placeRoad(places1, board);

    std::vector<std::pair<std::string, int>> places2 = {{"Wood", 2}, {"Brick", 3}};
    p1.placeRoad(places2, board);

    // Check if resources were used correctly (assuming placeRoad uses resources)
    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 0); // Adjust based on initial resources and road cost
    CHECK(p1.getResourceCount(ariel::Tile::BRICK) == 0); // Adjust based on initial resources and road cost
}

TEST_CASE("Test Year of Plenty Card") {
    ariel::Player p1("Player1");
    p1.yearOfPlenty(ariel::Tile::WOOD, ariel::Tile::BRICK);
    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 1);
    CHECK(p1.getResourceCount(ariel::Tile::BRICK) == 1);
}

TEST_CASE("Test Road Building Card") {
    ariel::Player p1("Player1");
    ariel::Board board;
    std::vector<std::pair<std::string, int>> places1 = {{"Wood", 1}, {"Brick", 2}};
    std::vector<std::pair<std::string, int>> places2 = {{"Wood", 2}, {"Brick", 3}};
    CHECK(p1.getRoadCount() == 0);
    p1.roadBuilding(places1, places2, board);
    CHECK(p1.getRoadCount() == 2);  // Assuming road count is updated in placeRoad
}

TEST_CASE("Test Victory Point Card") {
    ariel::Player p1("Player1");
    CHECK(p1.getVictoryPoints() == 0);
    p1.gainVictoryPoint();
    CHECK(p1.getVictoryPoints() == 1);
}

TEST_CASE("Test Monopoly Card") {
    ariel::Player p1("Player1");
    ariel::Player p2("Player2");
    ariel::Player p3("Player3");
    p2.addResource(ariel::Tile::WOOL, 3);
    p3.addResource(ariel::Tile::WOOD, 2);

    std::vector<ariel::Player> players = {p1, p2, p3};
    p1.monopoly(ariel::Tile::WOOD, players);

    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 2);
    CHECK(p2.getResourceCount(ariel::Tile::WOOL) == 3);
    CHECK(p3.getResourceCount(ariel::Tile::WOOD) == 2);
}

TEST_CASE("Test Remove Resource") {
    ariel::Player p1("Player1");

    // Add resources to the player
    p1.addResource(ariel::Tile::WOOD, 3);
    p1.addResource(ariel::Tile::BRICK, 2);

    // Check initial resource counts
    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 3);
    CHECK(p1.getResourceCount(ariel::Tile::BRICK) == 2);

    // Remove resources and check counts
    bool result = p1.removeResource(ariel::Tile::WOOD, 2);
    CHECK(result == true);
    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 1);

    // Try to remove more resources than available
    result = p1.removeResource(ariel::Tile::WOOD, 2);
    CHECK(result == false);
    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 1);

    // Remove remaining resources
    result = p1.removeResource(ariel::Tile::WOOD, 1);
    CHECK(result == true);
    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 0);

    // Remove resources for another resource type
    result = p1.removeResource(ariel::Tile::BRICK, 1);
    CHECK(result == true);
    CHECK(p1.getResourceCount(ariel::Tile::BRICK) == 1);

    // Try to remove more resources than available
    result = p1.removeResource(ariel::Tile::BRICK, 2);
    CHECK(result == false);
    CHECK(p1.getResourceCount(ariel::Tile::BRICK) == 1);
}


TEST_CASE("Test Knight Card") {
    ariel::Player p1("Player1");
    ariel::Player p2("Player2");
    ariel::Player p3("Player3");

    std::vector<ariel::Player> players = {p1, p2, p3};

    p1.playKnight(players);
    CHECK(p1.getKnightCount() == 1);
    CHECK(p1.getVictoryPoints() == 0);

    p1.playKnight(players);
    p1.playKnight(players);
    CHECK(p1.getKnightCount() == 3);
    CHECK(p1.getVictoryPoints() == 2);
}

TEST_CASE("Test Buy City") {
    ariel::Player p1("Player1");
    ariel::Board board;
    ariel::Map map;
    
    CHECK(p1.getResourceCount(ariel::Tile::WHEAT) == 0);

    // Add resources for city purchase
    p1.addResource(ariel::Tile::ORE, 3);
    p1.addResource(ariel::Tile::WHEAT, 2);

    // Place a settlement and upgrade to city
    p1.placeSettlement(4, map, board);
    CHECK(p1.getVictoryPoints() == 1);
    p1.buyCity(4, board);

    // Check if the settlement was upgraded to a city
    CHECK(p1.getCityCount() == 1);
    CHECK(p1.getResourceCount(ariel::Tile::ORE) == 0);
    CHECK(p1.getVictoryPoints() == 2);
}

TEST_CASE("Test Roll Dice with City") {
    ariel::Player p1("Player1");
    ariel::Board board;
    ariel::Map map;

    // Add resources for city purchase
    p1.addResource(ariel::Tile::ORE, 3);
    p1.addResource(ariel::Tile::WHEAT, 2);

    // Place a settlement and upgrade to city
    p1.placeSettlement(4, map, board);
    p1.buyCity(4, board);

    // Simulate rolling the dice for resource collection
    board.distribute_resources(4);

    // Check if the player received double resources from the city
    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 2); // Assuming hex 4 is WOOD
}

TEST_CASE("Test Buy Settlement") {
    ariel::Player p1("Player1");
    ariel::Board board;
    ariel::Map map;

    // Add resources for settlement purchase
    p1.addResource(ariel::Tile::BRICK, 1);
    p1.addResource(ariel::Tile::WOOD, 1);
    p1.addResource(ariel::Tile::WHEAT, 1);
    p1.addResource(ariel::Tile::WOOL, 1);

    // Check initial resources
    CHECK(p1.getResourceCount(ariel::Tile::BRICK) == 1);
    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 1);
    CHECK(p1.getResourceCount(ariel::Tile::WHEAT) == 1);
    CHECK(p1.getResourceCount(ariel::Tile::WOOL) == 1);

    // Buy a settlement
    p1.buySettlement(4, map, board);

    // Check if the settlement was added
    CHECK(p1.getVictoryPoints() == 1);
    CHECK(p1.getResourceCount(ariel::Tile::BRICK) == 0);
    CHECK(p1.getResourceCount(ariel::Tile::WOOD) == 0);
    CHECK(p1.getResourceCount(ariel::Tile::WHEAT) == 0);
    CHECK(p1.getResourceCount(ariel::Tile::WOOL) == 0);
}


