#include "Fish.h"


Fish::Fish(float x, float y) {
    shape.setRadius(10.0f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);

   
}

Fish::~Fish() {}

void Fish::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Fish::getPosition() const {
    return shape.getPosition();
}

void Fish::update(float deltaTime) {
    // No additional logic for now; could include animations in future
}