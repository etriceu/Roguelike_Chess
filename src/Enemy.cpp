#include "Enemy.hpp"

Enemy::Enemy(u_int lvl)
{
	if(lvl < TEX_PATH.size())
		lvl = 0;

	setTexture(*textures(TEX_PATH[lvl]));
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

	if(!isPlayer)
	{
		int dir = rand()%4;
		if(dir == LEFT && room.contains(x-1, y)) Actor::move(dir);
		else if(dir == RIGHT && room.contains(x+1, y)) Actor::move(dir);
		else if(dir == UP && room.contains(x, y-1)) Actor::move(dir);
		else if(dir == DOWN && room.contains(x, y+1)) Actor::move(dir);
	}
}
