#include "Light.hpp"
#include <cmath>

Light::Light(int width, int height)
{
	staticLight.create(width, height, sf::Color(ambient));
}

void Light::makeLight(sf::Image &img, sf::Vector2f pos, sf::Color color,
							  float bright, float radius)
{
	sf::IntRect r = {max<int>(pos.x-radius, 0), max<int>(pos.y-radius, 0),
					min<int>(pos.x+radius, img.getSize().x),
					min<int>(pos.y+radius, img.getSize().y)};

	for(uint x = r.left; x < r.width; x++)
	for(uint y = r.top; y < r.height; y++)
	{
		sf::Color c = img.getPixel(x, y);
		double xx = pos.x-x;
		double yy = pos.y-y;
		double d = sqrt(xx*xx+yy*yy);
		if(d <= radius)
		{
			double l = bright*min(max(1.0-d/radius, 0.0), 1.0);
			c.r = min(c.r+color.r*l, 255.0);
			c.g = min(c.g+color.g*l, 255.0);
			c.b = min(c.b+color.b*l, 255.0);
			c.a = 255;
		}
		img.setPixel(x, y, c);
	}
}

void Light::addLight(sf::Vector2f pos, sf::Color color, float bright, float radius)
{
	makeLight(staticLight, pos, color, bright, radius*WIDTH);
}

void Light::setPlayerLight(sf::Color color, float bright, float radius)
{
	pc = color;
	pb = bright;
	pr = radius;
}

void Light::setPlayerLightPos(sf::Vector2f pos)
{
	if(pos.x < 0)
		return;

	finalLight = staticLight;
	makeLight(finalLight, {pos.x, pos.y}, pc, pb, pr*WIDTH);
	tx.update(finalLight);
}

void Light::apply()
{
	finalLight = staticLight;
	tx.loadFromImage(finalLight);
	light.setTexture(tx);
	light.setPosition(0, 0);
}

void Light::clear()
{
	staticLight.create(staticLight.getSize().x, staticLight.getSize().y, sf::Color(ambient));
}

void Light::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(light, sf::BlendMultiply);
}
