/**/
#pragma once
#include "Tile.hpp"
#define MAX_SIZE 25
#include <SFML/Graphics.hpp>

class Lake
{
public:
	Lake(sf::RenderWindow* window, sf::Texture& waterTexture, sf::Texture& dockTexture); 
	void draw();

private:
	Tile lake[MAX_SIZE][MAX_SIZE]; // 25x25


};