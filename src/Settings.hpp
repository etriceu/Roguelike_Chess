#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "custom.hpp"

struct Settings
{
	Settings(string path);
	void save();
	bool fullScreen, vsync;
	short maxFPS;
	string path;
	vector <sf::VideoMode> modes;
	sf::VideoMode mode;
};

#endif // SETTINGS_HPP_INCLUDED
