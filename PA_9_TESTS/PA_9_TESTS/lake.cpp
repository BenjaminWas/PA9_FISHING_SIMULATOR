#include "Lake.h"
#include <cmath>

/*************************************************************
* Function: Lake::Lake(sf::RenderWindow* window)            *
* Date Created: 12/2/2024                                    *
* Date Last Modified:                                        *
* Description: Constructor for the Lake class. Initializes   *
*              the lake grid, creates tiles, and sets up the *
*              pier and shadow.                              *
* Input parameters:                                          *
*   - sf::RenderWindow* window: Pointer to the SFML window.  *
* Returns: None.                                             *
* Preconditions: The window must be initialized.             *
* Postconditions: The lake is initialized with tiles, a pier,*
*                 and a shadow.                              *
*************************************************************/
Lake::Lake(sf::RenderWindow* window) : window(window) {
    lake = new Tile * [MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; ++i) {
        lake[i] = new Tile[MAX_SIZE];
    }
    createTiles();
    createPier();
}

/*************************************************************
* Function: Lake::~Lake()                                    *
* Date Created: 12/2/2024                                    *
* Date Last Modified:                                        *
* Description: Destructor for the Lake class. Frees the      *
*              memory allocated for the lake grid.           *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: A Lake object must exist.                   *
* Postconditions: All allocated memory for the lake grid is  *
*                 released.                                  *
*************************************************************/
Lake::~Lake() {
    for (int i = 0; i < MAX_SIZE; ++i) {
        delete[] lake[i];
    }
    delete[] lake;
}

/*************************************************************
* Function: createTiles()                                    *
* Date Created: 12/2/2024                                    *
* Date Last Modified:                                        *
* Description: Initializes the tiles in the lake. Sets       *
*              their colors based on their position to       *
*              create a gradient effect for the water and    *
*              a sand color for the beach.                   *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: The lake array must be initialized.         *
* Postconditions: All tiles are set with appropriate colors  *
*                 and positions.                             *
*************************************************************/
void Lake::createTiles() {
    for (int y = 0; y < MAX_SIZE; ++y) {
        for (int x = 0; x < MAX_SIZE; ++x) {
            float tileX = static_cast<float>(x * TILE_SIZE);
            float tileY = static_cast<float>(y * TILE_SIZE);

            lake[y][x] = Tile(window, tileX, tileY);

            if (y > MAX_SIZE - 10) { // Beach area
                lake[y][x].setColor(sf::Color(237, 201, 175)); // Sand color
            }
            else { // Water area
                float gradientFactor = static_cast<float>(y) / (MAX_SIZE - 10);
                sf::Color waterColor = sf::Color(
                    static_cast<sf::Uint8>(0 + gradientFactor * 55),  // R: gradient from 0 to 55
                    static_cast<sf::Uint8>(105 + gradientFactor * 50), // G: gradient from 105 to 155
                    static_cast<sf::Uint8>(148 + gradientFactor * 100) // B: gradient from 148 to 255
                );
                lake[y][x].setColor(waterColor);
            }
        }
    }
}

/*************************************************************
* Function: createPier()                                     *
* Date Created: 12/2/2024                                    *
* Date Last Modified:                                        *
* Description: Creates the pier and its shadow. Sets the     *
*              size, position, and color for both the pier   *
*              and its shadow.                               *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: The window must be initialized.             *
* Postconditions: The pier and its shadow are set up in the  *
*                 lake.                                      *
*************************************************************/
void Lake::createPier() {
    pier.setSize(sf::Vector2f(180.0f, 300.0f));
    pier.setPosition((MAX_SIZE * TILE_SIZE) / 2.f - pier.getSize().x / 2.f, (MAX_SIZE - 18) * TILE_SIZE);
    pier.setFillColor(sf::Color(139, 69, 19));

    shadow.setSize(sf::Vector2f(193.0f, 308.0f));
    shadow.setPosition(pier.getPosition().x - 6.5f, pier.getPosition().y - 6.5f);
    shadow.setFillColor(sf::Color(0, 0, 0, 100));
}

