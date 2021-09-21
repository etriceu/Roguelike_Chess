#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "MapGenerator.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Torch.hpp"
#include "Crystal.hpp"
#include "Obstacle.hpp"

class World : public MapGenerator
{
	const int MAX_CRYSTAL = 3;
	const int MAX_TORCH = 2;
	const int MAX_OBSTACLES = 3;
	const float ARTIFACT_CHANCE = 10.0;
public:
	World();
	~World();
	void update();
	void draw(sf::RenderTarget& target);
	void newMap();
	Player* getPlayer();

private:
	sf::Vector2i getValidPosition(const pair<sf::IntRect, list<Object*>> &it, bool collidable = false);
	void addObjects();
	void destroyObjects();

	sf::RenderTexture preWindow;
	sf::Clock clock;
};

#endif // WORLD_HPP_INCLUDED
