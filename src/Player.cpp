#include "Player.hpp"

Player::Player(int tileSize)
	: TILE_SIZE(tileSize)
{
	setTexture(*textures(TEX_PATH));
}

void Player::update()
{
	if(dir != NONE && (x*TILE_SIZE != getPosition().x) !=
		(y*TILE_SIZE-TILE_SIZE/3 != getPosition().y))
	{
		if(walk.getElapsedTime().asSeconds() >= 1/WALK_SPEED)
		{
			switch(dir)
			{
				case LEFT: sf::Sprite::move(-1, 0); break;
				case RIGHT: sf::Sprite::move(1, 0); break;
				case UP: sf::Sprite::move(0, -1); break;
				case DOWN: sf::Sprite::move(0, 1);
			}
			walk.restart();
		}
	}
	else
		dir = NONE;

	if(walkAnim.getElapsedTime().asMilliseconds() >= WALK_TIME)
	{
		if(dir != NONE)
		{
			setFrame(WALK[dir][anim]);
			anim = (anim+1)%WALK[dir].size();
		}
		else
		{
			setFrame(STAND[standDir]);
			anim = 0;
		}
		walkAnim.restart();
	}
}

void Player::move(char dir)
{
	if(this->dir != NONE)
		return;

	switch(dir)
	{
		case LEFT: x--; break;
		case RIGHT: x++; break;
		case UP: y--; break;
		case DOWN: y++;
	}
	standDir = dir;
	this->dir = dir;
}

void Player::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	sf::Sprite::setPosition(x*TILE_SIZE, y*TILE_SIZE-TILE_SIZE/3);
	setFrame(DEFAULT_FRAME);
	standDir = DOWN;
}

void Player::setFrame(char frame)
{
	int x = getTexture()->getSize().x/WIDTH;
	setTextureRect({frame%x*WIDTH, frame/x*HEIGHT, WIDTH, HEIGHT});
}