/*************************************************************
* Function: update(sf::Vector2i mousePosition)               *
* Date Created: 12/2/2024                                    *
* Date Last Modified:                                        *
* Description: Updates the lake tiles based on the mouse     *
*              position, highlighting tiles under the cursor.*
* Input parameters:                                          *
*   - sf::Vector2i mousePosition: The current position of the*
*     mouse in the window.                                   *
* Returns: None.                                             *
* Preconditions: The lake array and window must be properly  *
*                initialized.                                *
* Postconditions: Tiles under the mouse cursor are           *
*                 highlighted.                               *
*************************************************************/
void Lake::update(sf::Vector2i mousePosition) {
    for (int y = 0; y < MAX_SIZE; ++y) {
        for (int x = 0; x < MAX_SIZE; ++x) {
            sf::FloatRect tileBounds(
                static_cast<float>(x * TILE_SIZE),
                static_cast<float>(y * TILE_SIZE),
                static_cast<float>(TILE_SIZE),
                static_cast<float>(TILE_SIZE)
            );

            bool isMouseOver = tileBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
            lake[y][x].update(isMouseOver, lake[y][x].hasFish());
        }
    }
}

/*************************************************************
* Function: draw()                                           *
* Date Created: 12/2/2024                                    *
* Date Last Modified:                                        *
* Description: Draws all lake tiles, the pier, and its shadow*
*              to the render window.                         *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: The lake array, pier, and shadow must be    *
*                properly initialized.                       *
* Postconditions: The lake, pier, and shadow are rendered to *
*                 the window.                                *
*************************************************************/
void Lake::draw() {
    for (int y = 0; y < MAX_SIZE; ++y) {
        for (int x = 0; x < MAX_SIZE; ++x) {
            lake[y][x].draw(*window);
        }
    }

    window->draw(shadow);
    window->draw(pier);
}

/*************************************************************
* Function: fishEvent(bool fish, int x, int y)               *
* Date Created: 12/2/2024                                    *
* Date Last Modified:                                        *
* Description: Adds or removes a fish from a specific tile in*
*              the lake.                                     *
* Input parameters:                                          *
*   - bool fish: True to add a fish, false to remove it.     *
*   - int x: X-coordinate of the tile.                      *
*   - int y: Y-coordinate of the tile.                      *
* Returns: None.                                             *
* Preconditions: The coordinates must be within the lake's   *
*                bounds.                                     *
* Postconditions: The tile's fish state is updated.          *
*************************************************************/
void Lake::fishEvent(bool fish, int x, int y) {
    if (x >= 0 && x < MAX_SIZE && y >= 0 && y < MAX_SIZE) {
        lake[y][x].setFish(fish);
    }
}

/*************************************************************
* Function: tryCatchFish(int x, int y)                       *
* Date Created: 12/2/2024                                    *
* Date Last Modified:                                        *
* Description: Attempts to catch a fish from a specific tile.*
*              If successful, the fish is removed, and true  *
*              is returned.                                  *
* Input parameters:                                          *
*   - int x: X-coordinate of the tile.                      *
*   - int y: Y-coordinate of the tile.                      *
* Returns: bool: True if a fish was caught, false otherwise. *
* Preconditions: The coordinates must be within the lake's   *
*                bounds.                                     *
* Postconditions: The tile's fish state is updated.          *
*************************************************************/
bool Lake::tryCatchFish(int x, int y) {
    if (x >= 0 && x < MAX_SIZE && y >= 0 && y < MAX_SIZE) {
        if (lake[y][x].hasFish()) {
            lake[y][x].catchFish();
            return true;
        }
    }
    return false;
}

/*************************************************************
* Function: getFishCount() const                             *
* Date Created: 12/2/2024                                    *
* Date Last Modified:                                        *
* Description: Counts the total number of tiles in the lake  *
*              that currently contain fish.                  *
* Input parameters: None.                                    *
* Returns: int: The number of tiles with fish.               *
* Preconditions: The lake array must be initialized.         *
* Postconditions: The total fish count is returned.          *
*************************************************************/
int Lake::getFishCount() const {
    int count = 0;
    for (int y = 0; y < MAX_SIZE; ++y) {
        for (int x = 0; x < MAX_SIZE; ++x) {
            if (lake[y][x].hasFish()) {
                count++;
            }
        }
    }
    return count;
}
