#include "menu.h"

/*************************************************************
* Function: Menu()                                           *
* Date Created: 12/5/2024                                    *
* Date Last Modified:                                        *
* Description: Constructor for the Menu class. It initializes*
*              the window, background texture, and sprite    *
*              objects, and sets their initial values.       *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: None.                                       *
* Postconditions: The Menu object is initialized with a      *
*                 window, background texture, and sprite.    *
*************************************************************/
Menu::Menu() {
    window = new sf::RenderWindow();
    backgroundTexture = new sf::Texture();
    background = new sf::Sprite();

    set_values();
}

/*************************************************************
* Function: ~Menu()                                          *
* Date Created: 12/5/2024                                    *
* Date Last Modified:                                        *
* Description: Destructor for the Menu class. It deallocates *
*              the memory used by dynamically created        *
*              objects to prevent memory leaks.              *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: Menu object must exist.                     *
* Postconditions: Dynamically allocated objects are deleted. *
*************************************************************/
Menu::~Menu() {
    delete window;
    delete backgroundTexture;
    delete background;
}

/*************************************************************
* Function: set_values()                                     *
* Date Created: 12/5/2024                                    *
* Date Last Modified:                                        *
* Description: Initializes the window and loads the          *
*              background texture and sprite.                *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: Objects (window, backgroundTexture,         *
*                background) must be allocated.              *
* Postconditions: Window is created, background texture      *
*                 is loaded, and sprite is set.              *
*************************************************************/
void Menu::set_values() {
    // Create the window
    window->create(sf::VideoMode(720, 720), "Fishing Simulator Menu", sf::Style::Titlebar | sf::Style::Close);

    // Load background image
    backgroundTexture->loadFromFile("Fishing-Image.png");
    background->setTexture(*backgroundTexture);
}

/*************************************************************
* Function: handle_events()                                  *
* Date Created: 12/5/2024                                    *
* Date Last Modified:                                        *
* Description: Processes events such as window close and key *
*              press. Closes the window if the close button  *
*              is clicked or starts the game on a key press. *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: The window must be initialized and open.    *
* Postconditions: The window is closed if needed, and game   *
*                 transitions are triggered on key press.    *
*************************************************************/
void Menu::handle_events() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        // Check if any key is pressed
        if (event.type == sf::Event::KeyPressed) {
            std::cout << "Game Started" << std::endl;
            // Transition to game
            window->close();
        }
    }
}

/*************************************************************
* Function: draw_menu()                                      *
* Date Created: 12/5/2024                                    *
* Date Last Modified:                                        *
* Description: Clears the window, draws the background, and  *
*              displays the updated window content.          *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: The window and background must be properly  *
*                initialized.                                *
* Postconditions: The window displays the menu background.   *
*************************************************************/
void Menu::draw_menu() {
    window->clear();
    window->draw(*background);
    window->display();
}

/*************************************************************
* Function: run()                                            *
* Date Created: 12/5/2024                                    *
* Date Last Modified:                                        *
* Description: Main loop of the menu. It handles events and  *
*              continuously updates the menu display until   *
*              the window is closed.                         *
* Input parameters: None.                                    *
* Returns: None.                                             *
* Preconditions: The window must be initialized and open.    *
* Postconditions: The menu is displayed and interactive      *
*                 until the window is closed.                *
*************************************************************/
void Menu::run() {
    while (window->isOpen()) {
        handle_events();
        draw_menu();
    }
}