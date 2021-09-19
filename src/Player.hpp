#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "Actor.hpp"
#include "Settings.hpp"
#include "Artifact.hpp"

class Player : public Actor
{
	const string FONT_PATH = "Fonts/uni0553.ttf";
	const string ARIFACT_PATH = "Graphics/artifacts.png";
	const string TEX_PATH = "Graphics/king.png";
	const string WALK_SOUND_PATH = "Sounds/stepX.ogg";
	static const int STEPS = 4;
	const int INFO_SIZE = 24;
	const sf::Color INFO_COLOR = {255, 255, 255, 255};
	const float INFO_TIME = 10;

	const float LBRIGHT = 0.8f;
	const float LRADIUS = 0.03f;
	const struct{float x, y;} OFFSET = {8.f, 9.f};
	const int32_t LCOLOR = 0xffffff00;

public:
	Player();
	void update();
	void control();
	void drawUI(sf::RenderTarget &rt);

	static Light *light;

private:
	sf::Sound steps[STEPS];

	sf::Text info[2];
	sf::Clock infoClock;
	sf::Sprite artifacts[Artifact::ART_NUM];

	bool lantern = 0, hammer = 0, clock = 0, flag = 0, diplomacy = 0;
};

#endif // PLAYER_HPP_INCLUDED
