#include "Light.hpp"
#include <cmath>

Light::Light(sf::RenderTexture *preWindow)
{
	if(!sf::Shader::isAvailable())
	{
		log("Shader system isn't available\n");
		exit(0);
	}

	if(!shader.loadFromFile("Shaders/light.frag", sf::Shader::Fragment))
	{
		log("Unable to open file: Shaders/light.frag\n");
		exit(0);
	}

	shader.setUniform("texture", sf::Shader::CurrentTexture);
	shader.setUniform("ambient", sf::Glsl::Vec3(0.2, 0.2, 0.2));
	shader.setUniform("size", 0);

	rt = preWindow;
}

bool Light::addLight(sf::Vector2f pos, sf::Color color, float bright, float radius)
{
	if(colors.size() >= MAX_LIGHTS)
		return false;

	sf::Vector2u ws = rt->getSize();
	circles.push_back({pos.x/ws.x, (ws.y-pos.y)/ws.y, radius*WIDTH/ws.x});
	colors.push_back({color.r/255.f, color.g/255.f, color.b/255.f, bright});
	return true;
}

void Light::apply()
{
	int size = colors.size();
	shader.setUniform("size", size);
	shader.setUniformArray("color", colors.data(), size);
	shader.setUniformArray("circle", circles.data(), size);
}

void Light::clear()
{
	colors.clear();
	circles.clear();
	shader.setUniform("size", 0);
}

void Light::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sf::Sprite(rt->getTexture()), &shader);
}
