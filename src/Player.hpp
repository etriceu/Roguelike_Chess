#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "Resources.hpp"

class Player : public sf::Sprite
{
	const string TEX_PATH = "Graphics/king.png";
	const int WIDTH = 16;
	const int HEIGHT = 18;

	const float WALK_SPEED = 100; // px/s
	const char DEFAULT_FRAME = 7;
	const int WALK_TIME = 75;
	const vector <char> STAND = {10, 4, 1, 7};
	const vector <vector<char>> WALK = {
		{9, 10, 11, 10}, {3, 4, 5, 4}, {0, 1, 2, 1}, {6, 7, 8, 7}};

public:
	Player(int tileSize);
	void update();
	void move(char dir);
	void setPosition(int x, int y);

	int x, y;
	enum Direction{NONE = -1, LEFT, RIGHT, UP, DOWN};

private:
	void setFrame(char frame);

	char dir = NONE;
	char standDir;
	char anim;
	const int TILE_SIZE;
	sf::Clock walk, walkAnim;
};

#endif // PLAYER_HPP_INCLUDED
