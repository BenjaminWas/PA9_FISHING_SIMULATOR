#include "Lake.h"
#include "Character.h"
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
    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window(
        sf::VideoMode(MAX_SIZE * TILE_SIZE, MAX_SIZE * TILE_SIZE),
        "Fishing Simulator",
        sf::Style::Close
    );

    Lake lake(&window);
    Character character((MAX_SIZE * TILE_SIZE) / 2.0f, (MAX_SIZE - 10) * TILE_SIZE);

    sf::Clock spawnClock;
    sf::Clock deltaClock;
    int score = 0;
    float movementSpeed = 100.0f;

    sf::Font font;
    if (!font.loadFromFile("Oswald-Regular.ttf")) {
        std::cerr << "Error: Could not load font file 'Oswald-Regular.ttf'" << std::endl;
        return 1;
    }

    sf::Text instructions("WASD to move, click to catch fish", font, 20);
    instructions.setPosition(10.f, 10.f);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 40.f);
    scoreText.setString("Fishes Caught: 0");

    GameState gameState = GameState::MainGame;

    while (window.isOpen()) {
        sf::Event event;
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
                        gameState = GameState::MiniGame;
                    }
                }
            }
        }

        float deltaTime = deltaClock.restart().asSeconds();

        if (gameState == GameState::MainGame) {
            sf::Vector2f direction(0.f, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x += 1;

            if (direction.x != 0 || direction.y != 0) {
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                direction /= length;
            }

            sf::Vector2f newPosition = character.getPosition() + direction * movementSpeed * deltaTime;

            // Constrain movement to the pier or beach
            float pierLeft = (MAX_SIZE / 2 - 4) * TILE_SIZE;  // Pier's left boundary
            float pierRight = (MAX_SIZE / 2 + 3) * TILE_SIZE; // Pier's right boundary
            float pierTop = (MAX_SIZE - 18) * TILE_SIZE;      // Pier's top boundary
            float beachTop = (MAX_SIZE - 10) * TILE_SIZE;     // Beach starts here

            if ((newPosition.y >= pierTop && newPosition.x >= pierLeft && newPosition.x <= pierRight) ||
                (newPosition.y >= beachTop)) {
                character.setPosition(newPosition.x, newPosition.y); // Valid movement area
            }

            if (spawnClock.getElapsedTime().asSeconds() >= 5 && lake.getFishCount() < 10) {
                int spawnX = rand() % MAX_SIZE;
                int spawnY = rand() % (MAX_SIZE - 10);
                lake.fishEvent(true, spawnX, spawnY);
                spawnClock.restart();
            }

            window.clear();
            lake.update(sf::Mouse::getPosition(window));
            lake.draw();
            character.draw(window);
            window.draw(instructions);
            scoreText.setString("Fishes Caught: " + std::to_string(score));
            window.draw(scoreText);
        }
        else if (gameState == GameState::MiniGame) {
            runMiniGame(window, gameState, score);
        }

        window.display();
    }

    return 0;
}

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
    for (const auto& fish : fishSprites) {
        window.draw(fish);
    }
}

