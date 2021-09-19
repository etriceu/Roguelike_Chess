#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "custom.hpp"

class Light : public sf::Drawable
{
	static constexpr int MAX_LIGHTS = 96;
	static constexpr int WIDTH = 1680;
public:
	Light(sf::RenderTexture *preWindow);

	bool addLight(sf::Vector2f pos, sf::Color color, float bright, float radius);
	void apply();
	void clear();
	void setPlayerLight(sf::Color color, float bright);
	void setPlayerLightPos(sf::Vector2f pos, float radius);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Shader shader;
	sf::RenderTexture *rt;

	vector <sf::Glsl::Vec4> colors;
	vector <sf::Glsl::Vec3> circles;
	sf::Glsl::Vec4 playerColor;
	sf::Glsl::Vec3 playerCircle;
};

#endif // LIGHT_HPP_INCLUDED
