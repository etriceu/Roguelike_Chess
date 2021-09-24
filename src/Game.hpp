#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "MainMenu.hpp"
#include "World.hpp"

class Game
{
	const int TICK_PER_SEC = 200;
	const string TITLE = "Roguelike Chess";
	const string CONF_PATH = "config.cfg";
	const vector<pair<u_int, float>> SCALES = {
		{480, 0.9}, {768, 0.7}, {1200, 0.5}, {999999, 0.25}};
	enum State {MENU, GAME};

public:
	Game();
	~Game();
	void run();

private:
	void events();
	void update();
	void draw();
	static void renderThread(Game *game);

	sf::View gameView, UIView, fightView;

	MainMenu mainMenu;
	World world;
	State state = MENU;
	bool game = true;
	bool isActive = true;
	sf::Clock clock;
	sf::Time tickTime;

	sf::RenderWindow window;
	sf::Event event;
};

#endif // GAME_HPP_INCLUDED
