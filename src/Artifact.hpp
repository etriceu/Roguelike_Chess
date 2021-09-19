#ifndef ARTIFACT_HPP_INCLUDED
#define ARTIFACT_HPP_INCLUDED

#include "Object.hpp"
#include "Resources.hpp"

class Artifact : public Object
{
	static constexpr string_view TEX_PATH = "Graphics/artifacts.png";

public:
	static constexpr int FSIZE = 16;
	enum ArtType{LANTERN, HAMMER, CLOCK, FLAG, DIPLOMACY, ART_NUM};

	Artifact(sf::Vector2i pos, ArtType artId)
	{
		this->artId = artId;
		x = pos.x;
		y = pos.y;
		pos.x *= TILE_SIZE;
		pos.y *= TILE_SIZE;

		setTexture(*tx);
		setPosition(pos.x, pos.y);

		setTextureRect({artId*FSIZE, 0, FSIZE, FSIZE});

		type = ARTIFACT;
		collidable = true;
	}

	ArtType artId;

private:
	inline static sf::Texture *tx = textures(string(Artifact::TEX_PATH));
};

#endif // ARTIFACT_HPP_INCLUDED
