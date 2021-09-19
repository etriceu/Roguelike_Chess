#include "Player.hpp"
#include "Controls.hpp"
#include "Enemy.hpp"

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
							 lantern ? LRADIUS : -1);
}

void Player::control()
{
	for(auto c : Control::controls)
		if(sf::Keyboard::isKeyPressed(c.first))
		{
			Object *obj = move((Direction)c.second);
			if(obj != nullptr)
			{
				for(auto &it : map->rooms)
					for(auto &obj : it.second)
						if(obj->type == ENEMY)
							static_cast<Enemy*>(obj)->move();
			}
			else
				break;

			if(obj->type == ARTIFACT)
			{
				Artifact *a = static_cast<Artifact*>(obj);
				map->rooms[room].remove(obj);
				if(a->artId == Artifact::LANTERN && !lantern)
				{
					info[0].setString("WOW! You found a lantern.");
					info[1].setString("Now everyone can see you in the dark ;)");
					lantern = true;
				} else if(a->artId == Artifact::HAMMER && !hammer)
				{
					info[0].setString("You found the most ordinary hammer.");
					info[1].setString("Just don't destroy anything.");
					hammer = true;
				} else if(a->artId == Artifact::CLOCK && !clock)
				{
					info[0].setString("From now on you can go back in time.");
					info[1].setString("Watch out for time paradoxes or the game will crash.");
					clock = true;
				} else if(a->artId == Artifact::FLAG && !flag)
				{
					info[0].setString("You found the white flag, the most useless artifact.");
					info[1].setString("You can save your life by escaping from the battlefield.");
					flag = true;
				} else if(a->artId == Artifact::DIPLOMACY && !diplomacy)
				{
					info[0].setString("You found a book called \"Diplomacy for the dummies\".");
					info[1].setString("You can bribe your opponent and run away with your army.");
					diplomacy = true;
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
	if(lantern) rt.draw(artifacts[Artifact::LANTERN]);
	if(hammer) rt.draw(artifacts[Artifact::HAMMER]);
	if(clock) rt.draw(artifacts[Artifact::CLOCK]);
	if(flag) rt.draw(artifacts[Artifact::FLAG]);
	if(diplomacy) rt.draw(artifacts[Artifact::DIPLOMACY]);
}

