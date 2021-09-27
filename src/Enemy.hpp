#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include "Actor.hpp"

class Enemy : public Actor
{
	static constexpr string_view TEX_PATH[] = {
		"Graphics/lowLevelEnemy.png", "Graphics/highLevelEnemy.png",
		"Graphics/enemyKing.png"};
	static constexpr int RAND_MOVE_CHANCE = 66;

public:
	static constexpr int MAX_LVL = LEN(TEX_PATH)-1;
	Enemy(u_int lvl);
	Object* move();
};

#endif // ENEMY_HPP_INCLUDED
