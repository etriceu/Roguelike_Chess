#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "MapGenerator.hpp"

class World : public MapGenerator
{

public:
	World();
	void update();
	void draw(sf::RenderTarget& target);
	void movePlayer(char dir);

private:
	sf::RenderTexture preWindow;
	sf::Clock clock;

	bool playerLayer;
};

#endif // WORLD_HPP_INCLUDED
