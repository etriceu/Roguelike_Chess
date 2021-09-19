#ifndef ACTOR_HPP_INCLUDED
#define ACTOR_HPP_INCLUDED

#include "MapGenerator.hpp"

class Actor : public Object
{
protected:
	static constexpr int WIDTH = 16;
	static constexpr int HEIGHT = 18;

	static constexpr float WALK_SPEED = 100; // px/s
	static constexpr int DEFAULT_FRAME = 7;
	static constexpr int WALK_TIME = 75;
	static constexpr int STAND[4] = {10, 4, 1, 7};
	static constexpr int WALK[4][4] = {
		{9, 10, 11, 10}, {3, 4, 5, 4}, {0, 1, 2, 1}, {6, 7, 8, 7}};

public:
	void update();

	enum Direction{NONE = -1, LEFT, RIGHT, UP, DOWN};

	Object* move(Direction dir);
	void setPosition(int x, int y);

	Direction moveDir = NONE;
	sf::IntRect room;

	static MapGenerator *map;

private:
	void setFrame(int frame);

	int standDir;
	int anim;
	sf::Clock walk, walkAnim;
};

#endif // ACTOR_HPP_INCLUDED
