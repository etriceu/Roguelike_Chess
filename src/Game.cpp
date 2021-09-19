#include "Game.hpp"

Game::Game()
	: mainMenu(TITLE)
{
	settings.init(&window, CONF_PATH, TITLE);
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
		{
			if(clock.getElapsedTime().asSeconds() >= tickTime.asSeconds())
			{
				update();
				clock.restart();
			}
			else
				sf::sleep(sf::microseconds(10));
		}
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
		if(settings.maxFPS)
			tickTime = sf::seconds(1.f/max((int)settings.maxFPS, TICK_PER_SEC));
		else
			tickTime = sf::seconds(0);

		UIView = window.getDefaultView();
		gameView = UIView;
		gameView.zoom(0.5);
	}
	else if(event.type == sf::Event::GainedFocus)
		isActive = true;
	else if(event.type == sf::Event::LostFocus)
		isActive = false;
	else
	{
		char retState = state == MENU ? mainMenu.event(event) : 0;

		if(retState == MainMenu::NEW || retState == MainMenu::BACK2GAME)
		{
			if(retState == MainMenu::NEW)
				world.newMap();

			state = GAME;
		}
		else if(state == GAME)
		{
			auto key = Control::controls.find(event.key.code);
			if(event.type == sf::Event::KeyPressed &&
				key != Control::controls.end() && key->second == Control::ESC)
			{
				state = MENU;
			}
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
			gameView.setCenter(world.getPlayer()->getPosition());
			window.setView(gameView);
			world.draw(window);
		} break;
		case MENU:
			window.draw(mainMenu);
			break;
	}
}

void Game::renderThread(Game* game)
{
	settings.apply();
	while(game->window.isOpen())
    {
		while(game->window.pollEvent(game->event))
			game->events();

		game->window.clear();
		game->draw();

		if(game->isActive && game->state == GAME)
		{
			game->world.getPlayer()->control();
			game->window.setView(game->UIView);
			game->world.getPlayer()->drawUI(game->window);
		}

		game->window.display();
	}
	game->game = false;
}
