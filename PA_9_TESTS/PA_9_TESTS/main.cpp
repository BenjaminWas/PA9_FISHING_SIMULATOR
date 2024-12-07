/*******************************************************************************************
* Programmer:  Naven Laya, Benjamin Wasisco, Colette Addah
* Class: CptS 122, Fall 2024; Lab Section 6
* Programming Assignment: PA 9
* Date: December 6, 2024
* Description: This program implements a 2D Fishing Simulator game. The game includes a
*              main gameplay mode where players can move around using WASD keys and attempt
*              to catch fish by clicking on tiles containing fish. Once a fish is caught,
*              players transition to a mini-game mode where they control a bait to catch
*              moving fish. 
*******************************************************************************************/




#include "Lake.h"
#include "Character.h"
#include "menu.h"
#include "Test.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>


enum class GameState {
    MainGame,
    MiniGame
};

void runMiniGame(sf::RenderWindow& window, GameState& gameState, int& score);

int main() {

    // Run unit tests for game components
    Test tester;
    tester.testLakeGen();
    tester.testFishSpawn();
    tester.testUserMove();
    tester.testFishCatch();
    tester.testUpdate();

    // Display the start menu
    Menu* menu = new Menu();
    menu->run();   // Display the menu and wait for input
    delete menu;   // Clean up the menu instance
    menu = nullptr;

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Create the main game window
    sf::RenderWindow window(
        sf::VideoMode(MAX_SIZE * TILE_SIZE, MAX_SIZE * TILE_SIZE),
        "Fishing Simulator",
        sf::Style::Close
    );

    // Initialize game objects
    Lake lake(&window); // Create the lake object
    Character character((MAX_SIZE * TILE_SIZE) / 2.0f, (MAX_SIZE - 10) * TILE_SIZE); // Create the player character

    // Initialize timing and score variables
    sf::Clock spawnClock;     // Tracks time for fish spawning
    sf::Clock deltaClock;     // Tracks time for frame updates
    int score = 0;            // Tracks the player's score
    float movementSpeed = 100.0f; // Controls the player's movement speed

    // Load font for on-screen text
    sf::Font font;
    if (!font.loadFromFile("Oswald-Regular.ttf")) {
        std::cerr << "Error: Could not load font file 'Oswald-Regular.ttf'" << std::endl;
        return 1; // Exit if the font file is missing
    }

    // Set up instructions text
    sf::Text instructions("WASD to move, click to catch fish", font, 20);
    instructions.setPosition(10.f, 10.f);

    // Set up score text
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 40.f);
    scoreText.setString("Fishes Caught: 0");

    // Set the initial game state
    GameState gameState = GameState::MainGame;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        // Handle events such as window close and mouse clicks
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (gameState == GameState::MainGame) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    int tileX = mousePosition.x / TILE_SIZE;
                    int tileY = mousePosition.y / TILE_SIZE;

                    if (lake.tryCatchFish(tileX, tileY)) {
                        gameState = GameState::MiniGame; // Transition to mini-game on fish catch
                    }
                }
            }
        }

        float deltaTime = deltaClock.restart().asSeconds(); // Calculate frame time

        if (gameState == GameState::MainGame) {
            // Handle player movement using WASD keys
            sf::Vector2f direction(0.f, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x += 1;

            // Normalize movement direction
            if (direction.x != 0 || direction.y != 0) {
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                direction /= length;
            }

            // Calculate new position and constrain to valid areas
            sf::Vector2f newPosition = character.getPosition() + direction * movementSpeed * deltaTime;
            float pierLeft = (MAX_SIZE / 2 - 4) * TILE_SIZE;  // Pier's left boundary
            float pierRight = (MAX_SIZE / 2 + 3) * TILE_SIZE; // Pier's right boundary
            float pierTop = (MAX_SIZE - 18) * TILE_SIZE;      // Pier's top boundary
            float beachTop = (MAX_SIZE - 10) * TILE_SIZE;     // Beach area

            if ((newPosition.y >= pierTop && newPosition.x >= pierLeft && newPosition.x <= pierRight) ||
                (newPosition.y >= beachTop)) {
                character.setPosition(newPosition.x, newPosition.y);
            }

            // Spawn fish at random intervals if the lake's fish count is below the limit
            if (spawnClock.getElapsedTime().asSeconds() >= 5 && lake.getFishCount() < 10) {
                int spawnX = rand() % MAX_SIZE;
                int spawnY = rand() % (MAX_SIZE - 10);
                lake.fishEvent(true, spawnX, spawnY);
                spawnClock.restart();
            }

            // Render game objects
            window.clear();
            lake.update(sf::Mouse::getPosition(window)); // Update lake tiles
            lake.draw();                                // Draw the lake
            character.draw(window);                    // Draw the character
            window.draw(instructions);                 // Draw instructions text
            scoreText.setString("Fishes Caught: " + std::to_string(score));
            window.draw(scoreText);                    // Draw score text
        }
        else if (gameState == GameState::MiniGame) {
            runMiniGame(window, gameState, score); // Run the mini-game
        }

        window.display(); // Display the frame
    }

    return 0; // Exit the program successfully
}


