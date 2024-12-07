#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>

#define MAX_SIZE 30

class Lake {
public:

    friend class Test;

    Lake(sf::RenderWindow* window);
    ~Lake();

    void createTiles();
    void draw();
    void update(sf::Vector2i mousePosition);
    void fishEvent(bool fish, int x, int y);
    bool tryCatchFish(int x, int y);
    int getFishCount() const;

private:
    Tile** lake;
    sf::RectangleShape pier;
    sf::RectangleShape shadow;
    sf::RenderWindow* window;

    sf::Texture beachTexture;
    sf::Texture waterTexture;

    void createPier();
};