#include <iostream>
#include <algorithm>
#include "Game.hpp"
#include "Board.hpp"
#include "Property.hpp"

Game::Game():currentPlayerIndex(0), gameOver(false), doubleCounter(0), dice(), board() {
    initializeGame();
}

Game::Game(const std::vector<std::string>& playerNames):currentPlayerIndex(0), gameOver(false), doubleCounter(0), dice(), board() {
    // Create players based on the provided names
    for (const auto& name : playerNames) {
        players.emplace_back(name);
    }
    initializeGame();
}

void Game::playTurn() {
    Player& currentPlayer = players[currentPlayerIndex];
    if(currentPlayer.isBankrupt){
        return;
    }
    
    std::cout << currentPlayer.getName() << "is rolling the dice!" << std::endl;
    
    int totalRoll = dice.roll();
    
    // Move the player on the board
    int newPosition = (currentPlayer.position + totalRoll) % board.getNumberOfPropertys();
    currentPlayer.position = newPosition;
    
    // Display the move
    std::cout << currentPlayer.getName() << " rolled " << dice.getFirst() << " and " << dice.getSecond() << "." << std::endl;
    
    // Check for doubles (to allow another turn)
    if (dice.isDouble()) {
        doubleCounter++;
        if(doubleCounter != 3){
            std::cout << currentPlayer.getName() << " rolled a double! Total doubles: " << doubleCounter << std::endl;
        } else {
            if(currentPlayer.removeGetOutOfJailCard()){
                std::cout << currentPlayer.getName() << " rolled 3 doubles but skipped jail time!" << std::endl;
            } else {
                currentPlayer.isJailed = true;
                currentPlayer.position = board.getJailIndex(); // Assuming Jail is at index 10
                std::cout << currentPlayer.getName() << " rolled 3 doubles and goes directly to Jail!" << std::endl;
                currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
                doubleCounter = 0;
                return;
            }
        }
    }

    // Handle landing on the Property
    Property* landedProperty = board.getProperty(newPosition);
    landedProperty->landOn(currentPlayer);
    
    if(!dice.isDouble()){
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        doubleCounter = 0;
    }
}

void Game::endGame() {
    gameOver = true;
    for(unsigned int i = 0; i < players.size(); i++){
        if(players[i].money >= 4000){
            std::cout << players[i].getName() << " wins!" << std::endl;
            return;
        }
    }
    for(unsigned int i = 0; i < players.size(); i++){
        if(!players[i].isBankrupt){
            std::cout << players[i].getName() << " wins!" << std::endl;
            return;
        }
    }    
}

void Game::addPlayer(const Player& player) {
    players.push_back(player);
}

bool Game::isGameOver() const {
    // Implement logic to determine if the game is over
    // For example, check if only one player is left with money
    int activePlayers = 0;
    for (const auto& player : players) {
        if (!player.isBankrupt) {
            ++activePlayers;
        }
        if(player.money >= 4000){
            return true;
        }
    }
    return activePlayers <= 1; // Game over if one or fewer players have money
}

std::vector<Player>& Game::getPlayers(){
    return players;
}

// The player's turn logic    
void Game::playerTurn(Player& player) {
    std::cout << player.getName() << "is rolling the dice..." << std::endl;

    Dice dice;
    int moveSteps = dice.roll();
    std::cout << player.getName() << " rolled a " << moveSteps << "!" << std::endl;
    player.position = player.position + moveSteps;
    if(player.position > board.getNumberOfPropertys()){
        std::cout << player.getName() << " has passed by the start mark and received 200!" << std::endl;
        player.money += 200;
        player.position = player.position % board.getNumberOfPropertys();
    }
    board.getProperty(player.position)->landOn(player);
}

Player Game::getWinner() const {
    // Determine and return the winner (the last player remaining with money)
    for (const auto& player : players) {
        if (player.money > 4000) {
            return player;
        }
    }
    for (const auto& player : players) {
        if (!player.isBankrupt) {
            return player;
        }
    }
    return players[0]; //using the first player as default winner in case of an error
}

int Game::getCurrentPlayerIndex(){
    return currentPlayerIndex;
}

Dice Game::getDice(){
    return dice;
}

