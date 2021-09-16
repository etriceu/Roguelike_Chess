#include "Player.hpp"
#include "Controls.hpp"
#include "Enemy.hpp"

Player::Player()
{
	setTexture(*textures(TEX_PATH));
	type = PLAYER;
	collidable = true;
}

void Player::control()
{
	for(auto c : Control::controls)
		if(sf::Keyboard::isKeyPressed(c.first))
		{
			move(c.second);
			for(auto &it : map->rooms)
				for(auto &obj : it.second)
					if(obj->type == ENEMY)
						static_cast<Enemy*>(obj)->move();

			break;
		}
}
