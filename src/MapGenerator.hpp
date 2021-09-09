#ifndef MAP_GENERATOR_HPP_INCLUDED
#define MAP_GENERATOR_HPP_INCLUDED

#include "Torch.hpp"
#include "Player.hpp"

class MapGenerator
{
protected:
	enum Tiles{EMPTY, FLOOR, FLOORX=20, WALL};
	static const int WIDTH = 105;
	static const int HEIGHT = 64;
	const string TEX_PATH = "Graphics/tiles.png";
	const int TILE_SIZE = 16;
	const float RANDOM_FLOOR = 0.1;
	const float ROOM_CHANCE = 0.02;

	const int MAX_TORCH = 2;

public:
	MapGenerator(sf::RenderTexture *preWindow);
    void newMap();

	Player player;

protected:
	void buildRooms(vector <sf::IntRect> rooms);
	bool setTunnelFloor(int x, int y, sf::IntRect r1, sf::IntRect r2);
	bool buildTunnels(vector <sf::IntRect> rooms);
	void addObjects(vector <sf::IntRect> rooms);
	bool fixTiles();
	void updateMap();

    sf::Texture *tileset;
	sf::VertexArray vertices;

	vector <Torch> torches;
	Light light;

	static const int SIZE = WIDTH*HEIGHT;
	struct Tile
	{
		Tiles type = EMPTY;
		char index = 0;
	} tiles[WIDTH][HEIGHT];
};

#endif // MAP_GENERATOR_HPP_INCLUDED
