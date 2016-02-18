#include "lib/screen.h"
#include "lib/game.h"
//#include "lib/utilities.h"
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
App->setFramerateLimit(60);
App->setVerticalSyncEnabled(true);
Screen menu(fs,App,vmode);
Game game(fs,App,vmode);

    // check all the window's events that were triggered since the last iteration of the loop
        while (App->isOpen()) //.pollEvent(event))
{

    sf::Event event;
    switch (state){
        case MAINMENU:
        state = menu.eventHandler(state);
        break;

        case OPTIONSMENU:
        state = menu.eventHandler(state);
        break;

        case PLAYING:
        state = game.eventHandler(menu.isFullscreen(), menu.isSoundEnabled());
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
            if (!fs){
                vmode = sf::VideoMode::getFullscreenModes()[0];
            }else{
                vmode.width = DEFAULT_WINDOW_WIDTH;
                vmode.height = DEFAULT_WINDOW_HEIGHT;
                vmode.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
            }

                //App->close();
                //App->create(vmode, "Don't Lose Hope");
        }
    }
                //App->SetView(view = sf::View(sf::FloatRect(0.f,0.f,static_cast<float>(App->.GetWidth()),static_cast<float>(App->.GetHeight))));
}

return EXIT_SUCCESS;
}
