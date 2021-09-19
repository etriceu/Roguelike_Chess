#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Object : public sf::Sprite
{
public:
	enum Type {TORCH, ENEMY, PLAYER, CRYSTAL, OBSTACLE, ARTIFACT};
	Type type;
	int x, y;
	bool collidable = false;
	inline static int TILE_SIZE;
};

#endif // OBJECT_HPP_INCLUDED
