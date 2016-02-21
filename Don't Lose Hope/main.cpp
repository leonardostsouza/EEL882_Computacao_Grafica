#include "lib/screen.h"
#include "lib/game.h"
#include "lib/map_editor.h"
//include "lib/utilities.h"
#include <string.h>

using namespace std;

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
    Screen* menu = NULL; //new Screen(fs,App,vmode);
    Game* game = NULL;// = new Game(fs,App,vmode,menu->passLevels());
    MapEditor* map_editor = NULL;// new MapEditor(fs,App,vmode);

// check all the window's events that were triggered since the last iteration of the loop
while (App->isOpen())
{

    sf::Event event;
    switch (state){
        case MAINMENU:
        if (game != NULL){
            delete game;
            game = NULL;
        }

        if(map_editor != NULL){
            delete map_editor;
            map_editor = NULL;
        }

        if (menu == NULL){
            menu = new Screen(fs,App,vmode);
        }
        state = menu->eventHandler(state);
        break;

        case OPTIONSMENU:
        state = menu->eventHandler(state);
        break;

        case CHOOSING:
        state = menu->eventHandler(state);
        break;

        case CONTINUE:
        if (game == NULL){
            game = new Game(fs,App,vmode,menu->passLevels());
        }
        if (game->loadGame("resources/saves/savegame")){
            state = PLAYING;
        }
        else
        {
            state = MAINMENU;
            menu->showMessage("No Save Game Found");//,vmode.height-vmode.height/4);
        }
        break;

        case CREATING:
            if (map_editor == NULL){
                map_editor = new MapEditor(fs,App,vmode);
            }
            state = map_editor->eventHandler(event,menu->isFullscreen(), menu->isSoundEnabled());
            break;

        case PLAYING:
        if (game == NULL){
            game = new Game(fs,App,vmode,menu->passLevels());
        }
        state = game->eventHandler(menu->isFullscreen(), menu->isSoundEnabled(),menu->getChosenLevel());
        break;                

        case CLOSE:
        App->close();
        break;

        default:
        state = MAINMENU;
    }

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
                delete map_editor;
                menu = new Screen(fs,App,vmode);
                game = new Game(fs,App,vmode,menu->passLevels());
                map_editor = new MapEditor(fs,App,vmode);
            }
        }
    }
}

return EXIT_SUCCESS;
}
