#include "World.hpp"

#include <algorithm>

World::World()
	: MapGenerator(&preWindow)
{
	int wmax = max(WIDTH, HEIGHT)*TILE_SIZE;
	preWindow.create(wmax, wmax);
	Torch::clock = &clock;
	Torch::light = &light;
	Actor::map = this;
	Crystal::light = &light;
	Player::light = &light;
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
				default:
					break;
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

sf::Vector2i World::getValidPosition(const pair<sf::IntRect, list<Object*>> &it)
{
	sf::IntRect r = it.first;
	sf::Vector2i pos;
	bool valid;
	do
	{
		valid = true;
		pos = {rand()%(r.width-2)+r.left+1, rand()%(r.height-2)+r.top+1};
		for(auto pp : it.second)
			if(pp->x == pos.x && pp->y == pos.y)
				valid = false;

	}while(!valid);

	return pos;
}

void World::addObjects()
{
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

	for(auto &it : rooms)
	{
		int torchNum = rand()%(MAX_TORCH+1);
		for(int n = torchNum; n > 0; n--)
			it.second.push_back(new Torch(getValidPosition(it)));

		for(int n = rand()%MAX_CRYSTAL+1; n > 0 && !torchNum; n--)
			it.second.push_back(new Crystal(getValidPosition(it)));

		for(int n = rand()%MAX_OBSTACLES; n > 0; n--)
			it.second.push_back(new Obstacle(getValidPosition(it)));
	}

	if(rand()/(RAND_MAX+1.0) <= ARTIFACT_CHANCE)
	{
		auto it = rooms.begin();
		advance(it, rand() % rooms.size());
		it->second.push_back(
			new Artifact(getValidPosition({it->first, it->second}),
				static_cast<Artifact::ArtType>(rand()%Artifact::ART_NUM)));
	}

	light.apply();
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
				case Object::OBSTACLE:
					delete static_cast<Obstacle*>(obj);
					break;
				case Object::ARTIFACT:
					delete static_cast<Artifact*>(obj);
					break;
				case Object::PLAYER:
				default:
					break;
			}
	rooms.clear();
}

