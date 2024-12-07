#include "Character.h"

/*************************************************************
* Function: Character::Character(float x, float y)          *
* Date Created: 12/3/2024                                    *
* Date Last Modified:                                        *
* Description: Constructor for the Character class. Sets up  *
*              the character's size, color, initial position,*
*              and movement speed.                           *
* Input parameters:                                          *
*   - float x: X-coordinate of the character's initial       *
*     position.                                              *
*   - float y: Y-coordinate of the character's initial       *
*     position.                                              *
* Returns: None.                                             *
* Preconditions: None.                                       *
* Postconditions: A Character object is initialized with a   *
*                 red square shape and positioned at (x, y). *
*************************************************************/
Character::Character(float x, float y) : speed(50.0f) {
    shape.setSize(sf::Vector2f(25.0f, 25.0f)); // Set the size of the character
    shape.setFillColor(sf::Color::Red);       // Set the color of the character to red
    shape.setPosition(x, y);                  // Set the initial position of the character
}

/*************************************************************
* Function: move(sf::Vector2f direction)                    *
* Date Created: 12/3/2024                                    *
* Date Last Modified:                                        *
* Description: Moves the character by the specified direction*
*              vector.                                       *
* Input parameters:                                          *
*   - sf::Vector2f direction: The vector representing the    *
*     direction and distance of the movement.                *
* Returns: None.                                             *
* Preconditions: The Character object must be initialized.   *
* Postconditions: The character's position is updated based  *
*                 on the direction vector.                   *
*************************************************************/
void Character::move(sf::Vector2f direction) {
    shape.move(direction); // Move the character by the direction vector
}

/*************************************************************
* Function: draw(sf::RenderWindow& window)                   *
* Date Created: 12/3/2024                                    *
* Date Last Modified:                                        *
* Description: Draws the character onto the specified render *
*              window.                                       *
* Input parameters:                                          *
*   - sf::RenderWindow& window: The window where the         *
*     character will be drawn.                               *
* Returns: None.                                             *
* Preconditions: The Character object and the window must be *
*                initialized.                                *
* Postconditions: The character's shape is rendered to the   *
*                 window.                                    *
*************************************************************/
void Character::draw(sf::RenderWindow& window) {
    window.draw(shape); // Render the character's shape to the window
}

/*************************************************************
* Function: getPosition() const                              *
* Date Created: 12/3/2024                                    *
* Date Last Modified:                                        *
* Description: Retrieves the current position of the         *
*              character.                                    *
* Input parameters: None.                                    *
* Returns: sf::Vector2f: The current position of the         *
*                        character as a 2D vector.           *
* Preconditions: The Character object must be initialized.   *
* Postconditions: The character's current position is        *
*                 returned.                                  *
*************************************************************/
sf::Vector2f Character::getPosition() const {
    return shape.getPosition(); // Return the position of the character
}

/*************************************************************
* Function: setPosition(float x, float y)                    *
* Date Created: 12/3/2024                                    *
* Date Last Modified:                                        *
* Description: Sets the character's position to the specified*
*              coordinates.                                  *
* Input parameters:                                          *
*   - float x: The X-coordinate to set the character's       *
*     position.                                              *
*   - float y: The Y-coordinate to set the character's       *
*     position.                                              *
* Returns: None.                                             *
* Preconditions: The Character object must be initialized.   *
* Postconditions: The character's position is updated to the *
*                 specified coordinates.                     *
*************************************************************/
void Character::setPosition(float x, float y) {
    shape.setPosition(x, y); // Set the character's position to (x, y)
}

/*************************************************************
* Function: update(float deltaTime)                          *
* Date Created: 12/3/2024                                    *
* Date Last Modified:                                        *
* Description: Updates the character's state. Currently a    *
*              placeholder for future functionality such as  *
*              animations or movement logic.                 *
* Input parameters:                                          *
*   - float deltaTime: The time elapsed since the last frame.*
* Returns: None.                                             *
* Preconditions: The Character object must be initialized.   *
* Postconditions: The character's state can be updated       *
*                 (future expansion).                        *
*************************************************************/
void Character::update(float deltaTime) {
    // Placeholder: Add logic for updates (e.g., animations) in the future
}
