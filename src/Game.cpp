#include "Game.hpp"

Game::Game()
	: settings(&window, CONF_PATH, TITLE), mainMenu(&settings, TITLE)
{

}

Game::~Game()
{

}

void Game::run()
{
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
		mainMenu.resize();
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

}

void Game::draw()
{
	switch(state)
	{
		case MENU:
			window.draw(mainMenu);
			break;
		case GAME:
			window.draw(world);
			break;
	};
}

void Game::renderThread(Game* game)
{
	game->settings.apply();
	while(game->window.isOpen())
    {
		while(game->window.pollEvent(game->event))
			game->events();

		game->window.clear();
		game->draw();
		game->window.display();
	}
}
