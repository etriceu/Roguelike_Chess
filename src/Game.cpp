#include "Game.hpp"

Game::Game()
	: settings(configFile)
{

}

Game::~Game()
{

}

void Game::run()
{
	window.create(settings.mode, title, settings.fullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	window.setActive(false);

	if(settings.maxFPS > 0 && !settings.vsync)
		window.setFramerateLimit(settings.maxFPS);

	sf::Thread thread(&renderThread, this);
    thread.launch();

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
	}
	else
	{

	}
}

void Game::update()
{

}

void Game::draw()
{

}

void Game::renderThread(Game* game)
{
	game->window.setActive(true);
	game->window.setVerticalSyncEnabled(game->settings.vsync);
	while(game->window.isOpen())
    {
		while(game->window.pollEvent(game->event))
			game->events();

		game->window.clear();
		game->draw();
		game->window.display();
	}
}


