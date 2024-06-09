#ifndef CATAN_HPP
#define CATAN_HPP

#include "Player.hpp"
#include "Board.hpp"
#include <vector>

namespace ariel{

class Catan {
private:
    std::vector<Player> players;
    Board board;
    int current_turn;

public:
    Catan(Player &p1, Player &p2, Player &p3);
    void ChooseStartingPlayer();
    Board getBoard() const;
    void start_game();
    void play_turn();
    void check_winner();
    void printWinner();
    void handle_development_card(Player &player, DevelopmentCard &card);
};
}
 
#endif // CATAN_HPP