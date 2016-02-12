#include "lib/screen.h"
#include "lib/game.h"
//#include "lib/utilities.h"
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    GAMESTATE state = PLAYING, prevState = state;
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
    (*window).setFramerateLimit(60);
    (*window).setVerticalSyncEnabled(true);
	Screen menu(fs,window,vmode);
    Game game(fs,window,vmode);

    while ((*window).isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while ((*window).isOpen()) //.pollEvent(event))
        {

            switch (state){
                case MAINMENU:
                    state = menu.eventHandler(state, event);
                    break;

                case OPTIONSMENU:
                    state = menu.eventHandler(state, event);
                    break;

                case PLAYING:
                    state = game.eventHandler(event, menu.isFullscreen(), menu.isSoundEnabled());
                    break;                

                case CLOSE:
                    (*window).close();
                    break;

                default:
                    state = MAINMENU;
            }

            prevState = state;
            // close window event
            //if (event.type == sf::Event::Closed)
            //    (*window).close();
        }
    }

   return EXIT_SUCCESS;
}
