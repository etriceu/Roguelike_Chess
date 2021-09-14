#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Object : public sf::Sprite
{
public:
	enum Type {TORCH, ENEMY, PLAYER};
	Type type;
	int x, y;
};

#endif // OBJECT_HPP_INCLUDED