/*************************************************************
* Function: runMiniGame()                                    *
* Date Created: 12/4/2024                                    *
* Date Last Modified:                                        *
* Description: Handles the mini-game logic for catching fish.*
*              Players move a bait to collide with fish that *
*              spawn randomly on the screen. On collision,   *
*              the score is incremented, and the game        *
*              transitions back to the main game.            *
* Input parameters:                                          *
*   - sf::RenderWindow& window: Reference to the game window *
*   - GameState& gameState: Reference to the game state      *
*   - int& score: Reference to the player's score            *
* Returns: None.                                             *
* Preconditions: Textures and game window must be properly   *
*                initialized.                                *
* Postconditions: Mini-game state is updated, and score is   *
*                 incremented on success.                    *
*************************************************************/
void runMiniGame(sf::RenderWindow& window, GameState& gameState, int& score) {
    static sf::CircleShape bait(10.f);
    static std::vector<sf::Sprite> fishSprites;
    static std::vector<sf::Vector2f> fishVelocities;
    static sf::Clock fishSpawnClock;
    static sf::Clock deltaClock;

    static bool resetMiniGame = true;

    // Load textures only once
    static sf::Texture fishTextureGreen;
    static sf::Texture fishTextureBlue;
    static sf::Texture fishTextureRed;
    static bool texturesLoaded = false;

    if (!texturesLoaded) {
        if (!fishTextureGreen.loadFromFile("fishTile_072.png") ||
            !fishTextureBlue.loadFromFile("fishTile_076.png") ||
            !fishTextureRed.loadFromFile("fishTile_078.png")) {
            std::cerr << "Error: Could not load fish sprites!" << std::endl;
            return;
        }
        texturesLoaded = true;
    }

    if (resetMiniGame) {
        fishSprites.clear();
        fishVelocities.clear();
        bait.setFillColor(sf::Color::Red);
        bait.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
        resetMiniGame = false;
    }

    float deltaTime = deltaClock.restart().asSeconds();

    sf::Font font;
    if (!font.loadFromFile("Oswald-Regular.ttf")) {
        std::cerr << "Error: Could not load font file 'Oswald-Regular.ttf'" << std::endl;
    }

    sf::Text instructions("Move hook using W for up, and S for down", font, 20);
    instructions.setPosition(10.f, 10.f);


    // Spawn fish off-screen
    if (fishSpawnClock.getElapsedTime().asSeconds() > 3.f) { // Adjust spawn interval as needed
        sf::Sprite newFish;

        // Randomly assign a texture
        int textureChoice = rand() % 3;
        switch (textureChoice) {
        case 0:
            newFish.setTexture(fishTextureGreen);
            break;
        case 1:
            newFish.setTexture(fishTextureBlue);
            break;
        case 2:
            newFish.setTexture(fishTextureRed);
            break;
        }

        float side = rand() % 2; // 0 for left, 1 for right
        float yPos = rand() % window.getSize().y;

        // Randomize the size (scale)
        float randomScale = static_cast<float>(rand() % 5 + 5) / 10.f; // Scale between 0.5 and 1.0
        if (side == 0) {
            newFish.setPosition(-newFish.getGlobalBounds().width, yPos); // Spawn on left side
            fishVelocities.emplace_back(100.f, 0.f); // Move to the right
            newFish.setScale(randomScale, randomScale); // Normal orientation with random size
        }
        else {
            newFish.setPosition(window.getSize().x, yPos); // Spawn on right side
            fishVelocities.emplace_back(-100.f, 0.f); // Move to the left
            newFish.setScale(-randomScale, randomScale); // Flip horizontally with random size
        }

        fishSprites.push_back(newFish);
        fishSpawnClock.restart();
    }



    // Move bait using W and S keys
    sf::Vector2f direction(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.f; // Move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.f; // Move down

    if (direction.y != 0.f) {
        direction.y /= std::abs(direction.y); // Normalize to -1, 0, or 1
    }

    // Apply movement to the bait
    bait.move(0.f, direction.y * 100.f * deltaTime);

    // Keep bait within screen bounds
    if (bait.getPosition().y < 0) {
        bait.setPosition(bait.getPosition().x, 0);
    }
    if (bait.getPosition().y > window.getSize().y - bait.getRadius() * 2) {
        bait.setPosition(bait.getPosition().x, window.getSize().y - bait.getRadius() * 2);
    }

    // Move fish across the screen
    for (size_t i = 0; i < fishSprites.size(); ++i) {
        fishSprites[i].move(fishVelocities[i] * deltaTime);

        // Check collision with bait
        if (fishSprites[i].getGlobalBounds().intersects(bait.getGlobalBounds())) {
            fishSprites.erase(fishSprites.begin() + i);
            fishVelocities.erase(fishVelocities.begin() + i);
            score++; // Update score
            gameState = GameState::MainGame; // Return to main game
            resetMiniGame = true;
            return;
        }
    }

    // Draw gradient background
    const int gradientSteps = 20;
    sf::RectangleShape gradientLayer(sf::Vector2f(window.getSize().x, window.getSize().y / gradientSteps));
    for (int i = 0; i < gradientSteps; ++i) {
        float colorIntensity = 255 - (i * (255.0f / gradientSteps));
        gradientLayer.setFillColor(sf::Color(0, static_cast<sf::Uint8>(colorIntensity / 2), static_cast<sf::Uint8>(colorIntensity)));
        gradientLayer.setPosition(0, i * (window.getSize().y / gradientSteps));
        window.draw(gradientLayer);
    }

    // Draw the fishing line
    sf::VertexArray fishingLine(sf::Lines, 2);
    fishingLine[0].position = sf::Vector2f(window.getSize().x / 2.f, 0.f); // Fixed point
    fishingLine[0].color = sf::Color::Black;
    fishingLine[1].position = bait.getPosition() + sf::Vector2f(bait.getRadius(), bait.getRadius()); // Center of bait
    fishingLine[1].color = sf::Color::Black;

    // Draw mini-game elements
    window.draw(fishingLine);
    window.draw(bait);
    window.draw(instructions);
    for (const auto& fish : fishSprites) {
        window.draw(fish);
    }
}
