#include "GUI.hpp"
#include <string>
#include <sstream>

GUI::GUI() : window(sf::VideoMode(1200, 1200), "Monopoly"), game() {
    if (!backgroundTexture.loadFromFile("board.jpeg")) {
        std::cerr << "Could not load background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    float targetWidth = 900.f;
    float targetHeight = 900.f;

    float scaleX = targetWidth / backgroundTexture.getSize().x; // Width scale
    float scaleY = targetHeight / backgroundTexture.getSize().y; // Height scale

    backgroundSprite.setScale(scaleX, scaleY);
    setupPlayers();
}
void GUI::setupPlayers() {
    // Initialize player names
    int numPlayers = 0;
    bool validInput = false;

    // Input for number of players
    while (!validInput) {
        // Display input prompt
        window.clear();
        displayText("How many players? (between 2 and 8):");
        std::cin >> numPlayers;

        if (numPlayers >= 2 && numPlayers <= 8) {
            validInput = true;
        } else {
            window.clear();
            displayText("Not allowed.");
        }
    }

    // Input for player names
    validInput = false;
    for (int i = 0; i < numPlayers; ++i) {
        std::stringstream prompt;
        prompt << "Name for player " << (i + 1) << ":";
        window.clear();
        displayText(prompt.str());
        std::string playerName;
        std::cin >> playerName;
        game.addPlayer(Player(playerName));
    }
    validInput = true;
}

void GUI::run() {
    while (window.isOpen() && !game.isGameOver()) {
        // Main game loop
        for (auto& player : game.getPlayers()) {
            handleEvents();
            render();
            std::cout << "test" << std::endl;
            displayText(player.getName() + "'s turn. Press Enter to roll the dice...");
            std::cin.ignore();
            game.playerTurn(player);
            if (game.isGameOver()) {
                break; // Exit if game is over
            }
        }
    }
    Player winner = game.getWinner();
    std::cout << winner.getName() + " wins the game!" << std::endl;
}

void GUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void GUI::render() {
    window.clear();
    window.draw(backgroundSprite); // Draw the background image
    drawPlayers();
    drawGameInfo();
    window.display();
}

void GUI::drawBoard() {
    // Load and draw the game board here (replace with actual drawing logic)
    sf::RectangleShape board(sf::Vector2f(600, 600));
    board.setFillColor(sf::Color::Green);
    window.draw(board);
}

void GUI::drawPlayers() {
    static const std::vector<sf::Color> playerColors = {
        sf::Color::Cyan,
        sf::Color::White,
        sf::Color::Red,
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color::Green,
        sf::Color::Black,
        sf::Color::Magenta
    };
    // Draw player names and their information
    for (size_t i = 0; i < game.getPlayers().size(); ++i) {
        Player& player = game.getPlayers()[i];
        player.updatePositions(900, 75);
        int positionX = player.positionX;
        int positionY = player.positionY;

        // Create a colored circle for the player
        sf::CircleShape playerBall(10); // Radius of 15 pixels
        playerBall.setFillColor(playerColors[i]); // Use the primary color
        playerBall.setPosition(positionX, positionY); // Set position based on calculated x and y

        window.draw(playerBall); // Draw the player ball
    }
}


void GUI::drawGameInfo() {
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Couldn't load font!" << std::endl;
    }
    Dice dice = game.getDice();
    std::stringstream roundInfo;
    //roundInfo << "Round: " << game.getCurrentRound() << "\n"; // Assuming you have this function
    roundInfo << "Dice Values: " << dice.getFirst() << ", " << dice.getSecond(); // Replace with actual values

    sf::Text roundText(roundInfo.str(), font, 24);
    roundText.setFillColor(sf::Color::White);
    roundText.setPosition(1000, 10); // Adjust position as needed
    window.draw(roundText);
}


void GUI::displayText(const std::string& message) {
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        std::cerr << "couldn't load font" << std::endl;
    }
    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setString(message);
    text.setPosition(10, 10);

    // Display the message
    window.draw(text);
    window.display();
}