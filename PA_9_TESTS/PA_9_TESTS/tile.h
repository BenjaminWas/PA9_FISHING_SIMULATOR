#pragma once
#include "Fish.h"
#include <SFML/Graphics.hpp>

#define TILE_SIZE 25

class Tile {
public:
    Tile();                                    // Default constructor
    Tile(sf::RenderWindow* window, float x, float y); // Constructor with position
    ~Tile();                                   // Destructor

    void setColor(sf::Color color);            // Set the color of the tile
    void update(bool isSelected, bool isFish); // Update state
    void draw(sf::RenderWindow& window);       // Draw the tile
    bool hasFish() const;                      // Check if the tile has a fish
    void setFish(bool hasFish);                // Set whether the tile contains a fish
    void catchFish();                          // Catch the fish (remove it)

private:
    sf::RenderWindow* window;                 // Pointer to the render window
    sf::RectangleShape shape;                 // Visual representation of the tile
    sf::Color defaultColor;                   // Default color of the tile (water/beach)
    Fish* fishPtr;                            // Pointer to a fish (if any)
    bool selected;                            // Whether the tile is selected
    bool fish;                                // Whether the tile contains a fish
    float x, y;                               // Position of the tile
};