#pragma once
#include "Lake.h"
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Test {
public:
    Test();
    void testLakeGen();   // Lake Generation
    void testFishSpawn(); // Fish Spawn Event
    void testUserMove();  // Tests user can move
    void testFishCatch(); // Tests catching fish updates the tile
    void testUpdate();    // Tests lake updates after fish is caught

private:
    sf::RenderWindow testWindow; // Render window for tests
};
