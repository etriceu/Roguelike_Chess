#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "custom.hpp"

class Light : public sf::Drawable
{
	static constexpr int WIDTH = 1680;
	static constexpr uint32_t ambient = 0x323232ff;
public:
	Light(int width, int height);

	void addLight(sf::Vector2f pos, sf::Color color, float bright, float radius);
	void apply();
	void clear();
	void setPlayerLight(sf::Color color, float bright, float radius);
	void setPlayerLightPos(sf::Vector2f pos);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void makeLight(sf::Image &img, sf::Vector2f pos, sf::Color color,
				   float bright, float radius);

	sf::Image staticLight, finalLight;
	sf::Texture tx;
	sf::Sprite light;
	sf::Color pc;
	float pb, pr;
};

#endif // LIGHT_HPP_INCLUDED
