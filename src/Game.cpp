#include "Game.hpp"

Game::Game()
	: settings(&window, string(CONF_PATH), string(TITLE)),
	mainMenu(&settings, string(TITLE)),
	light(&preWindow)
{
	Torch::light = &light;
}

Game::~Game()
{

}

void Game::run()
{
	sf::Thread thread(&renderThread, this);
    thread.launch();

	while(game)
		while(window.isOpen())
			update();
	thread.wait();
}

void Game::events()
{
	if(event.type == sf::Event::Closed)
		window.close();
	else if(event.type == sf::Event::Resized)
	{
		sf::Vector2u size(event.size.width, event.size.height);
		window.setView(sf::View({0, 0, (float)size.x, (float)size.y}));
		mainMenu.resize();
		uint wmax = max(size.x, size.y);
		preWindow.create(wmax, wmax);
	}
	else
	{
		if(state == MENU && mainMenu.event(event) == MainMenu::NEW)
		{
			world.newMap();
			state = GAME;
		}
		if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
			state = MENU;
	}
}

void Game::update()
{
	switch(state)
	{
		case GAME:
			world.update();
		break;
		case MENU:
			break;
	};
}

void Game::draw()
{
	switch(state)
	{
		case GAME:
		{
			preWindow.draw(world);
			preWindow.display();
			window.draw(light);
		} break;
		case MENU:
			window.draw(mainMenu);
			break;
	}
}

void Game::renderThread(Game* game)
{
	game->settings.apply();
	while(game->window.isOpen())
    {
		while(game->window.pollEvent(game->event))
			game->events();

		game->window.clear();
		game->preWindow.clear();
		game->draw();
		game->window.display();
	}
	game->game = false;
}
