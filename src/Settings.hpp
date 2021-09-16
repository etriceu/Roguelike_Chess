#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <list>

#include "custom.hpp"

class Settings
{
public:
	void init(sf::RenderWindow *window, string path, string title);
	void save();
	void apply();
	void addSound(sf::Sound *s);
	void removeSound(sf::Sound *s);

	bool fullScreen, vsync;
	short maxFPS;
	short soundEffects;
	vector <sf::VideoMode> modes;
	sf::VideoMode mode;

private:
	sf::RenderWindow *window;
	string path, title;
	list <sf::Sound*> sounds;
};

extern Settings settings;

#endif // SETTINGS_HPP_INCLUDED
