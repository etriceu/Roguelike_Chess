#include "Obstacle.hpp"

sf::Texture *Obstacle::tx = textures(string(Obstacle::TEX_PATH));

Obstacle::Obstacle(sf::Vector2i pos)
{
	x = pos.x;
	y = pos.y;
	pos.x *= TILE_SIZE;
	pos.y *= TILE_SIZE;
	int frame = rand()/(RAND_MAX+1.0)*(tx->getSize().x/FWIDTH);

	setTexture(*tx);
	setPosition(pos.x+OFFSET.x, pos.y+OFFSET.y);

	setTextureRect({frame*FWIDTH, 0, FWIDTH, FHEIGHT});

	type = OBSTACLE;
	collidable = true;
}
