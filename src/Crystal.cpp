#include "Crystal.hpp"
#include <cmath>

sf::Texture *Crystal::tx = textures(string(Crystal::TEX_PATH));
Light *Crystal::light;

Crystal::Crystal(sf::Vector2f pos)
{
	quad = sf::VertexArray(sf::Quads, 4);

	quad[0].position = pos + sf::Vector2f(0, FSIZE);
	quad[1].position = pos;
	quad[2].position = pos + sf::Vector2f(FSIZE, 0);
	quad[3].position = pos + sf::Vector2f(FSIZE, FSIZE);

	float frame = rand()/(RAND_MAX+1.0)*(tx->getSize().x/FSIZE);
	frame = floor(frame);

	quad[0].texCoords = {frame*FSIZE, FSIZE};
	quad[1].texCoords = {frame*FSIZE, 0};
	quad[2].texCoords = {(frame+1)*FSIZE, 0};
	quad[3].texCoords = {(frame+1)*FSIZE, FSIZE};

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

void Crystal::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	//states.texture = tx;
	target.draw(quad, tx);
}
