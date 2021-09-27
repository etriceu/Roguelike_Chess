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
			pos = {rand()%(r.width-2)+r.left+1, rand()%(r.height-4)+r.top+2};
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
	sf::IntRect pr = (--rooms.end())->first;
	Player *p = new Player();
	player = p;
	p->setPosition(pr.left+pr.width/2, pr.top+pr.height/2);
	p->room = pr;
	rooms[pr].push_back(p);

	sf::IntRect br = rooms.begin()->first;
	for(auto &it : rooms)
		if(it.first != pr && it.first.width == 8)
		{
			br = it.first;
			break;
		}

	Enemy *boss = new Enemy(Enemy::MAX_LVL);
	boss->setPosition(br.left+br.width/2, br.top+br.height/2);
	boss->room = br;
	rooms[br].push_back(boss);

	constexpr double MAX_DIST = WIDTH*WIDTH+HEIGHT*HEIGHT;
	for(auto &it : rooms)
		if(it.first != pr && it.first != br)
		{
			sf::IntRect r = it.first;
			int x = r.left+r.width/2;
			int y = r.top+r.height/2;
			double xx = p->x-x, yy = p->y-y;
			int lvl = min(round((xx*xx+yy*yy)/MAX_DIST*(Enemy::MAX_LVL+1)), Enemy::MAX_LVL-1.0);
			Enemy *e = new Enemy(lvl);
			it.second.push_back(e);
			e->setPosition(x, y);
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

