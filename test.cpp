#include "doctest.h"
#include "Board.hpp"
#include "Player.hpp"
#include "Dice.hpp"
#include "Game.hpp"

using namespace std;

TEST_CASE("Test Board functionality") {
    Board board;
    ColorGroup group = {"Brown", {}};
    // Test adding properties
    Property* property1 = new Street("Mediterranean Avenue", 100, 6, 50, 200, group);
    Property* property2 = new Street("Baltic Avenue", 100, 6, 50, 200, group);
    
    board.addProperty(property1);
    board.addProperty(property2);

    CHECK(board.getNumberOfPropertys() == 2);
    CHECK(board.getProperty(0)->getName() == "Mediterranean Avenue");
    CHECK(board.getProperty(1)->getName() == "Baltic Avenue");

    // Clean up
    delete property1;
    delete property2;
}

TEST_CASE("Test Player functionality") {
    Player player("Alice");
    ColorGroup group = {"Brown", {}};

    CHECK(player.getName() == "Alice");
    CHECK(player.getOwnedProperties().size() == 0);

    Property* property = new Street("Reading Railroad", 200, 25, 100, 200, group);
    player.addProperty(property);
    
    CHECK(player.getOwnedProperties().size() == 1);
    CHECK(player.getOwnedProperties()[0]->getName() == "Reading Railroad");

    // Clean up
    delete property;
}

TEST_CASE("Test Game functionality") {
    Game game({"Alice", "Bob"});
    
    CHECK(game.getPlayers().size() == 2);
    CHECK(game.getCurrentPlayerIndex() == 0);
    
    game.playTurn(); // Simulate a turn

    CHECK(game.isGameOver() == false); // Game should not be over yet

    // Check for a winner scenario
    game.endGame(); // End the game
    CHECK(game.getWinner().getName() == "Alice"); // Example: Assume Alice is the winner

    // Test adding players
    Player newPlayer("Charlie");
    game.addPlayer(newPlayer);
    CHECK(game.getPlayers().size() == 3);
}

TEST_CASE("Test Dice functionality") {
    Dice dice;

    int roll1 = dice.roll();
    int roll2 = dice.roll();

    CHECK(roll1 >= 2 && roll1 <= 12); // Dice roll should be between 2 and 12
    CHECK(roll2 >= 2 && roll2 <= 12); // Same for the second roll

    // Check if doubles
    CHECK(dice.isDouble() == false); // Initial roll can't be a double
}

TEST_CASE("Test Property landing") {
    Player player("Alice");
    ColorGroup group = {"Brown", {}};
    Property* property = new Street("Mediterranean Avenue", 100, 6, 50, 200, group);
    property->setOwner(&player);

    CHECK(property->getOwner()->getName() == player.getName());
    
    // Simulate landing on property
    property->landOn(player); // Implement the logic in Property to affect player

    // Check player state
    CHECK(player.money < 100); // Assume the player pays rent or similar
    CHECK(property->owned == true);

    // Clean up
    delete property;
}

TEST_CASE("Test invalid game state") {
    Game game;

    // Assuming certain conditions can throw exceptions
    CHECK_THROWS(game.playTurn()); // Play turn without initializing the game
}
