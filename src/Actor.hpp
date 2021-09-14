#ifndef ACTOR_HPP_INCLUDED
#define ACTOR_HPP_INCLUDED

#include "MapGenerator.hpp"

class Actor : public Object
{
protected:
	const int WIDTH = 16;
	const int HEIGHT = 18;

	const float WALK_SPEED = 100; // px/s
	const char DEFAULT_FRAME = 7;
	const int WALK_TIME = 75;
	const vector <char> STAND = {10, 4, 1, 7};
	const vector <vector<char>> WALK = {
		{9, 10, 11, 10}, {3, 4, 5, 4}, {0, 1, 2, 1}, {6, 7, 8, 7}};

public:
	void update();
	Object* move(char dir);
	void setPosition(int x, int y);

	sf::IntRect room;
	enum Direction{NONE = -1, LEFT, RIGHT, UP, DOWN};

	static MapGenerator *map;

private:
	void setFrame(char frame);

	char dir = NONE;
	char standDir;
	char anim;
	sf::Clock walk, walkAnim;
};

#endif // ACTOR_HPP_INCLUDED
