#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "MainMenu.hpp"
#include "World.hpp"

class Game
{
	const string TITLE = "Roguelike Chess";
	const string CONF_PATH = "config.cfg";
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

	Settings settings;
	MainMenu mainMenu;
	World world;
	State state = MENU;

	sf::RenderWindow window;
	sf::Event event;
};

#endif // GAME_HPP_INCLUDED
