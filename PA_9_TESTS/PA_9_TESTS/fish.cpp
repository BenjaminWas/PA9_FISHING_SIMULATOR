#include "Fish.h"


/*************************************************************
* Function: Fish::Fish(float x, float y)                    *
* Date Created: 12/3/2024                                    *
* Date Last Modified:                                        *
* Description: Constructor for the Fish class. Initializes   *
*              the fish's shape, color, and position.        *
* Input parameters:                                          *
*   - float x: X-coordinate of the fish's position.          *
*   - float y: Y-coordinate of the fish's position.          *
* Returns: None.                                             *
* Preconditions: None.                                       *
* Postconditions: A Fish object is created with a yellow     *
*                 circular shape and positioned at (x, y).   *
*************************************************************/
Fish::Fish(float x, float y) {
    shape.setRadius(10.0f);                  // Set the radius of the fish
    shape.setFillColor(sf::Color::Yellow);  // Set the fish's color to yellow
    shape.setPosition(x, y);                // Set the fish's position
}

/*************************************************************
* Function: Fish::~Fish()                                    *
* Date Created: 12/3/2024                                    *
* Date Last Modified:                                        *
* Description: Destructor for the Fish class. Currently, it  *
*              does not perform any specific cleanup.        *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: A Fish object must exist.                   *
* Postconditions: The Fish object is properly destroyed.     *
*************************************************************/
Fish::~Fish() {}

/*************************************************************
* Function: draw(sf::RenderWindow& window)                   *
* Date Created: 12/3/2024                                    *
* Date Last Modified:                                        *
* Description: Draws the fish's shape onto the specified      *
*              render window.                                *
* Input parameters:                                          *
*   - sf::RenderWindow& window: The window where the fish    *
*     will be drawn.                                         *
* Returns: None.                                             *
* Preconditions: The Fish object and the window must be      *
*                initialized.                                *
* Postconditions: The fish's shape is rendered to the window.*
*************************************************************/
void Fish::draw(sf::RenderWindow& window) {
    window.draw(shape); // Render the fish's shape
}

/*************************************************************
* Function: getPosition() const                              *
* Date Created: 12/3/2024                                    *
* Date Last Modified:                                        *
* Description: Retrieves the current position of the fish.   *
* Input parameters: None.                                    *
* Returns: sf::Vector2f: The position of the fish as a       *
*                        2D vector.                         *
* Preconditions: The Fish object must be initialized.        *
* Postconditions: The fish's position is returned.           *
*************************************************************/
sf::Vector2f Fish::getPosition() const {
    return shape.getPosition(); // Return the position of the fish
}

/*************************************************************
* Function: update(float deltaTime)                          *
* Date Created: 12/3/2024                                    *
* Date Last Modified:                                        *
* Description: Updates the fish's state. Currently a         *
*              placeholder for future logic such as          *
*              animations or movement.                       *
* Input parameters:                                          *
*   - float deltaTime: The time elapsed since the last frame.*
* Returns: None.                                             *
* Preconditions: The Fish object must be initialized.        *
* Postconditions: The fish's state can be updated (future    *
*                 expansion).                                *
*************************************************************/
void Fish::update(float deltaTime) {
    // Placeholder: Add animations or movement logic here in the future
}
