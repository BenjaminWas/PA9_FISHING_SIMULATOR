#include "Test.h"


Test::Test()
    : testWindow(sf::VideoMode(MAX_SIZE* TILE_SIZE, MAX_SIZE* TILE_SIZE), "Test Window", sf::Style::Close) {}

/*************************************************************
* Function: testLakeGen()                                    *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Tests the lake generation by verifying that   *
*              all tiles in the lake initially do not have   *
*              fish.                                         *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: The Lake object must be properly initialized*
*                and contain a lake array.                   *
* Postconditions: Outputs test result indicating whether     *
*                 lake generation passed or failed.          *
*************************************************************/
void Test::testLakeGen() {
    Lake lake(&testWindow);
    for (int y = 0; y < MAX_SIZE; ++y) {
        for (int x = 0; x < MAX_SIZE; ++x) {
            if (lake.lake[y][x].hasFish() != false) {
                std::cout << "Error in Lake Generation" << std::endl;
                return;
            }
        }
    }
    std::cout << "testLakeGen: Passed" << std::endl;
}

/*************************************************************
* Function: testFishSpawn()                                  *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Tests the spawning of a fish at a specific    *
*              location in the lake and verifies the tile    *
*              is updated correctly.                         *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: The Lake object and fishEvent function must *
*                be implemented and functional.              *
* Postconditions: Outputs test result for fish spawning.     *
*************************************************************/
void Test::testFishSpawn() {
    Lake lake(&testWindow);
    lake.fishEvent(true, 0, 0);
    if (lake.lake[0][0].hasFish() != true) {
        std::cout << "Fish Event Failed" << std::endl;
    }
    else {
        std::cout << "testFishSpawn: Passed" << std::endl;
    }
}

/*************************************************************
* Function: testUserMove()                                   *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Tests the movement of a character by setting  *
*              its position and verifying that it matches    *
*              the expected coordinates.                     *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: Character class and setPosition function    *
*                must be implemented and functional.         *
* Postconditions: Outputs test result for user movement.     *
*************************************************************/
void Test::testUserMove() {
    sf::Vector2i vector(1, 1);
    Character character((MAX_SIZE * TILE_SIZE) / 2.0f, (MAX_SIZE - 10) * TILE_SIZE);
    character.setPosition(1, 1);
    if (character.getPosition().x != vector.x || character.getPosition().y != vector.y) {
        std::cout << "Error within character movement" << std::endl;
    }
    else {
        std::cout << "testUserMove: Passed" << std::endl;
    }
}

/*************************************************************
* Function: testFishCatch()                                  *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Tests the functionality of catching a fish by *
*              spawning a fish at a specific location,       *
*              catching it, and verifying that the tile is   *
*              updated correctly.                            *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: Lake and catchFish functions must be        *
*                implemented and functional.                 *
* Postconditions: Outputs test result for fish catching.     *
*************************************************************/
void Test::testFishCatch() {
    Lake lake(&testWindow);
    lake.fishEvent(true, 0, 0);
    lake.lake[0][0].catchFish();
    if (lake.lake[0][0].hasFish() != false) {
        std::cout << "Tile did not update *fish" << std::endl;
    }
    else {
        std::cout << "testFishCatch: Passed" << std::endl;
    }
}

/*************************************************************
* Function: testUpdate()                                     *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Tests the lake's update functionality by      *
*              catching a fish and ensuring the tile         *
*              updates correctly after the update is called. *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: Lake and update functions must be           *
*                implemented and functional.                 *
* Postconditions: Outputs test result for lake update.       *
*************************************************************/
void Test::testUpdate() {
    sf::Vector2i vector(0, 0);
    Lake lake(&testWindow);
    lake.fishEvent(true, 0, 0);
    lake.lake[0][0].catchFish();
    lake.update(vector);
    if (lake.lake[0][0].hasFish() != false) {
        std::cout << "Lake did not update tile" << std::endl;
    }
    else {
        std::cout << "testUpdate: Passed" << std::endl;
    }
}
