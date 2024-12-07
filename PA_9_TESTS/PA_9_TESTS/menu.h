#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
    sf::RenderWindow* window;
    sf::Font* font;
    sf::Texture* backgroundTexture;
    sf::Sprite* background;
    sf::Sprite* startGameSprite;
    sf::Text startGameText;
    sf::Text instructionsText;

protected:
    void set_values();
    void handle_events();
    void draw_menu();

public:
    Menu();
    ~Menu();
    void run();
};