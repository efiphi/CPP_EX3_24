#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"

using namespace std;
using namespace ariel;

int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    // Starting the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer();   // should print the name of the starting player, assume it is Amit.
    Board board = catan.getBoard(); // get the board of the game.

    // Example places
    vector<string> places1 = {"Forest", "Hills", "Wool"};
    vector<int> placesNum1 = {5, 6, 11};
    p1.placeSettlement(places1, placesNum1, board);
    p1.placeRoad(places1, placesNum1, board);

    vector<string> places2 = {"Agricultural Land", "Desert"};
    vector<int> placesNum2 = {3, 4};
    p1.placeSettlement(places2, placesNum2, board);
    p1.placeRoad(places2, placesNum2, board);

    vector<string> places3 = {"Mountains", "Pasture Land"};
    vector<int> placesNum3 = {4, 9};
    p2.placeSettlement(places3, placesNum3, board);
    p2.placeRoad(places3, placesNum3, board);

    vector<string> places4 = {"Forest", "Pasture Land"};
    vector<int> placesNum4 = {5, 9};
    p2.placeSettlement(places4, placesNum4, board);
    p2.placeRoad(places4, placesNum4, board);

    vector<string> places5 = {"Mountains", "Pasture Land"};
    vector<int> placesNum5 = {3, 8};
    p3.placeSettlement(places5, placesNum5, board);
    p3.placeRoad(places5, placesNum5, board);

    vector<string> places6 = {"Agricultural Land", "Pasture Land"};
    vector<int> placesNum6 = {3, 9};
    p3.placeSettlement(places6, placesNum6, board);
    p3.placeRoad(places6, placesNum6, board);

    // Perform multiple rounds to accumulate resources and perform actions
    for (int i = 0; i < 10; ++i) {
        p1.rollDice(board);
        p1.endTurn();

        p2.rollDice(board);
        try {
            p2.buyDevelopmentCard(catan);
        } catch (const std::exception &e) {
            cout << "Error: " << e.what() << endl;
        }
        p2.endTurn();

        p3.rollDice(board);
        p3.endTurn();
    }

    // Perform actions with accumulated resources
    try {
        p1.placeRoad({"Forest", "Hills"}, {5, 6}, board);
        p1.placeSettlement({"Wood"}, {8}, board);
    } catch (const std::exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        p2.trade(p1, "wood", "brick", 1, 1); // p2 trades 1 wood for 1 brick with p1.
    } catch (const std::exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        p2.placeRoad({"Mountains", "Pasture Land"}, {4, 9}, board);
    } catch (const std::exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        p3.buyDevelopmentCard(catan);
    } catch (const std::exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    board.printBoard();

    p1.printPoints();
    p2.printPoints();
    p3.printPoints();

    // Final checks for resource allocation
    catan.printWinner(); // Should print None because no player reached 10 points.

    return 0;
}
