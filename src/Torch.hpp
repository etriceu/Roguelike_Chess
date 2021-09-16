#ifndef TORCH_HPP_INCLUDED
#define TORCH_HPP_INCLUDED

#include "Resources.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include "Settings.hpp"

class Torch : public Object
{
	static constexpr string_view SOUND_PATH = "Sounds/fire.ogg";
	static constexpr string_view TEX_PATH = "Graphics/torch.png";
	static constexpr float LBRIGHT = 1.8f;
	static constexpr float LRADIUS = 0.05f;
	static constexpr struct{float x, y;} OFFSET = {8.f, 14.f};
	static const uint32_t LCOLOR = 0xffdb6400;
	static const int FRAMES = 6;
	static const int FWIDTH = 16;
	static const int FHEIGHT = 32;
	static const int FTIME = 100;

	static constexpr float MIN_DIST = 48.f;
	static constexpr float ATTENUATE = 20.f;

public:
	Torch(sf::Vector2i pos);
	~Torch();
	void update();

	static Light *light;
	static sf::Clock *clock;

private:
	static sf::Texture *tx;

	int frame;
	sf::Time nextTime;
	sf::Sound fireSound;
};

#endif // TORCH_HPP_INCLUDED
