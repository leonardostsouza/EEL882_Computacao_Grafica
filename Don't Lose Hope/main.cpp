#include "lib/screen.h"
#include "lib/utilities.h"
#include "lib/game.h"
#include <string.h>

//using namespace std;

int main(int argc, char *argv[])
{
    GAMESTATE state = MAINMENU;
	bool fs = false;
    // check for execution flags
    #ifdef DEBUG
    std::cout << "DEBUG === Entering flag parse loop" << std::endl;
    #endif
    for (int iterator = 1; iterator < argc; iterator++)
    {
        if (strcmp(argv[1],"-f") == 0)
        {
			fs = true;
            #ifdef DEBUG
            std::cout << "DEBUG === fullscreen set to " << fs << std::endl;
            #endif
		}
    }

    sf::VideoMode vmode;
    sf::RenderWindow* window;
    //set VideoMode

    if (!fs)
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
    window = new sf::RenderWindow(sf::VideoMode(vmode.width, vmode.height, vmode.bitsPerPixel), "Don't Lose Hope");

	Screen screen(fs,window,vmode);
    Game game(fs,window,vmode);

    while ((*window).isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while ((*window).pollEvent(event))
        {
            switch (state){
                case MAINMENU:
                    state = screen.eventHandler(state);
                    std::cout << "Main Menu" << std::endl;
                    break;

                case OPTIONSMENU:
                    state = screen.eventHandler(state);
                    std::cout << "Options" << std::endl;
                    break;

                case PLAYING:
                    state = game.eventHandler(state);
                    std::cout << "Playing" << std::endl;
                    break;                

                case CLOSE:
                    std::cout << "Close" << std::endl;
                    (*window).close();
                    break;

                default:
                    state = MAINMENU;
            }
            // close window event
            if (event.type == sf::Event::Closed)
                (*window).close();
        }
    }

   return EXIT_SUCCESS;
}
