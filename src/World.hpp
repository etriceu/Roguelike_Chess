#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "MapGenerator.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Torch.hpp"

class World : public MapGenerator
{

public:
	World();
	~World();
	void update();
	void draw(sf::RenderTarget& target);
	void newMap();
	Player* getPlayer();

private:
	void addObjects();
	void destroyObjects();

	sf::RenderTexture preWindow;
	sf::Clock clock;
};

#endif // WORLD_HPP_INCLUDED
