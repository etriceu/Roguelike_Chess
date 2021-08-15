#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "custom.hpp"

class Settings
{
public:
	Settings(){}
	Settings(sf::RenderWindow *window, string path, string title);
	void save();
	void apply();

	bool fullScreen, vsync;
	short maxFPS;
	vector <sf::VideoMode> modes;
	sf::VideoMode mode;

private:
	sf::RenderWindow *window;
	string path, title;
};

#endif // SETTINGS_HPP_INCLUDED
