#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "Actor.hpp"

class Player : public Actor
{
	const string TEX_PATH = "Graphics/king.png";
public:
	Player();
	void control();
};

#endif // PLAYER_HPP_INCLUDED
