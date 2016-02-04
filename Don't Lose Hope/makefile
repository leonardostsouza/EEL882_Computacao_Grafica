#### Source Files ####
SOURCE_FILES=main.cpp Screen.cpp

#### Object Files ####
MAIN_OBJ=main.o
SCREEN_OBJ=Screen.o

#### Executable Files ####
EXEC_FILE=teste

#### Dependencies ####
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

default: $(SOURCE_FILES)
	g++ -c main.cpp -o $(MAIN_OBJ)
	g++ -c Screen.cpp -o $(SCREEN_OBJ)
	g++ -o $(EXEC_FILE) $(MAIN_OBJ) $(SCREEN_OBJ) $(SFML_FLAGS)

debug-mode: $(SOURCE_FILES)
	g++ -Wall -DDEBUG -O0 -c main.cpp -o $(MAIN_OBJ)
	g++ -Wall -DDEBUG -O0 -c Screen.cpp -o $(SCREEN_OBJ)
	g++ -o $(EXEC_FILE) -Wall $(MAIN_OBJ) $(SCREEN_OBJ) $(SFML_FLAGS)
