#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "Actor.hpp"
#include "Settings.hpp"

class Player : public Actor
{
	const string TEX_PATH = "Graphics/king.png";
	const string WALK_SOUND_PATH = "Sounds/stepX.ogg";
	static const int STEPS = 4;
public:
	Player();
	void update();
	void control();

private:
	sf::Sound steps[STEPS];
};

#endif // PLAYER_HPP_INCLUDED
