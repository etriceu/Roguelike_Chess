#ifndef OBSTACLE_HPP_INCLUDED
#define OBSTACLE_HPP_INCLUDED

#include "MapGenerator.hpp"

class Obstacle : public Object
{
	static constexpr string_view TEX_PATH = "Graphics/obstacles.png";
	static const int FWIDTH = 16;
	static const int FHEIGHT = 18;
	static constexpr struct{float x, y;} OFFSET = {0, -2};

public:
	Obstacle(sf::Vector2i pos);

private:
	static sf::Texture *tx;
};

#endif // OBSTACLE_HPP_INCLUDED
