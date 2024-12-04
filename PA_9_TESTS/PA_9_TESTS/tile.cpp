#include "Tile.h"

Tile::Tile()
    : window(nullptr), fishPtr(nullptr), selected(false), fish(false), x(0.f), y(0.f), defaultColor(sf::Color::Blue) {
    shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setPosition(sf::Vector2f(0.f, 0.f));
    shape.setFillColor(defaultColor);
}

Tile::Tile(sf::RenderWindow* window, float x, float y)
    : window(window), fishPtr(nullptr), selected(false), fish(false), x(x), y(y), defaultColor(sf::Color::Blue) {
    shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(defaultColor);
}

Tile::~Tile() {
    delete fishPtr; // Free fish memory if allocated
}

void Tile::setColor(sf::Color color) {
    defaultColor = color;
    shape.setFillColor(defaultColor);
}

void Tile::update(bool isSelected, bool isFish) {
    selected = isSelected;
    fish = isFish;

    if (selected) {
        shape.setFillColor(sf::Color::Green); // Highlight selected tile
    }
    else if (fish) {
        shape.setFillColor(sf::Color::Yellow); // Indicate fish presence
    }
    else {
        shape.setFillColor(defaultColor);
    }
}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Tile::hasFish() const {
    return fish;
}

void Tile::setFish(bool hasFish) {
    fish = hasFish;
    if (hasFish) {
        if (!fishPtr) {
            fishPtr = new Fish(x, y); // Create a new Fish object with tile's position
        }
    }
    else {
        delete fishPtr;  // Free memory if the fish is removed
        fishPtr = nullptr;
    }
}

void Tile::catchFish() {
    if (fish) {
        fish = false;        // Remove the fish
        delete fishPtr;      // Free the memory
        fishPtr = nullptr;   // Reset pointer
    }
}