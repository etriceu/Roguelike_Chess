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
}

World::~World()
{
	destroyObjects();
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
			obj->update();
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

sf::Vector2i World::getValidPosition(const pair<sf::IntRect, list<Object*>> &it, bool collidable)
{
	sf::IntRect r = it.first;
	sf::Vector2i pos;
	bool valid;
	do
	{
		valid = true;

		if(collidable)
			pos = {rand()%r.width+r.left, rand()%(r.height-4)+r.top+2};
		else
			pos = {rand()%r.width+r.left, rand()%r.height+r.top};

		for(auto pp : it.second)
			if(pp->x == pos.x && pp->y == pos.y)
				valid = false;

	}while(!valid);

	return pos;
}

void World::addObjects()
{
	sf::IntRect r = rooms.begin()->first;
	Player *p = new Player();
	player = p;
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

	if(rand()/(RAND_MAX+1.0) <= ARTIFACT_CHANCE)
	{
		auto it = rooms.begin();
		advance(it, rand() % rooms.size());
		it->second.push_back(
			new Artifact(getValidPosition({it->first, it->second}, true),
				(Artifact::ArtType)(rand()%Artifact::ART_NUM)));
	}

	for(auto &it : rooms)
	{
		for(int n = rand()%MAX_OBSTACLES; n > 0; n--)
			it.second.push_back(new Obstacle(getValidPosition(it, true)));

		int torchNum = rand()%(MAX_TORCH+1);
		for(int n = rand()%MAX_CRYSTAL+1; n > 0 && !torchNum; n--)
			it.second.push_back(new Crystal(getValidPosition(it)));

		for(int n = torchNum; n > 0; n--)
			it.second.push_back(new Torch(getValidPosition(it)));
	}

	light.apply();
}

void World::destroyObjects()
{
	for(auto it : rooms)
		for(auto obj : it.second)
			delete obj;

	rooms.clear();
}

