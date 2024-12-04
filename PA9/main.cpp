/**/
#include "Lake.hpp"
#define TILE_SIZE 32
using namespace sf;

int main(void)
{
    sf::RenderWindow app(sf::VideoMode(MAX_SIZE * TILE_SIZE, MAX_SIZE * TILE_SIZE, 8), "Fishing Simulator", sf::Style::Close);
    /* For Debugging opens window
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear the screen (fill it with black color)
        app.clear();

        // Display window contents on screen
        app.display();
    }
   */

    Texture t1, t2;
    t1.loadFromFile("images/water.png");
    t2.loadFromFile("images/dock.jpeg");


    Sprite waterSprite(t1);
    Sprite woodSprite(t2);

    // Scale sprites to fit the tile 
    waterSprite.setScale(TILE_SIZE / (float)t1.getSize().x, TILE_SIZE / (float)t1.getSize().y);
    woodSprite.setScale(TILE_SIZE / (float)t2.getSize().x, TILE_SIZE / (float)t2.getSize().y
    );

    while (app.isOpen()) {
        sf::Event event;
        while (app.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        // Draw water
        for (int i = 0; i < MAX_SIZE; i++) {
            for (int j = MAX_SIZE / 2; j < MAX_SIZE; j++) { waterSprite.setPosition(i * TILE_SIZE, j * TILE_SIZE);
            app.draw(waterSprite); }
        }

        // Draw  dock 
        for (int i = 8; i < 16; i++)
        {
            woodSprite.setPosition(i * TILE_SIZE, (MAX_SIZE / 2 - 1) * TILE_SIZE);
            app.draw(woodSprite);
        }
        app.display();
    }

    return 0;
}