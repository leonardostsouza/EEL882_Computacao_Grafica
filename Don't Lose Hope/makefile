#### Source Files ####
SOURCE_FILES=main.cpp screen.cpp game.cpp player.cpp map_editor.cpp

#### Object Files ####
MAIN_OBJ=main.o
SCREEN_OBJ=screen.o
GAME_OBJ=game.o
PLAYER_OBJ=player.o
MAP_EDITOR_OBJ=map_editor.o

#### Executable Files ####
EXEC_FILE=DLH

#### Dependencies ####
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

#### SFML Location ####
SFML_PATH=lib/sfml

default: $(SOURCE_FILES)
	g++ -std=c++11 -O3 -c game.cpp -o $(GAME_OBJ) #-I$(SFML_PATH)/include
	g++ -std=c++11 -O3 -c screen.cpp -o $(SCREEN_OBJ) #-I$(SFML_PATH)/include
	g++ -std=c++11 -O3 -c player.cpp -o $(PLAYER_OBJ) #-I$(SFML_PATH)/include
	g++ -std=c++11 -O3 -c map_editor.cpp -o $(MAP_EDITOR_OBJ) #-I$(SFML_PATH)/include
	g++ -std=c++11 -O3 -c main.cpp -o $(MAIN_OBJ) #-I$(SFML_PATH)/include
	g++ -std=c++11 -o $(EXEC_FILE) $(MAIN_OBJ) $(SCREEN_OBJ) $(GAME_OBJ) $(PLAYER_OBJ) $(MAP_EDITOR_OBJ) $(SFML_FLAGS) #-L$(SFML_PATH)/lib $(SFML_FLAGS)
	#export LD_LIBRARY_PATH=$(SFML_PATH)/lib && ./DLH
	./DLH

debug-mode: $(SOURCE_FILES)
	g++ -std=c++11 -Wall -DDEBUG -O0 -c game.cpp -o $(GAME_OBJ) -I$(SFML_PATH)/include
	g++ -std=c++11 -Wall -DDEBUG -O0 -c screen.cpp -o $(SCREEN_OBJ) -I$(SFML_PATH)/include
	g++ -std=c++11 -Wall -DDEBUG -O0 -c player.cpp -o $(PLAYER_OBJ) -I$(SFML_PATH)/include
	g++ -std=c++11 -Wall -DDEBUG -O0 -c map_editor.cpp -o $(MAP_EDITOR_OBJ) -I$(SFML_PATH)/include
	g++ -std=c++11 -Wall -DDEBUG -O0 -c main.cpp -o $(MAIN_OBJ) -I$(SFML_PATH)/include
	g++ -std=c++11 -o $(EXEC_FILE) $(MAIN_OBJ) $(SCREEN_OBJ) $(GAME_OBJ) $(PLAYER_OBJ) $(MAP_EDITOR_OBJ) -L$(SFML_PATH)/lib $(SFML_FLAGS)

clean:
	rm -f *.o DLH
