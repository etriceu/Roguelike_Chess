#include "Game.hpp"

Game::Game()
	: settings(&window, string(CONF_PATH), string(TITLE)),
	mainMenu(&settings, string(TITLE))
{

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
	}
	else
	{
		if(state == MENU && mainMenu.event(event) == MainMenu::NEW)
		{
			sf::View view = window.getView();
			view.zoom(0.5);
			window.setView(view);
			world.newMap();
			state = GAME;
		}
		if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.setView(window.getDefaultView());
			state = MENU;
		}
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
			sf::View view = window.getView();
			view.setCenter(world.player.getPosition());
			window.setView(view);
			world.draw(window);
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
		game->draw();
		game->window.display();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			game->world.movePlayer(Player::LEFT);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			game->world.movePlayer(Player::RIGHT);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			game->world.movePlayer(Player::UP);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			game->world.movePlayer(Player::DOWN);
	}
	game->game = false;
}
