#ifndef MAP_GENERATOR_HPP_INCLUDED
#define MAP_GENERATOR_HPP_INCLUDED

#include "Crystal.hpp"
#include "Object.hpp"

class MapGenerator
{
	struct compRooms
	{
		bool operator()(const sf::IntRect& l, const sf::IntRect& r) const
		{
			return (l.top | (int64_t)l.left<<32) < (r.top | (int64_t)r.left<<32);
		}
	};

protected:
	enum Tiles{EMPTY, FLOOR, FLOORX=20, WALL};
	static const int WIDTH = 105;
	static const int HEIGHT = 64;
	const string TEX_PATH = "Graphics/tiles.png";
	const int TILE_SIZE = 16;
	const float RANDOM_FLOOR = 0.1;
	const float ROOM_CHANCE = 0.02;

	const int MAX_TORCH = 2;
	const int MAX_CRYSTAL = 3;

public:
	MapGenerator(sf::RenderTexture *preWindow);

	Object *player;
	map <sf::IntRect, vector<Object*>, compRooms> rooms;

protected:
	void newMap();
	void buildRooms();
	bool setTunnelFloor(int x, int y, sf::IntRect r1, sf::IntRect r2);
	bool buildTunnels(vector<sf::IntRect> rooms);
	bool fixTiles();
	void updateMap();

    sf::Texture *tileset;
	sf::VertexArray vertices;

	vector <Crystal> crystals;
	Light light;

	static const int SIZE = WIDTH*HEIGHT;
	struct Tile
	{
		Tiles type = EMPTY;
		char index = 0;
	} tiles[WIDTH][HEIGHT];

	friend class Actor;
};

#endif // MAP_GENERATOR_HPP_INCLUDED
