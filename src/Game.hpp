#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "MainMenu.hpp"
#include "World.hpp"

class Game
{
	const int TICK_PER_SEC = 200;
	const string_view TITLE = "Roguelike Chess";
	const string_view CONF_PATH = "config.cfg";
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
