// efiphi10@gmail.com
#ifndef CATAN_HPP
#define CATAN_HPP

#include "Player.hpp"
#include "Board.hpp"
#include "Map.hpp"
#include <vector>

namespace ariel {

class Catan {
private:
    std::vector<Player> players;
    Board board;
    int current_turn;
    void printWinner(const Player& player);

public:
    Catan();
    Catan(Player &p1, Player &p2, Player &p3);
    void ChooseStartingPlayer();
    Board& getBoard();
    void start_game();
    void play_turn();
    Player* check_winner();
    void handle_development_card(Player &player, DevelopmentCard &card);
    std::vector<Player>& getPlayers();
    int rollDice() const;
    void performPlayerActions(Player &player);
};

}

#endif // CATAN_HPP
