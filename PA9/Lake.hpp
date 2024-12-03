/**/
#pragma once
#include "Tile.hpp"
#define MAX_SIZE 25
#include <SFML/Graphics.hpp>

class Lake
{
public:
	Lake(sf::RenderWindow* window);
	void draw();

private:
	Tile lake[MAX_SIZE][MAX_SIZE];
	sf::RectangleShape pier;
	sf::RectangleShape shadow;
	sf::RenderWindow* window; 

	void createTiles();
	void createPier();
};
