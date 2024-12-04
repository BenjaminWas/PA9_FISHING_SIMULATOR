#include "Tile.hpp"

// Default constructor
Tile::Tile() : window(nullptr) {}

// Parameterized constructor
Tile::Tile(sf::RenderWindow* window, float x, float y, sf::Texture& texture) : window(window) {
    sprite.setTexture(texture); 
    sprite.setPosition(x, y);  
    sprite.setScale(TILE_SIZE / (float)texture.getSize().x, TILE_SIZE / (float)texture.getSize().y); 
}

// Draw the tile
void Tile::draw() {
    if (window) {
        window->draw(sprite);
    }
}

Tile::~Tile() {
}