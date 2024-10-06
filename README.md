# Monopoly Game Simulation

A simple simulation of a Monopoly-style game, featuring core components such as a game board, players, properties, and a graphical user interface.

## Table of Contents

- **Project Overview** `project-overview`
- **Header Files and Their Functions** `header-files-and-their-functions`
  -  Board.hpp
  -  Dice.hpp
  -  Game.hpp
  -  GUI.hpp
  -  Player.hpp
  -  Property.hpp
- **Features**
- **Installation**
- **Usage**
- **Contributing**
- **License**
- **Acknowledgments**

## Project Overview

This project simulates a Monopoly-style game where players can buy properties, roll dice, and interact with a graphical user interface. The game logic is encapsulated within various classes, each serving a distinct purpose.

### Header Files and Their Functions

### 1. Board.hpp
The `Board` class manages the game board, including properties and color groups.

- **`Board()`**
  - Constructor that initializes the board.
- **`~Board()`**
  - Destructor that cleans up dynamically allocated properties.
- **`void addProperty(Property* Property)`**
  - Adds a property to the board.
- **`Property* getProperty(unsigned int index) const`**
  - Retrieves a property by its index.
- **`int getNumberOfPropertys() const`**
  - Returns the total number of properties on the board.
- **`void initializeColorGroups()`**
  - Initializes color groups and associates streets.
- **`Various index getter methods`**
  - Methods like `getJailIndex()` and `getBoardWalkIndex()` return specific property indices.

### 2. Dice.hpp
The `Dice` class simulates the rolling of two dice.

- **`Dice()`**
  - Constructor that initializes the dice.
- **`int roll()`**
  - Rolls the dice and returns the total value.
- **`int getFirst() const`**
  - Returns the value of the first die.
- **`int getSecond() const`**
  - Returns the value of the second die.
- **`bool isDouble() const`**
  - Checks if both dice rolled the same value.

### 3. Game.hpp
The `Game` class orchestrates the game logic and player interactions.

- **`Game()`**
  - Default constructor for creating an empty game.
- **`Game(const std::vector<std::string>& playerNames)`**
  - Constructor that initializes the game with player names.
- **`void initializeGame()`**
  - Sets up the initial game state.
- **`void playTurn()`**
  - Manages the logic for a player's turn.
- **`void endGame()`**
  - Ends the game and determines the winner.
- **Various player and game state methods**
  - Includes methods like `addPlayer()`, `isGameOver()`, and `getWinner()`.

### 4. GUI.hpp
The `GUI` class handles the graphical representation of the game using SFML.

- **`GUI()`**
  - Constructor that sets up the GUI.
- **`void setupPlayers()`**
  - Prepares player settings in the GUI.
- **`void run()`**
  - Main loop that runs the GUI.
- **`void render()`**
  - Renders the current game state.
- **`void handleEvents()`**
  - Handles user input and events.
- **Drawing functions**
  - Methods like `drawBoard()`, `drawPlayers()`, and `drawGameInfo()` for visual updates.

### 5. Player.hpp
The `Player` class represents each player in the game.

- **`Player(const std::string& name)`**
  - Constructor that initializes a player with a name.
- **`std::vector<Property*> getOwnedProperties()`**
  - Returns a list of properties owned by the player.
- **`const std::string& getName() const`**
  - Returns the player's name.
- **`void addProperty(Property* property)`**
  - Adds a property to the player's collection.
- **Various attributes**
  - Includes attributes like `money`, `position`, and methods for managing player status.

### 6. Property.hpp
Defines the `Property` class and its derived classes for various property types.

- **`Property(const std::string& name, bool isUtility, bool isRailroad)`**
  - Constructor for creating a property.
- **`virtual void landOn(Player& player) = 0`**
  - Pure virtual function to define actions when a player lands on a property.
- **Derived classes**
  - Includes `SpecialProperty`, `Street`, and `Train`, each with specific behaviors and attributes.

## Features

- A dynamic board with various properties, including streets and special properties.
- A dice rolling mechanism to simulate player movements.
- Player management, including buying properties and tracking ownership.
- A graphical user interface using SFML for an interactive experience.

## Installation

To set up the project, follow these steps:

1. Clone the repository
    ```bash
    git clone link
    cd repository-name
    ```

2. Install SFML (if not already installed). Instructions can be found on the [SFML website](https://www.sfml-dev.org/download.php).

3. Build the project
    ```bash
    make
    ```

## Usage

To run the game after compilation

```bash
    ./monoply
    ```
