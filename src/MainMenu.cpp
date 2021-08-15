#include <fstream>

#include "MainMenu.hpp"

using namespace std;

MainMenu::MainMenu(Settings *settings, string title)
	: settings(settings)
{
	sf::Font *font = fonts(fontPath);
	this->title.setFont(*font);
	this->title.setString(title);
	this->title.setCharacterSize(titleSize);

	menu.resize(text.size());
	for(size_t m = 0; m < text.size(); m++)
		for(size_t n = 0; n < text[m].size(); n++)
		{
			menu[m].push_back(sf::Text(text[m][n], *font, textSize));
			menu[m].back().setFillColor(inactiveColor);
		}

	menu[MAIN].pop_back();
	menu[MAIN][current].setFillColor(activeColor);
	functions();
}

void MainMenu::resize()
{
	sf::Vector2u size(settings->mode.width, settings->mode.height);
	title.setPosition((size.x-title.getLocalBounds().width)/2,
					 (size.y-title.getLocalBounds().height)/13);

	for(size_t m = 0; m < text.size(); m++)
		for(size_t n = 0; n < menu[m].size(); n++)
		{
			sf::FloatRect r = menu[m][n].getLocalBounds();
			menu[m][n].setPosition((size.x-r.width)/2,
				size.y/3+n*(size.y-r.height)/menu[m].size()/3);
		}
}

void MainMenu::event(sf::Event e)
{
	if(e.type == sf::Event::MouseMoved)
	{
		sf::Vector2i m(e.mouseMove.x, e.mouseMove.y);
		for(size_t n = 0; n < menu[state].size(); n++)
		{
			sf::FloatRect r = menu[state][n].getGlobalBounds();
			if(r.left <= m.x && r.left+r.width >= m.x &&
				r.top <= m.y && r.top+r.height >= m.y)
				current = n;
			else
				menu[state][n].setFillColor(inactiveColor);

			menu[state][current].setFillColor(activeColor);
		}
	}
	else if(e.type == sf::Event::MouseButtonReleased &&
			e.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i m(e.mouseButton.x, e.mouseButton.y);
		for(size_t n = 0; n < menu[state].size(); n++)
		{
			sf::FloatRect r = menu[state][n].getGlobalBounds();
			if(r.left <= m.x && r.left+r.width >= m.x &&
				r.top <= m.y && r.top+r.height >= m.y)
			{
				funcs[state][n](this, NEXT);
				break;
			}
		}
	}
	if(e.type == sf::Event::KeyPressed)
	{
		menu[state][current].setFillColor(inactiveColor);

		if(e.key.code == sf::Keyboard::Enter || e.key.code == sf::Keyboard::D ||
			e.key.code == sf::Keyboard::Right)
			funcs[state][current](this, NEXT);
		else if(e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left)
			funcs[state][current](this, PREVIOUS);
		else if(e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up)
			current--;
		else if(e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down)
			current++;

		if(current < 0)
			current = menu[state].size()-1;
		else if(current > (int)menu[state].size()-1)
			current = 0;

		menu[state][current].setFillColor(activeColor);
	}
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(title, states);

	for(const sf::Text &t : menu[state])
		target.draw(t, states);
}
