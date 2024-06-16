// efiphi10@gmail.com
#include <iostream>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Map.hpp"

using namespace std;
using namespace ariel;

int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    catan.ChooseStartingPlayer();
    Board &board = catan.getBoard();
    Map map;
    map.printBoard();

    p1.placeSettlement(24, map, board);
    p1.placeSettlement(19, map, board);
    p2.placeSettlement(10, map, board);
    p2.placeSettlement(11, map, board);
    p3.placeSettlement(15, map, board);
    p3.placeSettlement(16, map, board);

    p1.displayResources();
    p2.displayResources();
    p3.displayResources();
    p1.displaySettlements(map);
    p2.displaySettlements(map);
    p3.displaySettlements(map);

    catan.play_turn();
    catan.play_turn();
    p2.buyDevelopmentCard(catan);
    p2.trade(p1, "wood", "brick", 1, 1);
    catan.play_turn();
    p3.placeRoad({{"wool", 11}, {"wood", 5}}, board);

    p1.displayResources();
    p2.displayResources();
    p3.displayResources();
    p1.printPoints();
    p2.printPoints();
    p3.printPoints();

    catan.check_winner();

    return 0;
}
