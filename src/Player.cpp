#include "Player.hpp"
#include "Controls.hpp"
#include "Enemy.hpp"

Player::Player()
{
	setTexture(*textures(TEX_PATH));
	type = PLAYER;
	collidable = true;

	string path = WALK_SOUND_PATH;
	for(int n = 0; n < STEPS; n++)
	{
		path[path.size()-5] = n+49;
		steps[n].setBuffer(*sounds(path));
		steps[n].setRelativeToListener(true);
		settings.addSound(&steps[n]);
	}
}

void Player::update()
{
	if(moveDir != NONE)
	{
		bool step = false;
		for(auto &s : steps)
			if(s.getStatus() == sf::SoundSource::Playing)
			{
				step = true;
				break;
			}
		if(!step)
			steps[rand()%STEPS].play();
	}
	sf::Listener::setPosition(getPosition().x, 0.f, getPosition().y);
	Actor::update();
}

void Player::control()
{
	for(auto c : Control::controls)
		if(sf::Keyboard::isKeyPressed(c.first))
		{
			if(move((Direction)c.second) != nullptr)
			{
				for(auto &it : map->rooms)
					for(auto &obj : it.second)
						if(obj->type == ENEMY)
							static_cast<Enemy*>(obj)->move();
			}
			break;
		}
}
