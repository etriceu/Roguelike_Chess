#ifndef TORCH_HPP_INCLUDED
#define TORCH_HPP_INCLUDED

#include "Resources.hpp"
#include "Light.hpp"

class Torch
{
	static constexpr string_view TEX_PATH = "Graphics/torch.png";
	static constexpr float LBRIGHT = 1.8f;
	static constexpr float LRADIUS = 0.05f;
	static constexpr struct{float x, y;} LOFFSET = {8.f, 14.f};
	static const uint32_t LCOLOR = 0xffdb6400;
	static const int FRAMES = 6;
	static const int FSIZE = 16;
	static const int FTIME = 100;

public:
	Torch(sf::Vector2f pos);
	void update();
	void draw(sf::RenderTarget *target, bool layer);

	static Light *light;
	static sf::Clock *clock;

private:
	static sf::Texture *tx;

	sf::Sprite layers[2];
	int frame;
	sf::Time nextTime;
};

#endif // TORCH_HPP_INCLUDED
