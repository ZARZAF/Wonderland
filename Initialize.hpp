#pragma once
#include "Map.h" //including Container, Map, Alice, Character, Position, String, Items + (iostream, fstream) + (<chrono>, <thread>)!																					  

container<Map> maps;
container<Character> heroes;
container<Items> items;
Alice alice;

void initialize()
{
	maps.load_from_file_list("maps.bin");
	heroes.load_from_file_list("heroes.bin");
	items.load_from_file_list("items.bin");
}

bool correct_prototype_line(const string& line, size_t map_size)
{
	if (line.strlen() != map_size) return false;

	for (size_t i = 0; i < map_size; i++)
	{
		if (line[i] != wall && line[i] != free_space && line[i] != entrance_portal && line[i] != exit_portal) return false;
	}
	return true;
}

char** string_to_char_prot(string* map_prototype, size_t map_size)
{
	char** prot = new char* [map_size];
	for (size_t i = 0; i < map_size; i++)
	{
		prot[i] = new char[map_size];
		for (size_t j = 0; j < map_size; j++)
		{
			prot[i][j] = map_prototype[i][j];
		}
	}
	return prot;
}

void create_map()
{
	Map new_map;

	string name;
	std::cout << "Please enter map's name: ";
	std::cin >> name;

	size_t map_size = 0;
	std::cout << "Please enter map's size: ";
	std::cin >> map_size;
	while (map_size < 3 || map_size > 30) //min, max map size just a formality
	{
		std::cout << "\033[A\rPlease reenter map's size [3, 30]: ";
		std::cin.ignore();
		std::cin >> map_size;
	}

	string guide_line('_', map_size);
	std::cout << "Use the these symbols to build the map. If you want to stop, type - 'cancel'.\nwall = 'w', free_sapce = 'f', entrance_portal = 'e', exit_portal = 'x'" << std::endl;
	std::cout << guide_line << std::endl;

	string* map_prototype = new string[map_size];

	string erace(' ', map_size);		// avoid realocating data in -> for + while iterations
	string incorect_line = "incorect line";
	std::cin.ignore();

	for (size_t i = 0; i < map_size; i++)
	{

		std::cin >> map_prototype[i];
		while (!correct_prototype_line(map_prototype[i], map_size))
		{
			if (map_prototype[i] == "cancel") return;
			std::cout << "\033[A\r";	//"\033[A\r" https://stackoverflow.com/questions/1508490/erase-the-current-printed-console-line
			std::cout << erace << '\r' << incorect_line;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << '\r' << erace << '\r';
			std::cin >> map_prototype[i];
		}
	}

	char** prot = string_to_char_prot(map_prototype, map_size);
	new_map.set_size(map_size);
	new_map.set_map(prot);
	new_map.set_name(name);

	if (!correct_map(new_map, map_size))
	{
		std::cout << ">incorrect map<";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	else
	{
		Position map_pos;
		size_t item = 0, hero = 0, x = 0, y = 0;
		Character set_hero;
		Items set_item;

		std::cout << "0. exit" << std::endl;
		heroes.print_list();
		do
		{
			std::cout << "select a coordinates: x y: ";
			std::cin >> x >> y;
			map_pos.x = x;
			map_pos.y = y;
			if (check_cell_unwalkable(new_map, map_pos))
				throw std::invalid_argument("Invalid coordinates");

			std::cout << "select a number: ";
			std::cin >> hero;
			if (hero == 0) break;
			set_hero = heroes[hero - 1];
			set_hero.pos_set(map_pos);
			new_map.set_hero(set_hero);
		} while (hero != 0);

		std::cout << "0. exit" << std::endl;
		items.print_list();

		do
		{
			std::cout << "select a coordinates: x y: ";
			std::cin >> x >> y;
			map_pos.x = x;
			map_pos.y = y;
			if (check_cell_unwalkable(new_map, map_pos))
				throw std::invalid_argument("Invalid coordinates");

			std::cout << "select a number: ";
			std::cin >> item;
			if (item == 0) break;
			set_item = items[item - 1];
			set_item.set_pos(map_pos);
			new_map.set_item(set_item);
		} while (item != 0);

		new_map.set_portal('e');
		new_map.set_portal('x');

		std::ofstream to_file("maps.bin", std::ios::binary | std::ios::app);

		if (!to_file)
			throw std::exception("maps.bin could't open");

		to_file << new_map;
	}

	for (size_t i = 0; i < map_size; i++)
	{
		delete[] prot[i];
	}
	delete[] prot;
	delete[] map_prototype;
	system("cls");
}

void create_hero()
{
	std::cout << "Name: ";
	string name;
	std::cin >> name;

	std::cout << "Damage: ";
	size_t dmg;
	std::cin >> dmg;

	std::cout << "Ability(char): ";
	char ablty;
	std::cin >> ablty;

	Character new_hero(dmg, ablty, name);

	if (heroes.find_item(new_hero) != -1)
		throw std::invalid_argument("This hero already exists");

	std::ofstream save_to_file("heroes.bin", std::ios::binary | std::ios::app);

	if (!save_to_file)
		throw std::exception("heroes.bin cound't open");

	save_to_file << new_hero;

	save_to_file.close();
}

void create_item()
{
	std::cout << "Item's name: ";
	string name;
	std::cin >> name;

	std::cout << "Ability(char): ";
	char ablty;
	std::cin >> ablty;

	Items new_item(name, ablty);

	std::ofstream save_to_file("items.bin", std::ios::binary | std::ios::app);

	if (!save_to_file)
		throw std::exception("items.bin cound't open");

	save_to_file << new_item;

	save_to_file.close();
}