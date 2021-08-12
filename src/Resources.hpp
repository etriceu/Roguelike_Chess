#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>

#include "custom.hpp"

template <typename T>
class Resources
{
	map <string, T> res;

public:
	T* operator()(string name, bool custom = false)
	{
		size_t s = res.size();
		T *r = &res[name];
		if(s != res.size())
		{
			if(!custom && !r->loadFromFile(name))
			{
				log("Unable to open file: %s\n", name.c_str());
				return nullptr;
			}

			if(typeid(T) == typeid(sf::Texture))
				sf::Texture *tx = (sf::Texture*)r;
		}
		return r;
	}
};

static Resources <sf::Texture> textures;
static Resources <sf::Font> fonts;
static Resources <sf::SoundBuffer> sounds;

#endif // RESOURCES_HPP_INCLUDED
