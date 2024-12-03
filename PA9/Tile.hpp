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
	Tile(sf::RenderWindow*, float, float);
	~Tile();
	//
	void update(bool, bool);
private:
	sf::RenderWindow* window;
	Fish* fishPtr;
	bool selected, fish;
	float x, y;
};
//
Tile::Tile(sf::RenderWindow* window, float x, float y)
{
	this->window = window;
	this->x = x;
	this->y = y;
	fishPtr = nullptr;
	selected = false;
	fish = false;
}
Tile::~Tile()
{
	delete(fishPtr);
}
//
void Tile::update(bool isSelected, bool isFish)
{
	if (selected) {
		if (fish) {

		}
		else {

		}
	}
	else {
		if (fish) {

		}
		else {

		}
	}
}