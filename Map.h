#pragma once
#include "Alice.h" //including Character, Position, String, Items
#include "Container.hpp"

class Map
{
	string name;
	char** map;
	size_t size;
	container<Character> heroes;
	container<Items> items;
	Position entrance_portal;
	Position exit_portal;
	void copy(string name, size_t size, char** map, container<Character> heroes, container<Items> items, Position entrance, Position exit);
	void free();

public:
	Map();
	Map(string name, size_t size, char** map, container<Character> heroes, container<Items> items, Position entrance, Position exit);
	Map(const Map& other);
	Map& operator=(const Map & other);
	~Map();

	void set_name(string& size);
	void set_size(size_t size);
	void set_map(char** map);
	void set_hero(Character& hero);
	void set_item(Items& item);
	bool set_portal(char portal);

	string get_name() const;
	size_t get_size() const;
	Position get_entrance() const;
	size_t get_number_of_heroes() const;
	size_t get_number_of_items() const;

	void remove_item(const Items& picked_item);
	void remove_hero(const Character& slain_hero);
	const container<Character>& get_heroes() const;
	const container<Items>& get_items() const;
	Position get_exit() const;

	void visualize_map(Position alice_pos) const;
	void load_alice(Alice& alice);

	char& operator[](const Position& pos);
	char operator[](const Position& pos) const;

	bool pos_is_exit_portal(Position pos) const;

	friend std::ostream& operator<<(std::ostream& stream, const Map& map);
	friend std::istream& operator>>(std::istream& stream, Map& map);
	friend bool path_algorythm(Position start_pos, Map& map, size_t& steps);
	friend bool check_cell_unwalkable(const Map& map, Position& p);
	friend size_t find_path_in_map(const Map& map, Position pos);
	friend bool correct_map(Map& temp, size_t map_size);
	friend bool valid_move(const Alice& alice, const Map& map);
};

bool operator==(const Map& lhs, const Map& rhs);
bool pos_in_map(const Map& map, Position p);


enum map_symbols { wall = 'w', free_space = 'f', entrance_portal = 'e', exit_portal = 'x'};