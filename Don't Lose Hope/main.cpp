#include "lib/screen.h"
#include "lib/game.h"
//include "lib/utilities.h"
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    GAMESTATE state = MAINMENU, prevState = state;
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
   sf::RenderWindow* App;

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
App = new sf::RenderWindow(sf::VideoMode(vmode.width, vmode.height, vmode.bitsPerPixel), "Don't Lose Hope");
sf::View view(App->getDefaultView());
App->setFramerateLimit(60);
App->setVerticalSyncEnabled(true);
Screen* menu = new Screen(fs,App,vmode);
Game* game = new Game(fs,App,vmode,menu->passLevels());

    // check all the window's events that were triggered since the last iteration of the loop
    while (App->isOpen()) //.pollEvent(event))
{

    sf::Event event;
    switch (state){
        case MAINMENU:
        state = menu->eventHandler(state);
        break;

        case OPTIONSMENU:
        state = menu->eventHandler(state);
        break;

        case CHOOSING:
        state = menu->eventHandler(state);
        break;

        case CREATING:
        break;

        case PLAYING:
        state = game->eventHandler(menu->isFullscreen(), menu->isSoundEnabled(),menu->getChosenLevel());
        break;                

        case CLOSE:
        App->close();
        break;

        default:
        state = MAINMENU;
    }

    prevState = state;
    //close window event
    while(App->pollEvent(event)){
        if (event.type == sf::Event::Closed)
            App->close();

        if (event.type == sf::Event::Resized){
            if (vmode.width != event.size.width){
                vmode.width = event.size.width;
                vmode.height = event.size.height;
                App->setView(view = sf::View(sf::FloatRect(0,0,vmode.width, vmode.height)));
                fs = !fs;
                delete menu;
                delete game;
                menu = new Screen(fs,App,vmode);
                game = new Game(fs,App,vmode,menu->passLevels());
            }
        }
    }
}

return EXIT_SUCCESS;
}
