
/*
Tile Class
friend of Lake so no getter or setters

*/
#pragma once
#define TILE_SIZE 25
#include "Fish.hpp"
#include <SFML/Graphics.hpp>

class Lake;
class Tile
{
	friend class Lake;
public:
	//
	Tile();
	Tile(sf::RenderWindow*, float, float, sf::Texture& texture);
	~Tile();
	//
	void update(bool isSelected, bool isFish);

	void draw();

private:
	sf::RenderWindow* window;
	sf::Sprite sprite;
	Fish* fishPtr;
	bool selected, fish;
	float x, y;
};

