#include "Lake.hpp"

Lake::Lake(sf::RenderWindow* window, sf::Texture& waterTexture, sf::Texture& dockTexture) {
    
    
    
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (j >= MAX_SIZE / 2) {
                // Water tile
                lake[i][j] = Tile(window, i * TILE_SIZE, j * TILE_SIZE, waterTexture);
            }
            else if (j == MAX_SIZE / 2 - 1 && i >= 8 && i < 16) {
                // Dock tile
                lake[i][j] = Tile(window, i * TILE_SIZE, j * TILE_SIZE, dockTexture);
            }
        }
    }
}

void Lake::draw() {
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            lake[i][j].draw();
        }
    }
}
