#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string.h>
#include <stdio.h>

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

using namespace std;

int main(int argc, char *argv[])
{
    // useful variables and objects
    sf::VideoMode vmode;
    bool fullscreen = true;

    // check for execution flags
    for (int iterator = 1; iterator < argc; iterator++)
    {
        if (strcmp(argv[1],"-w") == 0)
        {
            fullscreen = false;
            #ifdef DEBUG
                printf("DEBUG === fullscreen set to %d\n", fullscreen);
            #endif
        }
    }

    //set VideoMode
    if (!fullscreen)
    {
        vmode.width = DEFAULT_WINDOW_WIDTH;
        vmode.height = DEFAULT_WINDOW_HEIGHT;
        vmode.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
    }
    else
    {
        vmode = sf::VideoMode::getFullscreenModes()[0];
    }

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(vmode.width, vmode.height, vmode.bitsPerPixel), "Don't Lose Hope");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen())
    {
        
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // close window event
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
        
    }

   return EXIT_SUCCESS;
}