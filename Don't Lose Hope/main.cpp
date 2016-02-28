/********************************************************
* UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
* COMPUTAÇÃO GRÁFICA (EEL882) - PROF. CLÁUDIO ESPERANÇA
*
* TRABALHO 3
*
* ALUNOS:
* LEONARDO SOUZA - 112086681
* RAPHAEL SATHLER - 111344078
********************************************************/

#include "lib/screen.h"
#include "lib/game.h"
#include "lib/map_editor.h"
#include "lib/utilities.h"
#include <string.h>

int main(int argc, char *argv[])
{
    GAMESTATE state = MAINMENU;

    //set Video Mode
    sf::VideoMode vmode;
    sf::RenderWindow* App;
    int style = 0;

    vmode.width = DEFAULT_WINDOW_WIDTH;
    vmode.height = DEFAULT_WINDOW_HEIGHT;
    vmode.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;

    // Create main window
    App = new sf::RenderWindow(sf::VideoMode(vmode.width, vmode.height, vmode.bitsPerPixel), "Don't Lose Hope", sf::Style::Close|sf::Style::Titlebar);
	App->setIcon(dlh_icon.width, dlh_icon.height, dlh_icon.pixel_data);
    App->setFramerateLimit(60);
    App->setVerticalSyncEnabled(true);
    sf::View view(App->getDefaultView());

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
            menu = new Screen(App,vmode);
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
            game = new Game(App,vmode,menu->passLevels());
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
                map_editor = new MapEditor(App,vmode);
            }
            state = map_editor->eventHandler(event, menu->isSoundEnabled());
            break;

        // game screen
        case PLAYING:
        if (game == NULL){
            game = new Game(App,vmode,menu->passLevels());
        }
        state = game->eventHandler(menu->isSoundEnabled(), menu->getChosenLevel());
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
