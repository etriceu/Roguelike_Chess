#include "Crystal.hpp"
#include <cmath>

sf::Texture *Crystal::tx = textures(string(Crystal::TEX_PATH));
Light *Crystal::light;

Crystal::Crystal(sf::Vector2i pos)
{
	x = pos.x;
	y = pos.y;
	pos.x *= TILE_SIZE;
	pos.y *= TILE_SIZE;
	int frame = rand()/(RAND_MAX+1.0)*(tx->getSize().x/FSIZE);

	setTexture(*tx);
	setPosition(pos.x, pos.y);

	setTextureRect({frame*FSIZE, 0, FSIZE, FSIZE});

	type = CRYSTAL;

	light->addLight({pos.x+LOFFSET.x, pos.y+LOFFSET.y},
					color(rand()/(RAND_MAX+1.0)), LBRIGHT, LRADIUS);
}

sf::Color Crystal::color(double h)
{
	h *= 6;
    double r, g, b;
	if(h == 6)
		h = 0;

	double i = floor(h);
	double x = 1 - (h - i);
	double y = 1 - ( 1 - (h-i));

	if(i == 0){r = 1; g = y; b = 0;}
	else if(i == 1){r = x; g = 1; b = 0;}
	else if(i == 2){r = 0; g = 1; b = y;}
	else if(i == 3){r = 0; g = x; b = 1;}
	else if(i == 4){r = y; g = 0; b = 1;}
	else{r = 1; g = 0; b = x;}

	r *= 255;
	g *= 255;
	b *= 255;

	return sf::Color(r, g, b);
}
