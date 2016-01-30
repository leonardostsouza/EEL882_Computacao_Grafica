#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <string.h>


class Map
{
public:
	// render map
	Map();
	~Map();

	void renderMap();
	void saveMap(string saveName);
	void loadMap(string saveName);

private:
	fstream saveFile;
};

#endif
