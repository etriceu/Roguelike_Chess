#include "Enemy.hpp"

Enemy::Enemy(u_int lvl)
{
	if(lvl < LEN(TEX_PATH))
		lvl = 0;

	setTexture(*textures(string(TEX_PATH[lvl])));
	type = ENEMY;
	collidable = true;
}

void Enemy::move()
{
	bool isPlayer = false;
	for(auto obj : map->rooms[room])
		if(obj->type == PLAYER && room.contains(obj->x, obj->y))
		{
			int r = x != obj->x && y != obj->y ? rand()%2 : x != obj->x;
			if(r)
				Actor::move(obj->x < x ? LEFT : RIGHT);
			else
				Actor::move(obj->y < y ? UP : DOWN);

			isPlayer = true;
			break;
		}

	if(!isPlayer && rand()%100 < RAND_MOVE_CHANCE)
	{
		constexpr Direction dir[4] = {LEFT, RIGHT, UP, DOWN};
		int r = rand()%4;
		if(dir[r] == LEFT && room.contains(x-1, y)) Actor::move(dir[r]);
		else if(dir[r] == RIGHT && room.contains(x+1, y)) Actor::move(dir[r]);
		else if(dir[r] == UP && room.contains(x, y-1)) Actor::move(dir[r]);
		else if(dir[r] == DOWN && room.contains(x, y+1)) Actor::move(dir[r]);
	}
}
