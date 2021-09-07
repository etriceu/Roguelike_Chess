#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "custom.hpp"

class Light : public sf::Drawable
{
	static const int MAX_LIGHTS = 64;
	static const int WIDTH = 1680;
public:
	Light(sf::RenderTexture *preWindow);

	bool addLight(sf::Vector2f pos, sf::Color color, float bright, float radius);
	void apply();
	void clear();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Shader shader;
	sf::RenderTexture *rt;

	vector <sf::Glsl::Vec4> colors;
	vector <sf::Glsl::Vec3> circles;
};

#endif // LIGHT_HPP_INCLUDED
