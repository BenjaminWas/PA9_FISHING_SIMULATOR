/*
Tile Class
friend of Lake so no getter or setters

*/
#pragma once
#include "Fish.hpp"
#include <SFML/Graphics.hpp>

class Lake;
class Tile
{
	friend class Lake;
public:
	//
	Tile(sf::Window*);
	~Tile();
	//
	void update(bool, bool);
private:
	Fish* fishPtr;
	bool selected, fish;
	sf::Window* window;
};
//
Tile::Tile(sf::Window* window)
{
	this->window = window;
	fishPtr = nullptr;
	selected = false;
	fish = false;
}
Tile::~Tile()
{
	delete(fishPtr);
}
//

//