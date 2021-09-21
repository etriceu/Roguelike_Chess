#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include "Actor.hpp"

class Enemy : public Actor
{
	static constexpr string_view TEX_PATH[2] = {
		"Graphics/lowLevelEnemy.png", "Graphics/highLevelEnemy.png"};
	static constexpr int RAND_MOVE_CHANCE = 66;

public:
	Enemy(u_int lvl);
	Object* move();
};

#endif // ENEMY_HPP_INCLUDED
