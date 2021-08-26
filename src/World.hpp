#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "Resources.hpp"

class World : public sf::Drawable, public sf::Transformable
{
	enum Tiles{EMPTY, FLOOR, FLOORX=20, WALL};
	const string TEX_PATH = "Graphics/tiles.png";
	const int TILE_SIZE = 16;
	static const int WIDTH = 105;
	static const int HEIGHT = 64;
	const float RANDOM_FLOOR = 0.1;
	const float ROOM_CHANCE = 0.02;

public:
	World();
    void newMap();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void buildRooms(vector <sf::IntRect> rooms);
	bool setTunnelFloor(int x, int y, sf::IntRect r1, sf::IntRect r2);
	bool buildTunnels(vector <sf::IntRect> rooms);
	bool fixTiles();
	void updateMap();

    sf::Texture *tileset;
	sf::VertexArray vertices;

	static const int SIZE = WIDTH*HEIGHT;
	struct Tile
	{
		Tiles type = EMPTY;
		char index = 0;
	} tiles[WIDTH][HEIGHT];
};

#endif // WORLD_HPP_INCLUDED
