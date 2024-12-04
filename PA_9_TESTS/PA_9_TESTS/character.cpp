#include "Character.h"

Character::Character(float x, float y) : speed(50.0f) {
    shape.setSize(sf::Vector2f(25.0f, 25.0f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}

void Character::move(sf::Vector2f direction) {
    shape.move(direction);
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Character::getPosition() const {
    return shape.getPosition();
}

void Character::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

void Character::update(float deltaTime) {

}