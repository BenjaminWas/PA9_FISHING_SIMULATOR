/**/
#include "Lake.hpp"
int main(void)
{
    sf::RenderWindow app(sf::VideoMode(MAX_SIZE * TILE_SIZE, MAX_SIZE * TILE_SIZE, 8), "Fishing Simulator", sf::Style::Close);
    /* For Debugging opens window
	while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear the screen (fill it with black color)
        app.clear();

        // Display window contents on screen
        app.display();
    }
    */Lake lake(&window);

while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    window.clear();
    lake.draw(); // Draw the lake
    window.display();
}

return 0;
}
