#ifndef MAP_H
#define MAP_H

//#include <fstream.h>
#include <string.h>


class Map
{
public:
	// render map
	Map();
	~Map();

	void renderMap();
	void saveMap(std::string saveName);
	void loadMap(std::string saveName);

private:
	//fstream saveFile;
};

#endif
