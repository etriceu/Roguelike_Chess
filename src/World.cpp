#include "World.hpp"

#include <algorithm>

World::World()
	: MapGenerator(&preWindow)
{
	int wmax = max(WIDTH, HEIGHT)*TILE_SIZE;
	preWindow.create(wmax, wmax);
	Torch::clock = &clock;
	Torch::light = &light;
	Torch::TILE_SIZE = TILE_SIZE;
	Actor::map = this;
	player = new Player();
}

World::~World()
{
	destroyObjects();
	delete getPlayer();
}

void World::draw(sf::RenderTarget& target)
{
	sf::RenderStates states;
	states.texture = tileset;
	preWindow.clear();

	preWindow.draw(vertices, states);

	for(auto c : crystals)
		preWindow.draw(c);

	for(auto it : rooms)
		for(auto obj : it.second)
			preWindow.draw(*obj);

	preWindow.display();
	target.draw(light);
}

void World::update()
{
	for(auto it : rooms)
		for(auto obj : it.second)
			switch(obj->type)
			{
				case Object::TORCH:
					static_cast<Torch*>(obj)->update();
					break;
				case Object::ENEMY:
					static_cast<Enemy*>(obj)->update();
					break;
				case Object::PLAYER:
					static_cast<Player*>(obj)->update();
			}
}

Player* World::getPlayer()
{
	return static_cast<Player*>(player);
}

void World::newMap()
{
	destroyObjects();
	MapGenerator::newMap();
	addObjects();
}

void World::addObjects()
{
	for(auto it : rooms)
	{
		sf::IntRect r = it.first;
		vector <sf::Vector2i> objects;
		bool type = true;
		int num = rand()%(MAX_TORCH+1);
		if(num == 0)
		{
			type = false;
			num = rand()%MAX_CRYSTAL+1;
		}
		for(int n = 0; n < num; n++)
		{
			sf::Vector2i pos = {rand()%(r.width-2)+r.left+1, rand()%(r.height-2)+r.top+1};
			bool valid = true;
			for(auto pp : objects)
				if(pp == pos)
				{
					n--;
					valid = false;
				}

			if(valid)
			{
				objects.push_back(pos);
				if(type)
					rooms[r].push_back(new Torch({pos.x, pos.y}));
				else
					crystals.push_back(Crystal({(float)pos.x*TILE_SIZE, (float)pos.y*TILE_SIZE}));
			}
		}
	}
	light.apply();

	sf::IntRect r = rooms.begin()->first;
	Player *p = getPlayer();
	p->setPosition(r.left+r.width/2, r.top+r.height/2);
	p->room = r;
	rooms[r].push_back(p);

	for(auto &it : rooms)
		if(it.first != r)
		{
			Enemy *e = new Enemy(0);
			it.second.push_back(e);
			sf::IntRect r = it.first;
			e->setPosition(r.left+r.width/2, r.top+r.height/2);
			e->room = r;
		}
}

void World::destroyObjects()
{
	for(auto it : rooms)
		for(auto obj : it.second)
			switch(obj->type)
			{
				case Object::TORCH:
					delete static_cast<Torch*>(obj);
					break;
				case Object::ENEMY:
					delete static_cast<Enemy*>(obj);
					break;
				case Object::PLAYER:
				default:
					break;
			}
	rooms.clear();
}

