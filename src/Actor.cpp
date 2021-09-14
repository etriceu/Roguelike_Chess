#include "Actor.hpp"

MapGenerator* Actor::map;
void Actor::update()
{
	if(dir != NONE && (x*map->TILE_SIZE != getPosition().x) !=
		(y*map->TILE_SIZE-map->TILE_SIZE/3 != getPosition().y))
	{
		if(walk.getElapsedTime().asSeconds() >= 1/WALK_SPEED)
		{
			switch(dir)
			{
				case LEFT: Object::move(-1, 0); break;
				case RIGHT: Object::move(1, 0); break;
				case UP: Object::move(0, -1); break;
				case DOWN: Object::move(0, 1);
			}
			walk.restart();
		}
	}
	else
		dir = NONE;

	if(walkAnim.getElapsedTime().asMilliseconds() >= WALK_TIME)
	{
		if(dir != NONE)
		{
			setFrame(WALK[dir][anim]);
			anim = (anim+1)%WALK[dir].size();
		}
		else
		{
			setFrame(STAND[standDir]);
			anim = 0;
		}
		walkAnim.restart();
	}
}

Object* Actor::move(char dir)
{
	if(this->dir != NONE)
		return nullptr;

	int oldx = x, oldy = y;

	if(dir == LEFT && map->tiles[x-1][y].type == map->FLOOR)		x--;
	else if(dir == RIGHT && map->tiles[x+1][y].type == map->FLOOR)	x++;
	else if(dir == UP && map->tiles[x][y-1].type == map->FLOOR)		y--;
	else if(dir == DOWN && map->tiles[x][y+1].type == map->FLOOR)	y++;

	if(x != oldx || y != oldy)
	{
		auto it = map->rooms.find(room);
		for(auto obj : it->second)
			if(obj != this && x == obj->x && y == obj->y && obj->type != TORCH)
			{
				x = oldx;
				y = oldy;
				return obj;
			}

		if(!room.contains(x, y))
			for(auto &r : map->rooms)
				if(r.first.contains(x, y))
				{
					for(size_t n = 0; n < it->second.size(); n++)
						if(it->second[n] == this)
						{
							it->second.erase(it->second.begin()+n);
							break;
						}

					room = r.first;
					r.second.push_back(this);
					break;
				}

		standDir = dir;
		this->dir = dir;

		sort(it->second.begin(), it->second.end(),
			[](const Object *l, const Object *r)
			{
				return l->y < r->y || (l->y == r->y && l->type != TORCH);
			});
	}
	return nullptr;
}

void Actor::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	sf::Sprite::setPosition(x*map->TILE_SIZE, y*map->TILE_SIZE-map->TILE_SIZE/3);
	setFrame(DEFAULT_FRAME);
	standDir = DOWN;
}

void Actor::setFrame(char frame)
{
	int x = getTexture()->getSize().x/WIDTH;
	setTextureRect({frame%x*WIDTH, frame/x*HEIGHT, WIDTH, HEIGHT});
}
