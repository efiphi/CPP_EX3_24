# CPP_EX3_24 - Catan Game Implementation
## Introduction

This project implements a simplified version of the board game Catan. The implementation includes the main components of the game, such as players, resources, settlements, cities, and development cards. The game is programmed in C++ and is designed to simulate the core mechanics of the original board game.
Game Rules

The game follows these simplified rules:

    Players can place settlements and upgrade them to cities.
    Players can purchase settlements and cities using resources.
    Players can trade resources with each other.
    Players can use development cards for special actions.
    The game ends when a player reaches 10 victory points.

## Class Hierarchy

The project is structured into several classes, each representing different parts of the game:
Tile

Represents the different types of resources in the game.

    Resources: WOOD, BRICK, WHEAT, WOOL, ORE, DESERT

### Player

Represents a player in the game.

    Attributes:
        name: The name of the player.
        resources: A map of resources and their quantities.
        settlements: A vector of settlement IDs.
        cities: A vector of city IDs.
        victoryPoints: The number of victory points the player has.
        knightCount: The number of knights the player has.
        roadCount: The number of roads the player has.
        cityCount: The number of cities the player has.

    Methods:
        getName(): Returns the player's name.
        getVictoryPoints(): Returns the player's victory points.
        placeSettlement(int settlementId, Map& map, Board& board): Places a settlement.
        buySettlement(int settlementId, Map& map, Board& board): Buys a settlement.
        buyCity(int settlementId, Board& board): Buys and upgrades a settlement to a city.
        addResource(Tile resource, int quantity): Adds resources to the player.
        removeResource(Tile resource, int quantity): Removes resources from the player.
        trade(Player& other, Tile give, Tile receive, int quantity): Trades resources with another player.
        yearOfPlenty(Tile resource1, Tile resource2): Uses the Year of Plenty development card.
        roadBuilding(const std::vector<std::pair<std::string, int>>& places1, const std::vector<std::pair<std::string, int>>& places2, Board& board): Uses the Road Building development card.
        gainVictoryPoint(): Increases the player's victory points.
        monopoly(Tile resource, std::vector<Player>& otherPlayers): Uses the Monopoly development card.
        playKnight(std::vector<Player>& otherPlayers): Uses the Knight development card.
        getKnightCount(): Returns the number of knights the player has.
        getCityCount(): Returns the number of cities the player has.
        getRoadCount(): Returns the number of roads the player has.

### Board

Represents the game board.

    Methods:
        upgradeSettlementToCity(int settlementId): Upgrades a settlement to a city.
        rollDiceAndDistributeResources(int roll, Player& player): Rolls the dice and distributes resources to players.

### Map

Represents the map of the game.

    Methods:
        printBoard(): Prints the current state of the board.

### Catan

Represents the game manager.

    Attributes:
        players: A vector of players in the game.

    Methods:
        Catan(Player& p1, Player& p2, Player& p3): Initializes the game with three players.
        start_game(): Starts the game.
        getPlayers(): Returns the list of players.
        check_winner(): Checks if a player has won the game.
        printWinner(const Player& player): Prints the winner of the game.

### Libraries Used

    <iostream>: For input and output operations.
    <vector>: For using dynamic arrays.
    <map>: For mapping resource types to their quantities.
    <string>: For handling string operations.
    <algorithm>: For using algorithms like std::find.

## Methods Description
### Player Class Methods

    getName(): Returns the name of the player.
    getVictoryPoints(): Returns the number of victory points the player has.
    placeSettlement(int settlementId, Map& map, Board& board): Places a settlement on the board and increases the player's victory points.
    buySettlement(int settlementId, Map& map, Board& board): Buys a settlement using resources and places it on the board. Increases the player's victory points.
    buyCity(int settlementId, Board& board): Upgrades a settlement to a city using resources. Increases the player's victory points.
    addResource(Tile resource, int quantity): Adds the specified quantity of a resource to the player's inventory.
    removeResource(Tile resource, int quantity): Removes the specified quantity of a resource from the player's inventory if possible.
    trade(Player& other, Tile give, Tile receive, int quantity): Trades the specified quantity of resources with another player.
    yearOfPlenty(Tile resource1, Tile resource2): Gives the player two specified resources immediately.
    roadBuilding(const std::vector<std::pair<std::string, int>>& places1, const std::vector<std::pair<std::string, int>>& places2, Board& board): Allows the player to place two roads for free.
    gainVictoryPoint(): Increases the player's victory points by one.
    monopoly(Tile resource, std::vector<Player>& otherPlayers): Takes all of a specified resource from all other players.
    playKnight(std::vector<Player>& otherPlayers): Uses a knight card. The player with the most knights gets additional victory points.
    getKnightCount(): Returns the number of knights the player has.
    getCityCount(): Returns the number of cities the player has.
    getRoadCount(): Returns the number of roads the player has.

### Board Class Methods

    upgradeSettlementToCity(int settlementId): Upgrades a settlement to a city on the board.
    rollDiceAndDistributeResources(int roll, Player& player): Rolls the dice and distributes resources to the players based on the roll.

### Map Class Methods

    printBoard(): Prints the current state of the game board.

### Catan Class Methods

    Catan(Player& p1, Player& p2, Player& p3): Constructor to initialize the game with three players.
    start_game(): Starts the game by initializing necessary components.
    getPlayers(): Returns the list of players in the game.
    check_winner(): Checks if any player has reached 10 victory points and declares the winner.
    printWinner(const Player& player): Prints the name of the winning player.

## How to Run

    Clone the repository:

    bash

git clone https://github.com/efiphi/CPP_EX3_24.git

Navigate to the project directory:

bash

cd CPP_EX3_24

Build the project:

go

make

make test

Run the main:

bash

    ./catan

Run the tests:

bash

    ./catan_test

## Authors

    Efi Phillips
