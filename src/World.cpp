#include "World.hpp"

#include <algorithm>

World::World()
	: vertices(sf::Quads)
{
	tileset = textures(TEX_PATH);
	Torch::clock = &clock;
}

void World::newMap()
{
	const int MARGIN = 1;

	fill_n(*tiles, SIZE, Tile());
	vertices.clear();
	Torch::light->clear();
	torches.clear();
	vector <sf::IntRect> rooms;

	for(int x = 2; x < WIDTH-1; x++)
		for(int y = 2; y < HEIGHT-1; y++)
			if(rand()/(RAND_MAX+1.0) <= ROOM_CHANCE)
			{
				int w = 8;
				int h = 8;
				if(x+w+2 < WIDTH && y+h+MARGIN < HEIGHT)
				{
					bool intersects = false;
					for(sf::IntRect r : rooms)
					{
						r.top -= MARGIN;
						r.left -= MARGIN;
						r.height += MARGIN;
						r.width += MARGIN;
						if(r.intersects({x-MARGIN, y-MARGIN, w+MARGIN, h+MARGIN}))
						{
							intersects = true;
							break;
						}
					}
					if(!intersects)
						rooms.push_back({x, y, w, h});
				}
			}

	buildRooms(rooms);
	if(buildTunnels(rooms) && fixTiles())
	{
		addObjects(rooms);
		updateMap();
	}
	else
		newMap();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = tileset;
	target.draw(vertices, states);
	for(auto t : torches)
	{
		t.draw(&target, 0);
		t.draw(&target, 1);
	}
}

void World::buildRooms(vector<sf::IntRect> rooms)
{
	for(sf::IntRect &r : rooms)
	{
		for(int x = r.left; x < r.left+r.width; x++)
			for(int y = r.top; y < r.top+r.height; y++)
				tiles[x][y].type = FLOOR;

		for(int x = r.left-1; x <= r.left+r.width; x++)
		{
			tiles[x][r.top-1].type = WALL;
			tiles[x][r.top+r.height].type = WALL;
		}
		for(int y = r.top-1; y <= r.top+r.height; y++)
		{
			tiles[r.left-1][y].type = WALL;
			tiles[r.left+r.width][y].type = WALL;
		}
	}
}

void World::addObjects(vector<sf::IntRect> rooms)
{
	for(auto r : rooms)
	{
		vector <sf::Vector2i> pos;
		for(int n = 0, num = rand()%(MAX_TORCH+1); n < num; n++)
		{
			sf::Vector2i p = {rand()%(r.width-2)+r.left+1, rand()%(r.height-2)+r.top+1};
			bool valid = true;
			for(auto pp : pos)
				if(pp == p)
				{
					n--;
					valid = false;
				}

			if(valid)
			{
				pos.push_back(p);
				torches.push_back(Torch(sf::Vector2f(p.x*TILE_SIZE, p.y*TILE_SIZE)));
			}
		}
	}
	Torch::light->apply();
}


bool World::setTunnelFloor(int x, int y, sf::IntRect r1, sf::IntRect r2)
{
	if(tiles[x][y].type != WALL ||
		r1.contains(x, y-1) || r1.contains(x, y+1) ||
		r2.contains(x, y-1) || r2.contains(x, y+1) ||
		r1.contains(x-1, y) || r1.contains(x+1, y) ||
		r2.contains(x-1, y) || r2.contains(x+1, y))
	{
		tiles[x][y].type = FLOOR;
		return false;
	}
	return true;
}

bool World::buildTunnels(vector<sf::IntRect> rooms)
{
	int res = 0;
	vector<sf::IntRect> buf = rooms;
	while(rooms.size() && !res)
	{
		sf::IntRect r1 = rooms.back(), r2 = {-1, 0, 0, 0};
		for(size_t n = 0, min = SIZE; n < rooms.size()-1; n++)
		{
			int x = r1.left-rooms[n].left, y = r1.top-rooms[n].top;
			size_t d = x*x+y*y;
			if(min > d)
			{
				min = d;
				r2 = rooms[n];
			}
		}

		rooms.pop_back();
		if(r2.left == -1)
			continue;

		int x1 = min(r1.left, r2.left), x2 = max(r1.left+r1.width, r2.left+r2.width);
		int y1 = min(r1.top, r2.top), y2 = max(r1.top+r1.height, r2.top+r2.height);

		int cx = x1+(x2-x1)/2, cy = y1+(y2-y1)/2;

		if(r1.intersects({r2.left, r1.top, r2.width, r2.height}))
			for(int y = min(r1.top, r2.top); y < max(r1.top, r2.top); y++)
			{
				res += setTunnelFloor(cx, y, r1, r2);
				if(tiles[cx-1][y].type == EMPTY)
				{
					tiles[cx+1][y].type = WALL;
					tiles[cx-1][y].type = WALL;
				}
			}
		else if(r1.intersects({r1.left, r2.top, r2.width, r2.height}))
			for(int x = min(r1.left, r2.left); x < max(r1.left, r2.left); x++)
			{
				res += setTunnelFloor(x, cy, r1, r2);
				if(tiles[x][cy+1].type == EMPTY)
				{
					tiles[x][cy-1].type = WALL;
					tiles[x][cy+1].type = WALL;
				}
			}
		else
		{
			if(r1.top > r2.top)
				swap(r1, r2);

			if(r1.left < r2.left)
			{
				x1 = r1.left+r1.width;
				y1 = r1.top+r1.height-1;
				x2 = r2.left;
				y2 = r2.top;
			}
			else
			{
				x1 = r2.left+r2.width-1;
				y1 = r1.top+r1.height-1;
				x2 = r1.left;
				y2 = r2.top;
			}
			if(tiles[x1-1][y1-1].type == EMPTY)
				tiles[x1-1][y1-1].type = WALL;
			if(tiles[x2+1][y1-1].type == EMPTY)
				tiles[x2+1][y1-1].type = WALL;

			for(int x = x1; x <= x2; x++)
			{
				res += setTunnelFloor(x, y1, r1, r2);
				if(tiles[x][y1-1].type == EMPTY)
					tiles[x][y1-1].type = WALL;
				if(tiles[x][y1+1].type == EMPTY)
					tiles[x][y1+1].type = WALL;
			}
			for(int y = y1; y < y2; y++)
			{
				int x = r1.left < r2.left ? x2 : x1;
				res += setTunnelFloor(x, y, r1, r2);
				if(tiles[x+1][y].type == EMPTY)
					tiles[x+1][y].type = WALL;
				if(tiles[x-1][y].type == EMPTY)
					tiles[x-1][y].type = WALL;
			}
		}
	}
	return res ? false : true;
}

