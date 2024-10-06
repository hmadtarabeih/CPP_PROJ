#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Board.hpp"
#include "Player.hpp"
#include "Dice.hpp"

class Game {
private:
    std::vector<Player> players;
    int currentPlayerIndex;
    bool gameOver;
    int doubleCounter;
    Dice dice;
public:
    Board board;
    Game(); // Empty constructor
    Game(const std::vector<std::string>& playerNames);
    void initializeGame();
    void playTurn();
    void endGame();
    void addPlayer(const Player& player);
    
    bool isGameOver() const;

    void playerTurn(Player& player);
    Player getWinner() const;
    int getCurrentPlayerIndex();
    Dice getDice();
    std::vector<Player>& getPlayers();
    
};

#endif // GAME_H
