#### Source Files ####
SOURCE_FILES=main.cpp screen.cpp game.cpp

#### Object Files ####
MAIN_OBJ=main.o
SCREEN_OBJ=screen.o
GAME_OBJ=game.o

#### Executable Files ####
EXEC_FILE=DLH

#### Dependencies ####
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

default: $(SOURCE_FILES)
	g++ -std=c++11 -c game.cpp -o $(GAME_OBJ)
	g++ -std=c++11 -c screen.cpp -o $(SCREEN_OBJ)
	g++ -std=c++11 -c main.cpp -o $(MAIN_OBJ)
	g++ -std=c++11 -o $(EXEC_FILE) $(MAIN_OBJ) $(SCREEN_OBJ) $(GAME_OBJ) $(SFML_FLAGS)

debug-mode: $(SOURCE_FILES)
	g++ -std=c++11 -Wall -DDEBUG -O0 -c game.cpp -o $(GAME_OBJ)
	g++ -std=c++11 -Wall -DDEBUG -O0 -c screen.cpp -o $(SCREEN_OBJ)
	g++ -std=c++11 -Wall -DDEBUG -O0 -c main.cpp -o $(MAIN_OBJ)
	g++ -std=c++11 -o $(EXEC_FILE) -Wall $(MAIN_OBJ) $(SCREEN_OBJ) $(GAME_OBJ) $(SFML_FLAGS)

clean:
	rm -f *.o DLH