bool World::fixTiles()
{
	const vector <array <char, 11>> tab = {
		{-1, -1, -1, -1, WALL, WALL, -1, WALL, FLOOR, 0, 4},
		{-1, FLOOR, FLOOR, WALL, WALL, FLOOR, -1, WALL, -1, 8, 4},
		{-1, -1, -1, WALL, WALL, WALL, -1, FLOOR, -1, 4, 4},
		{-1, -1, -1, FLOOR, WALL, FLOOR, -1, -1, -1, 16, 2},
		{FLOOR, FLOOR, FLOOR, FLOOR, WALL, FLOOR, -1, WALL, -1, 12, 4},
		{-1, WALL, -1, FLOOR, WALL, WALL, -1, WALL, FLOOR, 18, 4},
		{-1, FLOOR, -1, WALL, WALL, WALL, -1, WALL, FLOOR, 22, 4},
		{-1, -1, -1, WALL, WALL, WALL, FLOOR, WALL, FLOOR, 26, 4},
		{FLOOR, WALL, -1, WALL, WALL, WALL, -1, WALL, FLOOR, 30, 2},
		{-1, FLOOR, -1, WALL, WALL, WALL, FLOOR, WALL, FLOOR, 32, 4},
		{FLOOR, FLOOR, -1, FLOOR, WALL, WALL, -1, WALL, FLOOR, 36, 4},
		{FLOOR, WALL, FLOOR, WALL, WALL, WALL, FLOOR, WALL, -1, 40, 4},
		{FLOOR, WALL, FLOOR, WALL, WALL, WALL, FLOOR, WALL, FLOOR, 44, 1}};

	const int F_HALF_SIZ = (FLOORX-FLOOR)/2;
	const int rotate[] = {6, 3, 0, 7, 4, 1, 8, 5, 2};

	for(int y = 1, f = 0; y < HEIGHT; y++, (WIDTH%2 ? f++ : f))
		for(int x = 1; x < WIDTH; x++, f++)
		{
			if(tiles[x][y].type == WALL)
			{
				for(auto matrix : tab)
					for(int a = 0; a < matrix[10]; a++)
					{
						int valid = 0;
						for(int yy = -1, n = 0; yy < 2; yy++)
							for(int xx = -1; xx < 2; xx++, n++)
								if(matrix[n] == -1 || tiles[x+xx][y+yy].type == matrix[n])
									valid++;

						if(valid == matrix.size()-2)
						{
							tiles[x][y].index = WALL+a+matrix[9];
							break;
						}

						auto buf = matrix;
						for(int n = 0; n < 9; n++)
							matrix[n] = buf[rotate[n]];
					}

				if(tiles[x][y].type == WALL && tiles[x][y].index == 0)
					return false;
			}
			else if(tiles[x][y].type == FLOOR)
			{
				if(rand()/(RAND_MAX+1.0) < RANDOM_FLOOR)
					tiles[x][y].index = rand()%F_HALF_SIZ+FLOOR+1+(f%2 ? F_HALF_SIZ : 0);
				else
					tiles[x][y].index = (f%2 ? F_HALF_SIZ+FLOOR+1 : FLOOR);
			}
		}
	return true;
}

void World::updateMap()
{
	for(int y = 1; y < HEIGHT; y++)
		for(int x = 1; x < WIDTH; x++)
		{
			if(tiles[x][y].type == EMPTY)
				continue;

			float tx = tiles[x][y].index%(tileset->getSize().x/TILE_SIZE);
			float ty = tiles[x][y].index/(tileset->getSize().x/TILE_SIZE);

			sf::Vertex quad[4];
			quad[0].position = sf::Vector2f(x*TILE_SIZE, y*TILE_SIZE);
			quad[1].position = sf::Vector2f((x+1)*TILE_SIZE, y*TILE_SIZE);
			quad[2].position = sf::Vector2f((x+1)*TILE_SIZE, (y+1)*TILE_SIZE);
			quad[3].position = sf::Vector2f(x*16, (y+1) *TILE_SIZE);

			quad[0].texCoords = sf::Vector2f(tx*TILE_SIZE, ty*TILE_SIZE);
			quad[1].texCoords = sf::Vector2f((tx+1)*TILE_SIZE, ty*TILE_SIZE);
			quad[2].texCoords = sf::Vector2f((tx+1)*TILE_SIZE, (ty+1)*TILE_SIZE);
			quad[3].texCoords = sf::Vector2f(tx*TILE_SIZE, (ty+1)*TILE_SIZE);

			for(int n = 0; n < 4; n++)
				vertices.append(quad[n]);
		}
}

void World::update()
{
	for(Torch &t : torches)
		t.update();
}
