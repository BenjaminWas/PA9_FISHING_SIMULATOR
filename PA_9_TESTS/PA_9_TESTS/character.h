#pragma once
#include "GameEntity.h"

class Character : public GameEntity {
public:
    Character(float x, float y);
    void move(sf::Vector2f direction);
    void draw(sf::RenderWindow& window) override;
    sf::Vector2f getPosition() const override;
    void update(float deltaTime) override;  // Implement the update method
    void setPosition(float x, float y);

private:
    sf::RectangleShape shape;
    float speed;
};