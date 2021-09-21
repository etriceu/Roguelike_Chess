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

	static constexpr string_view info[][2] = {
		{"WOW! You found a lantern.", "Now everyone can see you in the dark ;)"},
		{"You found the most ordinary hammer.", "Just don't destroy anything."},
		{"From now on you can go back in time.", "Watch out for time paradoxes or the game will crash."},
		{"You found the white flag, the most useless artifact.", "You can save your life by escaping from the battlefield."},
		{"You found a book called \"Diplomacy for the dummies\".", "You can bribe your opponent and run away with your army."}
	};

private:
	inline static sf::Texture *tx = textures(string(Artifact::TEX_PATH));
};

#endif // ARTIFACT_HPP_INCLUDED
