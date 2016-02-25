#include "lib/screen.h"
#include "lib/game.h"
#include "lib/map_editor.h"
#include "lib/utilities.h"
#include <string.h>

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

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
            //fs = true;
        #ifdef DEBUG
            std::cout << "DEBUG === fullscreen set to " << fs << std::endl;
        #endif
        }
    }

    //set Video Mode
    sf::VideoMode vmode;
    sf::RenderWindow* App;
    int style = 0;

    if (!fs)
    {
        vmode.width = DEFAULT_WINDOW_WIDTH;
        vmode.height = DEFAULT_WINDOW_HEIGHT;
        vmode.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
        style = sf::Style::Close|sf::Style::Titlebar;
    }
    else
    {
        vmode = sf::VideoMode::getFullscreenModes()[0];
        style = sf::Style::Close|sf::Style::Titlebar|sf::Style::Fullscreen;
    }

    // Create main window
    App = new sf::RenderWindow(sf::VideoMode(vmode.width, vmode.height, vmode.bitsPerPixel), "Don't Lose Hope", style);
	App->setIcon(dlh_icon.width, dlh_icon.height, dlh_icon.pixel_data);
    sf::View view(App->getDefaultView());
    App->setFramerateLimit(60);
    App->setVerticalSyncEnabled(true);

    Screen* menu = NULL;            // Main Menu Screen object
    Game* game = NULL;              // Game Screen object
    MapEditor* map_editor = NULL;   // Map Editor Screen object

// check all the window's events that were triggered since the last iteration of the loop
while (App->isOpen())
{

    sf::Event event;
    switch (state){
        // Main menu screen
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

        // Options menu screen
        case OPTIONSMENU:
        state = menu->eventHandler(state);
        break;

        // Phase selection screen
        case CHOOSING:
        state = menu->eventHandler(state);
        break;

        // load game
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
            menu->showMessage("No Save Game Found");
        }
        break;

        // map editor screen
        case CREATING:
            if (map_editor == NULL){
                map_editor = new MapEditor(fs,App,vmode);
            }
            state = map_editor->eventHandler(event,menu->isFullscreen(), menu->isSoundEnabled());
            break;

        // game screen
        case PLAYING:
        if (game == NULL){
            game = new Game(fs,App,vmode,menu->passLevels());
        }
        state = game->eventHandler(menu->isFullscreen(), menu->isSoundEnabled(),menu->getChosenLevel());
        break;                

        // exit game
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
    }
}

return EXIT_SUCCESS;
}