void Game::initializeGame() {
    // Set up the board and add Propertys
    // Example Propertys (you will need to create the actual Property subclasses and instances)
    std::vector<ColorGroup>& colorGroups = board.getColorGroups();
    board.addProperty(new SpecialProperty("Go", this, SpecialAction::AdvanceToGo));
    board.addProperty(new Street("MEDITERRANEAN AVENUE", 60, 50, 100, 200, colorGroups[0]));
    board.addProperty(new SpecialProperty("COMMUNITY CHEST", this, SpecialAction::CommunityChest));
    board.addProperty(new Street("BALTIC AVENUE", 60, 50, 100, 200, colorGroups[0]));
    board.addProperty(new SpecialProperty("INCOME TAX", this, SpecialAction::PoorTax));
    board.addProperty(new Train("READING RAILROAD" , 200, 50));
    board.addProperty(new Street("ORIENTAL AVENUE", 100, 50, 100, 200, colorGroups[1]));
    board.addProperty(new SpecialProperty("CHANCE", this, SpecialAction::Chance));
    board.addProperty(new Street("VERMONT AVENUE", 100, 50, 100, 200, colorGroups[1]));
    board.addProperty(new Street("CONNECTICUT AVENUE", 120, 50, 100, 200, colorGroups[1]));
    
    board.addProperty(new SpecialProperty("Go", this, SpecialAction::GoToJail));
    board.addProperty(new Street("ST.CHARLES PLACE", 140, 50, 100, 200, colorGroups[2]));
    board.addProperty(new SpecialProperty("ELECTRIC COMPANY", this, SpecialAction::ElectricCompany));
    board.addProperty(new Street("STATES AVENUE", 140, 50, 100, 200, colorGroups[2]));
    board.addProperty(new Street("VIRGINIA AVENUE", 160, 50, 100, 200, colorGroups[2]));
    board.addProperty(new Train("PENNSYLVANIA RAILROAD", 200, 50));
    board.addProperty(new Street("ST.JAMES PLACE", 180, 50, 100, 200, colorGroups[3]));
    board.addProperty(new SpecialProperty("COMMUNITY CHEST", this, SpecialAction::CommunityChest));
    board.addProperty(new Street("TENNESSE AVENUE", 180, 50, 100, 200, colorGroups[3]));
    board.addProperty(new Street("NEW YORK AVENUE", 200, 50, 100, 200, colorGroups[3]));
    
    board.addProperty(new SpecialProperty("Go", this, SpecialAction::Jail));
    board.addProperty(new Street("KENTUCKY AVENUE", 220, 50, 100, 200, colorGroups[4]));
    board.addProperty(new SpecialProperty("CHANCE", this, SpecialAction::Chance));
    board.addProperty(new Street("INDIANA AVENUE", 220, 50, 100, 200, colorGroups[4]));
    board.addProperty(new Street("ILLINOIS AVENUE", 240, 50, 100, 200, colorGroups[4]));
    board.addProperty(new Train("B.&O. RAILROAD", 200, 50));
    board.addProperty(new Street("ATLANTIC AVENUE", 260, 50, 100, 200, colorGroups[5]));
    board.addProperty(new Street("VENTNOR AVENUE", 260, 50, 100, 200, colorGroups[5]));
    board.addProperty(new SpecialProperty("WATER WORKS", this, SpecialAction::WaterWorks));
    board.addProperty(new Street("MARVIN GARDENS", 280, 50, 100, 200, colorGroups[5]));

    board.addProperty(new SpecialProperty("Go", this, SpecialAction::FreeParking));
    board.addProperty(new Street("PACIFIC AVENUE", 300, 50, 100, 200, colorGroups[6]));
    board.addProperty(new Street("NORTH CAROLINA AVENUE", 300, 50, 100, 200, colorGroups[6]));
    board.addProperty(new SpecialProperty("COMMUNITY CHEST", this, SpecialAction::CommunityChest));
    board.addProperty(new Street("PENNSYLVANIA AVENUE", 320, 50, 100, 200, colorGroups[6]));
    board.addProperty(new Train("SHORT LINE", 200, 50));
    board.addProperty(new SpecialProperty("CHANCE", this, SpecialAction::Chance));
    board.addProperty(new Street("PARK PLACE", 350, 50, 100, 200, colorGroups[7]));
    board.addProperty(new SpecialProperty("LUXURY TAX", this, SpecialAction::LuxuryTax));
    board.addProperty(new Street("BOARDWALK", 400, 50, 100, 200, colorGroups[7]));
    std::cerr << "board size: " << board.getNumberOfPropertys() << std::endl;
}