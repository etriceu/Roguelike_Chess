#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Resources.hpp"
#include "Settings.hpp"
#include "MainMenu.hpp"

class Game
{
	const string TITLE = "Roguelike Chess";
	const string CONF_PATH = "config.cfg";

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

	sf::RenderWindow window;
	sf::Event event;
};

#endif // GAME_HPP_INCLUDED
