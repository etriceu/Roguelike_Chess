#include "Torch.hpp"

sf::Texture *Torch::tx = textures(string(Torch::TEX_PATH));
Light *Torch::light;
sf::Clock *Torch::clock;

Torch::Torch(sf::Vector2i pos)
{
	x = pos.x;
	y = pos.y;
	pos.x *= TILE_SIZE;
	pos.y *= TILE_SIZE;
	frame = rand()%FRAMES;

	setTexture(*tx);
	setPosition(pos.x, pos.y);
	light->addLight({pos.x+LOFFSET.x, pos.y+LOFFSET.y}, sf::Color(LCOLOR), LBRIGHT, LRADIUS);

	setTextureRect({frame*FWIDTH, 0, FWIDTH, FHEIGHT});

	type = TORCH;

	fireSound.setBuffer(*sounds(string(SOUND_PATH)));
	settings.addSound(&fireSound);
	fireSound.setPosition(pos.x, 0, pos.y);
	fireSound.setMinDistance(MIN_DIST);
	fireSound.setAttenuation(ATTENUATE);
	fireSound.setLoop(true);
	fireSound.play();
}

Torch::~Torch()
{
	settings.removeSound(&fireSound);
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
