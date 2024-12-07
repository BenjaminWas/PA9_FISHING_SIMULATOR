#include "tile.h"

/*************************************************************
* Function: Tile()                                           *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Default constructor for the Tile class.       *
*              Initializes the tile with default values,     *
*              including position (0, 0), size (TILE_SIZE),  *
*              and default color (blue).                    *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: None.                                       *
* Postconditions: A Tile object is created with default      *
*                 values and no associated fish.             *
*************************************************************/
Tile::Tile()
    : window(nullptr), fishPtr(nullptr), selected(false), fish(false), x(0.f), y(0.f), defaultColor(sf::Color::Blue) {
    shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setPosition(sf::Vector2f(0.f, 0.f));
    shape.setFillColor(defaultColor);
}

/*************************************************************
* Function: Tile(sf::RenderWindow* window, float x, float y) *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Parameterized constructor for the Tile class. *
*              Initializes the tile with a specified window, *
*              position (x, y), and default color (blue).    *
* Input parameters:                                          *
*   - sf::RenderWindow* window: Pointer to the render window *
*   - float x: X-coordinate of the tile                     *
*   - float y: Y-coordinate of the tile                     *
* Returns: None.                                             *
* Preconditions: The window pointer must be valid.           *
* Postconditions: A Tile object is created at the specified  *
*                 position with no associated fish.          *
*************************************************************/
Tile::Tile(sf::RenderWindow* window, float x, float y)
    : window(window), fishPtr(nullptr), selected(false), fish(false), x(x), y(y), defaultColor(sf::Color::Blue) {
    shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(defaultColor);
}

/*************************************************************
* Function: ~Tile()                                          *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Destructor for the Tile class. Frees any      *
*              dynamically allocated memory for the Fish     *
*              object, if present.                          *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: Tile object must exist.                     *
* Postconditions: Any allocated fish memory is released.     *
*************************************************************/
Tile::~Tile() {
    delete fishPtr; // Free fish memory if allocated
}

/*************************************************************
* Function: setColor(sf::Color color)                        *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Updates the default color of the tile and     *
*              changes its fill color accordingly.           *
* Input parameters:                                          *
*   - sf::Color color: New color for the tile                *
* Returns: None.                                             *
* Preconditions: Tile object must be initialized.            *
* Postconditions: Tile's fill color is updated.              *
*************************************************************/
void Tile::setColor(sf::Color color) {
    defaultColor = color;
    shape.setFillColor(defaultColor);
}

/*************************************************************
* Function: update(bool isSelected, bool isFish)             *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Updates the tile's state based on selection   *
*              and fish presence, and adjusts its color      *
*              accordingly.                                  *
* Input parameters:                                          *
*   - bool isSelected: Whether the tile is selected          *
*   - bool isFish: Whether the tile contains a fish          *
* Returns: None.                                             *
* Preconditions: Tile object must be initialized.            *
* Postconditions: Tile's state and color are updated.        *
*************************************************************/
void Tile::update(bool isSelected, bool isFish) {
    selected = isSelected;
    fish = isFish;

    if (selected) {
        shape.setFillColor(sf::Color::Green); // Highlight selected tile
    }
    else if (fish) {
        shape.setFillColor(sf::Color::Yellow); // Indicate fish presence
    }
    else {
        shape.setFillColor(defaultColor);
    }
}

/*************************************************************
* Function: draw(sf::RenderWindow& window)                   *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Renders the tile to the specified window.     *
* Input parameters:                                          *
*   - sf::RenderWindow& window: Reference to the render      *
*     window where the tile will be drawn                   *
* Returns: None.                                             *
* Preconditions: Tile and window must be properly initialized.*
* Postconditions: Tile is drawn to the render window.        *
*************************************************************/
void Tile::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

/*************************************************************
* Function: hasFish() const                                  *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Checks if the tile contains a fish.           *
* Input parameters: None.                                    *
* Returns: bool: True if the tile contains a fish, false     *
*                otherwise.                                  *
* Preconditions: Tile object must be initialized.            *
* Postconditions: The fish presence state is returned.       *
*************************************************************/
bool Tile::hasFish() const {
    return fish;
}

/*************************************************************
* Function: setFish(bool hasFish)                            *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Sets the fish presence for the tile. If a fish*
*              is added, a new Fish object is created. If    *
*              removed, the memory is released.              *
* Input parameters:                                          *
*   - bool hasFish: True to add a fish, false to remove it   *
* Returns: None.                                             *
* Preconditions: Tile object must be initialized.            *
* Postconditions: Fish state is updated, and memory is       *
*                 managed accordingly.                       *
*************************************************************/
void Tile::setFish(bool hasFish) {
    fish = hasFish;
    if (hasFish) {
        if (!fishPtr) {
            fishPtr = new Fish(x, y); // Create a new Fish object with tile's position
        }
    }
    else {
        delete fishPtr;  // Free memory if the fish is removed
        fishPtr = nullptr;
    }
}

/*************************************************************
* Function: catchFish()                                      *
* Date Created: 12/6/2024                                    *
* Date Last Modified:                                        *
* Description: Removes the fish from the tile, resets its    *
*              state, and releases associated memory.        *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: Tile object must be initialized and may     *
*                contain a fish.                             *
* Postconditions: Fish is removed, and memory is released.   *
*************************************************************/
void Tile::catchFish() {
    if (fish) {
        fish = false;        // Remove the fish
        delete fishPtr;      // Free the memory
        fishPtr = nullptr;   // Reset pointer
    }
}
