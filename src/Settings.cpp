#include <fstream>
#include "Settings.hpp"

Settings::Settings(string path)
	: path(path)
{
	fstream cfg(path, ios::in);
	if(!cfg.good())
	{
		log("Unable to open file: %s\n", path.c_str());
		return;
	}

	cfg>>fullScreen>>vsync>>maxFPS>>mode.width>>mode.height;
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
		<<mode.width<<endl<<mode.height<<endl;

	cfg<<"#full screen 0-1"<<endl
	<<"#vsync 0-1"<<endl
	<<"#FPS limit N (If set to 0 then no limit)"<<endl
	<<"#width N (If set to 0 it will automatically detect the resolution)"<<endl
	<<"#height N"<<endl;

	cfg.close();
}
