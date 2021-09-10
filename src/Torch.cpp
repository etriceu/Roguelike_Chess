#include "Torch.hpp"

sf::Texture *Torch::tx = textures(string(Torch::TEX_PATH));
Light *Torch::light;
sf::Clock *Torch::clock;

Torch::Torch(sf::Vector2f pos)
{
	frame = rand()%FRAMES;

	setTexture(*tx);
	setPosition(pos);
	light->addLight({pos.x+LOFFSET.x, pos.y+LOFFSET.y}, sf::Color(LCOLOR), LBRIGHT, LRADIUS);

	setTextureRect({frame*FWIDTH, 0, FWIDTH, FHEIGHT});
}

void Torch::update()
{
	if(clock->getElapsedTime().asMilliseconds() >= nextTime.asMilliseconds())
	{
		frame = (frame+1)%FRAMES;
		setTextureRect({frame*FWIDTH, 0, FWIDTH, FHEIGHT});
		nextTime = clock->getElapsedTime() + sf::milliseconds(FTIME);
	}
}
