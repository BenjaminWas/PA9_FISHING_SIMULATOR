#include "Lake.h"
#include <cmath>

Lake::Lake(sf::RenderWindow* window) : window(window) {
    lake = new Tile * [MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; ++i) {
        lake[i] = new Tile[MAX_SIZE];
    }
    createTiles();
    createPier();
}

Lake::~Lake() {
    for (int i = 0; i < MAX_SIZE; ++i) {
        delete[] lake[i];
    }
    delete[] lake;
}

void Lake::createTiles() {
    for (int y = 0; y < MAX_SIZE; ++y) {
        for (int x = 0; x < MAX_SIZE; ++x) {
            float tileX = static_cast<float>(x * TILE_SIZE);
            float tileY = static_cast<float>(y * TILE_SIZE);

            lake[y][x] = Tile(window, tileX, tileY);

            if (y > MAX_SIZE - 10) { // Beach area
                lake[y][x].setColor(sf::Color(237, 201, 175)); // Sand color
            }
            else { // Water area
                float gradientFactor = static_cast<float>(y) / (MAX_SIZE - 10);
                sf::Color waterColor = sf::Color(
                    static_cast<sf::Uint8>(0 + gradientFactor * 55),  // R: gradient from 0 to 55
                    static_cast<sf::Uint8>(105 + gradientFactor * 50), // G: gradient from 105 to 155
                    static_cast<sf::Uint8>(148 + gradientFactor * 100) // B: gradient from 148 to 255
                );
                lake[y][x].setColor(waterColor);
            }
        }
    }
}


void Lake::createPier() {
    pier.setSize(sf::Vector2f(180.0f, 300.0f));
    pier.setPosition((MAX_SIZE * TILE_SIZE) / 2.f - pier.getSize().x / 2.f, (MAX_SIZE - 18) * TILE_SIZE);
    pier.setFillColor(sf::Color(139, 69, 19));

    shadow.setSize(sf::Vector2f(193.0f, 308.0f));
    shadow.setPosition(pier.getPosition().x - 6.5f, pier.getPosition().y - 6.5f);
    shadow.setFillColor(sf::Color(0, 0, 0, 100));
}

void Lake::update(sf::Vector2i mousePosition) {
    for (int y = 0; y < MAX_SIZE; ++y) {
        for (int x = 0; x < MAX_SIZE; ++x) {
            sf::FloatRect tileBounds(
                static_cast<float>(x * TILE_SIZE),
                static_cast<float>(y * TILE_SIZE),
                static_cast<float>(TILE_SIZE),
                static_cast<float>(TILE_SIZE)
            );

            bool isMouseOver = tileBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
            lake[y][x].update(isMouseOver, lake[y][x].hasFish());
        }
    }
}

void Lake::draw() {
    for (int y = 0; y < MAX_SIZE; ++y) {
        for (int x = 0; x < MAX_SIZE; ++x) {
            lake[y][x].draw(*window);
        }
    }

    window->draw(shadow);
    window->draw(pier);
}

void Lake::fishEvent(bool fish, int x, int y) {
    if (x >= 0 && x < MAX_SIZE && y >= 0 && y < MAX_SIZE) {
        lake[y][x].setFish(fish);
    }
}

bool Lake::tryCatchFish(int x, int y) {
    if (x >= 0 && x < MAX_SIZE && y >= 0 && y < MAX_SIZE) {
        if (lake[y][x].hasFish()) {
            lake[y][x].catchFish();
            return true;
        }
    }
    return false;
}

int Lake::getFishCount() const {
    int count = 0;
    for (int y = 0; y < MAX_SIZE; ++y) {
        for (int x = 0; x < MAX_SIZE; ++x) {
            if (lake[y][x].hasFish()) {
                count++;
            }
        }
    }
    return count;
}