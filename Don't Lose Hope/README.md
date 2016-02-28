/********************************************************
* UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
* COMPUTAÇÃO GRÁFICA (EEL882) - PROF. CLÁUDIO ESPERANÇA
********************************************************/

Game developed for the course EEL882 - Computação Gráfica (Graphic Computing) taken during the 2nd term of 2015.
This game is multi-platform.

SETUP LINUX:
	Enter on the folder and run a make*. Open the game through the launcher or via shell.

	*Requires G++ compiler.

SETUP WINDOWS:
	Must be compiled using G++ using this command lines, then, execute the launcher.

	g++ -std=c++11 -O3 -c game.cpp -o game.o -I./lib/sfmlxYY/include
	g++ -std=c++11 -O3 -c screen.cpp -o screen.o -I./lib/sfmlxYY/include
	g++ -std=c++11 -O3 -c player.cpp -o player.o -I./lib/sfmlxYY/include
	g++ -std=c++11 -O3 -c map_editor.cpp -o map_editor.o -I./lib/sfmlxYY/include
	g++ -std=c++11 -O3 -c main.cpp -o main.o -I./lib/sfmlxYY/include
	g++ -std=c++11 -o DLH.exe main.o screen.o game.o player.o map_editor.o -L$-I./lib/sfmlxYY/lib -lsfml-audio -lsfml-graphics -lsfml-window  -lsfml-system

	NOTE: sfmlxYY - one must change YY to his current platform supports, whether 86 or 64 bits.

authors:
	Leonardo Souza - 112086681
	Raphael Sathler 111344078 

