#include <fstream>

#include "MainMenu.hpp"

using namespace std;

MainMenu::MainMenu(string title)
{
	sf::Font *font = fonts(string(FONT_PATH));
	this->title.setFont(*font);
	this->title.setString(title);
	this->title.setCharacterSize(TITLE_SIZE);

	menu.resize(TEXT.size());
	for(size_t m = 0; m < TEXT.size(); m++)
		for(size_t n = 0; n < TEXT[m].size(); n++)
		{
			menu[m].push_back(sf::Text(TEXT[m][n], *font, TEXT_SIZE));
			menu[m].back().setFillColor(IN_ACT_COLOR);
		}

	menu[MAIN].pop_back();
	menu[MAIN][current].setFillColor(ACT_COLOR);
	functions();

	clickSound.setBuffer(*sounds(string(SOUND_PATH)));
	clickSound.setRelativeToListener(true);
	settings.addSound(&clickSound);
}

void MainMenu::resize()
{
	sf::Vector2u size(settings.mode.width, settings.mode.height);
	title.setPosition((size.x-title.getLocalBounds().width)/2,
					 (size.y-title.getLocalBounds().height)/13);

	for(size_t m = 0; m < TEXT.size(); m++)
		for(size_t n = 0; n < menu[m].size(); n++)
		{
			sf::FloatRect r = menu[m][n].getLocalBounds();
			menu[m][n].setPosition((size.x-r.width)/2,
				size.y/3+n*(size.y-r.height)/menu[m].size()/3);
		}
}

int MainMenu::event(sf::Event e)
{
	int ret = 0;
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
				menu[state][n].setFillColor(IN_ACT_COLOR);

			menu[state][current].setFillColor(ACT_COLOR);
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
				clickSound.play();
				ret = funcs[state][n](this, NEXT);
				break;
			}
		}
	}
	if(e.type == sf::Event::KeyPressed)
	{
		menu[state][current].setFillColor(IN_ACT_COLOR);
		auto key = Control::controls.find(e.key.code);
		if(key != Control::controls.end())
		{
			if(key->second == Control::ENTER || key->second == Control::RIGHT)
			{
				clickSound.play();
				ret = funcs[state][current](this, NEXT);
			}
			else if(key->second == Control::LEFT)
			{
				clickSound.play();
				ret = funcs[state][current](this, PREVIOUS);
			}
			else if(key->second == Control::UP)
				current--;
			else if(key->second == Control::DOWN)
				current++;
			else if(key->second == Control::ESC)
			{
				current = 0;
				if(state != MAIN)
					state = MAIN;
				else if(swapped)
					return BACK2GAME;
			}

			if(current < 0)
				current = menu[state].size()-1;
			else if(current > (int)menu[state].size()-1)
				current = 0;
		}
	}
	menu[state][current].setFillColor(ACT_COLOR);
	return ret;
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(title, states);

	for(const sf::Text &t : menu[state])
		target.draw(t, states);
}
