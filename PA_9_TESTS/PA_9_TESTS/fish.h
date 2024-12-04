#pragma once
#include "GameEntity.h"

class Fish : public GameEntity {
public:
    Fish(float x, float y);
    ~Fish() override;

    void draw(sf::RenderWindow& window) override;
    sf::Vector2f getPosition() const override;
    void update(float deltaTime) override;  // Implement the update method

private:
    sf::CircleShape shape;
};