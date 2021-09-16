#ifndef CRYSTAL_HPP_INCLUDED
#define CRYSTAL_HPP_INCLUDED

#include "Resources.hpp"
#include "Light.hpp"
#include "Object.hpp"

class Crystal : public Object
{
	static constexpr string_view TEX_PATH = "Graphics/crystals.png";
	static constexpr float LBRIGHT = 0.5f;
	static constexpr float LRADIUS = 0.02f;
	static const int FSIZE = 16;
	static constexpr struct{float x, y;} LOFFSET = {FSIZE/2, FSIZE/2};

public:
	Crystal(sf::Vector2i pos);

	static Light *light;

private:
	sf::Color color(double h);

	static sf::Texture *tx;
};

#endif // CRYSTAL_HPP_INCLUDED
