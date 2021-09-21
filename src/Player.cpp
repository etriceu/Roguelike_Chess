#include "Player.hpp"
#include "Controls.hpp"
#include "Enemy.hpp"

#include <cmath>

Light *Player::light;
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
	for(auto &t : info)
	{
		t.setFont(*fonts(FONT_PATH));
		t.setCharacterSize(INFO_SIZE);
		t.setPosition(100, 40);
	}
	for(int n = 0; n < Artifact::ART_NUM; n++)
	{
		artifacts[n].setTexture(*textures(ARIFACT_PATH));
		artifacts[n].setTextureRect({n*Artifact::FSIZE, 0, Artifact::FSIZE, Artifact::FSIZE});
		artifacts[n].setPosition(n*Artifact::FSIZE*2, 0);
		artifacts[n].setScale(2, 2);
	}

	light->setPlayerLight(sf::Color(LCOLOR), LBRIGHT);
}

void Player::update()
{
	if(info[0].getString().getSize() != 0)
	{
		sf::Color c = INFO_COLOR;
		float time = infoClock.getElapsedTime().asSeconds();
		if(time >= INFO_TIME)
		{
			info[0].setString("");
			info[1].setString("");
		}
		c.a = 255-time/INFO_TIME*255;
		info[0].setFillColor(c);
		info[1].setFillColor(c);
	}

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
	light->setPlayerLightPos({getPosition().x+OFFSET.x, getPosition().y+OFFSET.y},
							 enabled_artifacts[Artifact::LANTERN] ? LRADIUS : -1);
}

void Player::control()
{
	for(auto c : Control::controls)
		if(sf::Keyboard::isKeyPressed(c.first))
		{
			Object *obj = nullptr;
			if(!fight)
			{
				obj = move((Direction)c.second);
				Object *e = nullptr;
				if(obj != nullptr)
				{
					for(auto &it : map->rooms)
						for(auto &o : it.second)
							if(o->type == ENEMY)
							{
								Object *buf = static_cast<Enemy*>(o)->move();
								if(buf != nullptr && buf->type == PLAYER)
									obj = o;
							}
				}
			}
			if(obj == nullptr)
				break;

			if(obj->type == ENEMY)
			{
				setPosition(ceil(room.left+(room.width-1)/2), room.top+room.height-1);
				fight = true;
			}
			else if(obj->type == ARTIFACT)
			{
				Artifact *a = static_cast<Artifact*>(obj);
				map->rooms[room].remove(obj);
				if(!enabled_artifacts[a->artId])
				{
					info[0].setString(string(Artifact::info[a->artId][0]));
					info[1].setString(string(Artifact::info[a->artId][1]));
					enabled_artifacts[a->artId] = true;
				}
				for(int n = 0; n < LEN(info); n++)
					info[n].setPosition(
						(settings.mode.width-info[n].getLocalBounds().width)/2,
						n*info[0].getLocalBounds().height);

				infoClock.restart();
				delete a;
			}
			break;
		}
}

void Player::drawUI(sf::RenderTarget& rt)
{
	rt.draw(info[0]);
	rt.draw(info[1]);
}

