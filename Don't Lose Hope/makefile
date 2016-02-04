default: main.cpp Screen.cpp
	g++ -c main.cpp -lsfml-graphics -lsfml-window -lsfml-system
	g++ -c Screen.cpp -lsfml-graphics -lsfml-window -lsfml-system
	g++ -o teste main.o Screen.o -lsfml-graphics -lsfml-window -lsfml-system

debug-mode: main.cpp Screen.cpp
	g++ -Wall -DDEBUG -O0 -c main.cpp
	g++ -Wall -DDEBUG -O0 -c Screen.cpp
	g++ -o teste -Wall main.o Screen.o -lsfml-graphics -lsfml-window -lsfml-system
