#include "Torch.hpp"

sf::Texture *Torch::tx = textures(string(Torch::TEX_PATH));
Light *Torch::light;
sf::Clock *Torch::clock;

Torch::Torch(sf::Vector2f pos)
{
	frame = rand()%FRAMES;

	layers[0].setTexture(*tx);
	layers[1].setTexture(*tx);

	layers[0].setPosition(pos);
	layers[1].setPosition(pos.x, pos.y+FSIZE);
	light->addLight({pos.x+LOFFSET.x, pos.y+LOFFSET.y}, sf::Color(LCOLOR), LBRIGHT, LRADIUS);

	layers[0].setTextureRect({frame*FSIZE, 0, FSIZE, FSIZE});
	layers[1].setTextureRect({frame*FSIZE, FSIZE, FSIZE, FSIZE});
}

void Torch::update()
{
	if(clock->getElapsedTime().asMilliseconds() >= nextTime.asMilliseconds())
	{
		frame = (frame+1)%FRAMES;
		layers[0].setTextureRect({frame*FSIZE, 0, FSIZE, FSIZE});
		layers[1].setTextureRect({frame*FSIZE, FSIZE, FSIZE, FSIZE});
		nextTime = clock->getElapsedTime() + sf::milliseconds(FTIME);
	}
}

void Torch::draw(sf::RenderTarget *target, bool layer)
{
	target->draw(layers[layer]);
}
