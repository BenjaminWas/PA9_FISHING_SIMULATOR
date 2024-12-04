#pragma once
#include <SFML/Graphics.hpp>

class GameEntity {
public:
    virtual ~GameEntity() = default;                     // Virtual destructor
    virtual void draw(sf::RenderWindow& window) = 0;     // Pure virtual draw
    virtual sf::Vector2f getPosition() const = 0;        // Pure virtual getPosition
    virtual void update(float deltaTime) = 0;            // Pure virtual update
};