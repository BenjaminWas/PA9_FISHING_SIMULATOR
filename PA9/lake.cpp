#include "lake.hpp"
#include <cmath> 

Lake::Lake(sf::RenderWindow* window) : window(window) {
    createTiles();
    createPier();
}

void Lake::createTiles() {
    for (int y = 0; y < MAX_SIZE; ++y) {
        for (int x = 0; x < MAX_SIZE; ++x) {
            sf::Vector2f position(x * 40.f, y * 40.f); 
            sf::Vector2f size(40.f, 40.f);
           
            if (y > 18) { 
                float grain = std::sin(x * 0.1f + y * 0.1f) * 5.0f;
                sf::Color color(237 + grain / 2, 201 + grain / 4, 175); 
                lake[y][x] = Tile(position, size, color);
            }
            else { 
                float ripple = std::sin(x * 0.03f + y * 0.03f) * 5.0f;
                float shallowFactor = static_cast<float>(y) / MAX_SIZE;
                sf::Color color(
                    static_cast<sf::Uint8>(0 + shallowFactor * 55),
                    static_cast<sf::Uint8>(105 + shallowFactor * 50),
                    static_cast<sf::Uint8>(148 + shallowFactor * 30)
                );
                lake[y][x] = Tile(position, size, color);
            }
        }
    }
}

void Lake::createPier() {
    pier.setSize(sf::Vector2f(180.0f, 350.0f));
    pier.setPosition(500.f, 460.f); 
    pier.setFillColor(sf::Color(139, 69, 19));

    shadow.setSize(sf::Vector2f(193.0f, 358.0f));
    shadow.setPosition(498.5f, 453.5f); 
    shadow.setFillColor(sf::Color(0, 0, 0, 100));
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
