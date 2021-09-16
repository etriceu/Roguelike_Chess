#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include "Actor.hpp"

class Enemy : public Actor
{
	const array<string, 2> TEX_PATH = {
		"Graphics/lowLevelEnemy.png",
		"Graphics/highLevelEnemy.png"};
	const int RAND_MOVE_CHANCE = 66;

public:
	Enemy(u_int lvl);
	void move();
};

#endif // ENEMY_HPP_INCLUDED
