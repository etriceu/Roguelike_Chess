#include <fstream>
#include "Settings.hpp"

Settings settings;

void Settings::init(sf::RenderWindow *window, string path, string title)
{
	this->window = window;
	this->path = path;
	this->title = title;

	fstream cfg(path, ios::in);
	if(!cfg.good())
	{
		log("Unable to open file: %s\n", path.c_str());
		return;
	}

	cfg>>fullScreen>>vsync>>maxFPS>>mode.width>>mode.height>>soundEffects;
	cfg.close();

	sf::VideoMode defaultMode = sf::VideoMode::getDesktopMode();

	mode.bitsPerPixel = defaultMode.bitsPerPixel;

	if(mode.width > defaultMode.width || mode.height > defaultMode.height ||
		mode.width <= 0 || mode.height <= 0)
	{
		mode = defaultMode;
		save();
	}

	modes = sf::VideoMode::getFullscreenModes();

	for(size_t n = 0; n < modes.size(); n++)
		if(modes[n].bitsPerPixel != modes[0].bitsPerPixel)
		{
			modes.erase(modes.begin()+n, modes.end());
			break;
		}
}

void Settings::save()
{
	fstream cfg(path, ios::out);

	if(!cfg.good())
	{
		log("Unable to save setting\n");
		return;
	}

	cfg<<fullScreen<<endl<<vsync<<endl<<maxFPS<<endl
		<<mode.width<<endl<<mode.height<<endl<<soundEffects<<endl;

	cfg<<"#full screen 0-1"<<endl
	<<"#vsync 0-1"<<endl
	<<"#FPS limit N (If set to 0 then no limit)"<<endl
	<<"#width N (If set to 0 it will automatically detect the resolution)"<<endl
	<<"#height N"<<endl
	<<"#sound Effects volume N (0-100)"<<endl;

	cfg.close();
}

void Settings::apply()
{
	window->setActive(false);
	window->create(mode, title, fullScreen ? sf::Style::Fullscreen :
		sf::Style::None | sf::Style::Close | sf::Style::Titlebar);

	if(maxFPS >= 0 && !vsync)
		window->setFramerateLimit(maxFPS);

	window->setVerticalSyncEnabled(vsync);

	if(!fullScreen)
		window->setPosition(sf::Vector2i(
			(sf::VideoMode::getDesktopMode().width-mode.width)/2,
			(sf::VideoMode::getDesktopMode().height-mode.height)/2));

	window->setActive(true);

	for(auto s : sounds)
		s->setVolume(soundEffects);
}

void Settings::addSound(sf::Sound* s)
{
	sounds.push_back(s);
}

void Settings::removeSound(sf::Sound* s)
{
	sounds.remove(s);
}

