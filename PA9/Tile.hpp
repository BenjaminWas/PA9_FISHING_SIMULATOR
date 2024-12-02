/*
Tile Class
friend of Lake so no getter or setters

*/
#include "Fish.hpp"

class Lake;

class Tile
{
	friend class Lake;
public:
	//
	Tile();
	~Tile();
	//
	void update(bool, bool);
private:
	Fish* fishPtr;
	bool selected, fish;
};
//
Tile::Tile()
{
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