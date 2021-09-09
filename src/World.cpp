#include "World.hpp"

#include <algorithm>

World::World()
	: MapGenerator(&preWindow)
{
	Torch::clock = &clock;
	int wmax = max(WIDTH, HEIGHT)*TILE_SIZE;
	preWindow.create(wmax, wmax);
}

void World::draw(sf::RenderTarget& target)
{
	sf::RenderStates states;
	states.texture = tileset;
	preWindow.clear();

	preWindow.draw(vertices, states);
	for(auto c : crystals)
		preWindow.draw(c);

	for(auto t : torches)
		t.draw(&preWindow, 1);

	preWindow.draw(player);

	for(auto t : torches)
		t.draw(&preWindow, 0);

	preWindow.display();
	target.draw(light);
}

void World::update()
{
	for(Torch &t : torches)
		t.update();

	player.update();
}

void World::movePlayer(char dir)
{
	if(dir == Player::LEFT && tiles[player.x-1][player.y].type == FLOOR)
		player.move(dir);
	else if(dir == Player::RIGHT && tiles[player.x+1][player.y].type == FLOOR)
		player.move(dir);
	else if(dir == Player::UP && tiles[player.x][player.y-1].type == FLOOR)
		player.move(dir);
	else if(dir == Player::DOWN && tiles[player.x][player.y+1].type == FLOOR)
		player.move(dir);
}
