#include "Actor.hpp"

MapGenerator* Actor::map;
void Actor::update()
{
	if(moveDir != NONE && (x*map->TILE_SIZE != getPosition().x) !=
		(y*map->TILE_SIZE-map->TILE_SIZE/3 != getPosition().y))
	{
		if(walk.getElapsedTime().asSeconds() >= 1/WALK_SPEED)
		{
			switch(moveDir)
			{
				case LEFT: Object::move(-1, 0); break;
				case RIGHT: Object::move(1, 0); break;
				case UP: Object::move(0, -1); break;
				case DOWN: Object::move(0, 1);
				default:
					break;
			}
			walk.restart();
		}
	}
	else
		moveDir = NONE;

	if(walkAnim.getElapsedTime().asMilliseconds() >= WALK_TIME)
	{
		if(moveDir != NONE)
		{
			setFrame(WALK[moveDir][anim]);
			anim = (anim+1)%LEN(WALK[moveDir]);
		}
		else
		{
			setFrame(STAND[standDir]);
			anim = 0;
		}
		walkAnim.restart();
	}
}

Object* Actor::move(Direction moveDir)
{
	if(this->moveDir != NONE)
		return nullptr;

	int oldx = x, oldy = y;

	if(moveDir == LEFT && map->tiles[x-1][y].type == map->FLOOR)		x--;
	else if(moveDir == RIGHT && map->tiles[x+1][y].type == map->FLOOR)	x++;
	else if(moveDir == UP && map->tiles[x][y-1].type == map->FLOOR)		y--;
	else if(moveDir == DOWN && map->tiles[x][y+1].type == map->FLOOR)	y++;

	if(x != oldx || y != oldy)
	{
		auto it = map->rooms.find(room);
		for(auto obj : it->second)
			if(obj != this && x == obj->x && y == obj->y && obj->collidable)
			{
				x = oldx;
				y = oldy;
				return obj;
			}

		if(!room.contains(x, y))
			for(auto &r : map->rooms)
				if(r.first.contains(x, y))
				{
					it->second.remove(this);
					room = r.first;
					r.second.push_back(this);
					break;
				}

		standDir = moveDir;
		this->moveDir = moveDir;

		it->second.sort(
			[](const Object *l, const Object *r)
			{
				return l->y < r->y || (l->y == r->y &&
					(l->type != TORCH && r->type != CRYSTAL));
			});

		return this;
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

void Actor::setFrame(int frame)
{
	int x = getTexture()->getSize().x/WIDTH;
	setTextureRect({frame%x*WIDTH, frame/x*HEIGHT, WIDTH, HEIGHT});
}
