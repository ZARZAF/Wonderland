#include "Map.h"

Map::Map() : name() , heroes() , items()
{
	map = nullptr;
	size = 0;
	entrance_portal = Position(0, 0);
	exit_portal = Position(0, 0);
}

Map::Map(string name, size_t size, char** map, container<Character>& heroes, container<Items>& items, Position entrance, Position exit)
{
	copy(name, size, map, heroes, items, entrance, exit);
}

Map::Map(const Map& other)
{
	copy(other.name, other.size, other.map, other.heroes, other.items, other.entrance_portal, other.exit_portal);
}

Map::Map(Map&& other)
{
	move_copy(std::move(other));
}

Map& Map::operator=(const Map& other)
{
	if (this != &other)
	{
		free();
		copy(other.name, other.size, other.map, other.heroes, other.items, other.entrance_portal, other.exit_portal);
	}
	return *this;
}

Map& Map::operator=(Map&& other) 
{
	free();
	move_copy(std::move(other));
	return *this;
}

Map::~Map()
{
	free();
}

void Map::copy(string name, size_t size, char** map, container<Character> heroes, container<Items> items, Position entrance, Position exit)
{
	this->name = name;
	this->size = size;
	this->map = new char* [size];
	for (size_t i = 0; i < size; i++)
	{
		this->map[i] = new char[size];
		for (size_t j = 0; j < size; j++)
		{
			this->map[i][j] = map[i][j];
		}
	}
	this->heroes = heroes;
	this->items = items;
	entrance_portal = entrance;
	exit_portal = exit;
}

void Map::move_copy(Map&& other)
{
	this->name = other.name;
	this->size = other.size;
	this->map = other.map;
	this->heroes = std::move(other.heroes);
	this->items = std::move(other.items);
	this->entrance_portal = other.entrance_portal;
	this->exit_portal = other.exit_portal;

	other.map = nullptr;
}

void Map::free()
{
	for (size_t i = 0; i < size && map != nullptr; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

void Map::set_name(string& str)
{
	name = str;
}

void Map::set_size(size_t size)
{
	if (size <= 2 || size > 30)
		throw std::invalid_argument("incorrect map size");
	this->size = size;
}

void Map::set_map(char** map)
{
	this->map = new char* [size];
	for (size_t i = 0; i < size; i++)
	{
		this->map[i] = new char[size];
		for (size_t j = 0; j < size; j++)
		{
			this->map[i][j] = map[i][j];
		}
	}
}

void Map::set_hero(Character& hero)
{
	heroes.add_item(hero);
}

void Map::set_item(Items& item)
{
	items.add_item(item);
}

bool Map::set_portal(char portal)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (map[i][j] == portal)
			{
				if (portal == 'e')
				{
					entrance_portal.y = i;
					entrance_portal.x = j;
				}
				else if (portal == 'x')
				{
					exit_portal.y = i;
					exit_portal.x = j;
				}
				return true;
			}
		}
	}
	return false;
}


string Map::get_name() const
{
	return name;
}

size_t Map::get_size() const
{
	return size;
}

Position Map::get_entrance() const
{
	return entrance_portal;
}

const container<Character>& Map::get_heroes() const
{
	return heroes;
}

const container<Items>& Map::get_items() const
{
	return items;
}


Position Map::get_exit() const
{
	return exit_portal;
}

size_t Map::get_number_of_heroes() const
{
	return heroes.get_size();
}

size_t Map::get_number_of_items() const
{
	return items.get_size();
}

void Map::remove_item(const Items& picked_item)
{
	items.remove_rearagne_item(picked_item);
}

void Map::remove_hero(const Character& slain_hero)
{
	heroes.remove_rearagne_item(slain_hero);
}

void Map::visualize_map(Position alice_pos) const
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (alice_pos.x == j && alice_pos.y == i)
				std::cout << 'A';
			else if (map[i][j] == free_space)
				std::cout << ' ';
			else
				std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}

void Map::load_alice(Alice& alice)
{
	alice.pos_set(entrance_portal);
}


std::ostream& operator<<(std::ostream& stream, const Map& map)
{
	stream << map.name;
	stream.write((char*)&map.size, sizeof(size_t));
	for (size_t i = 0; i < map.size; i++)
	{
		for (size_t j = 0; j < map.size; j++)
		{
			stream << map.map[i][j];
		}
	}
	stream << map.heroes << map.items;
	stream << map.entrance_portal;
	stream << map.exit_portal;
	return stream;
}

std::istream& operator>>(std::istream& stream, Map& map)
{
	stream >> map.name;
	map.free();
	stream.read((char*)&map.size, sizeof(size_t));
	map.map = new char* [map.size];
	for (size_t i = 0; i < map.size; i++)
	{
		map.map[i] = new char[map.size];
		for (size_t j = 0; j < map.size; j++)
		{
			stream >> map.map[i][j];
		}
	}
	stream >> map.heroes >> map.items;
	stream >> map.entrance_portal;
	stream >> map.exit_portal;
	return stream;
}

bool operator==(const Map& lhs, const Map& rhs)
{
	return lhs.get_name() == rhs.get_name();
}


char& Map::operator[](const Position& pos)
{
	if (!pos_in_map(*this, pos))
		throw std::invalid_argument("Position is not in the map");

	return map[pos.y][pos.x];
}

char Map::operator[](const Position& pos) const
{
	if (!pos_in_map(*this, pos))
		throw std::invalid_argument("Position is not in the map");

	return map[pos.y][pos.x];
}

bool pos_in_map(const Map& map, Position p)
{
	return p.x < map.get_size() && p.y < map.get_size() && p.x >= 0 && p.y >= 0;
}

bool check_cell_unwalkable(const Map& map, Position& p)
{
	return map[p] != free_space && map[p] != entrance_portal && map[p] != exit_portal;
}

bool Map::pos_is_exit_portal(Position pos) const
{
	return pos == exit_portal;
}

bool path_algorythm(Position pos, Map& map, size_t& steps)
{
	steps++;
	if (!pos_in_map(map, pos))
	{
		steps--;
		return false;
	}

	if (map.pos_is_exit_portal(pos))
		return true;

	if (check_cell_unwalkable(map, pos))
	{
		steps--;
		return false;
	}

	map[pos] = wall;

	path_algorythm(pos.move_right(), map, steps);
	path_algorythm(pos.move_down(), map, steps);
	path_algorythm(pos.move_left(), map, steps);
	path_algorythm(pos.move_up(), map, steps);

	map[pos] = free_space;
	return true;
}



size_t find_path_in_map(const Map& map, Position pos)
{
	size_t steps = 0;
	
	Map working_copy = map;

	path_algorythm(pos, working_copy, steps); 
	return steps;
}

bool correct_map(Map& map, size_t map_size)
{
	if (!(map.set_portal('e') && (map.set_portal('x')))) // checks if portals exsist in map prototype and fills them in the real map
		return false;

	return find_path_in_map(map, map.get_entrance()) != 0;
}

bool valid_move(const Alice& alice, const Map& map)
{
	Position temp = alice.get_pos(); // non-const Position
	return pos_in_map(map, temp) && !check_cell_unwalkable(map, temp);
}