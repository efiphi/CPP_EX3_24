#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Player.hpp"
#include "Board.hpp"
#include "Catan.hpp"

using namespace ariel;

TEST_CASE("Resource distribution based on dice roll") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan game(p1, p2, p3);

    game.ChooseStartingPlayer();
    Board &board = game.getBoard();

    p1.placeSettlement({{"wood", 5}, {"brick", 3}, {"wool", 11}}, board);
    p2.placeSettlement({{"wheat", 10}, {"wood", 6}, {"ore", 9}}, board);
    p3.placeSettlement({{"wood", 4}, {"wheat", 9}, {"wool", 6}}, board);

    game.start_game();

    // Assume we can directly set dice roll results
    p1.rollDice(board);
    CHECK(p1.getResourceCount(Tile::WOOD) == 1);
    CHECK(p1.getResourceCount(Tile::WOOL) == 1);
}
