#pragma once
#include "Map.h" //including Container, Map, Alice, Character, Position, String, Items + (iostream, fstream) + (<chrono>, <thread>)!
#include "Abilities.hpp"																						  
#include <conio.h>
#include <stdlib.h>


static void battle(Map& map, Alice& alice, size_t i) // i comes from matching_pos function below 
{
	bool victorious = false;

	std::cout << "Prepare for battle with " << alice.get_map().get_heroes()[i].get_name() << std::endl;

	Position alice_start_pos = alice.get_pos();
	alice.equip_item();

	if (!(alice.get_pos() == alice_start_pos))
	{
		victorious = true;
	}

	Character enemie = map.get_heroes()[i];

	while (alice.get_hp() > 0 && !victorious)
	{
		if (enemie.get_hp() <= 0)
		{
			victorious = true;
		}

		action(map, enemie, victorious, alice);
		if (victorious)
			break;
		
		enemie.inflict_dmg(alice.get_dmg());

		alice.inflict_dmg(enemie.get_dmg());
	}
	
	if (alice.get_hp() <= 0 && !victorious)
	{
		std::cout << "Defeat" << std::endl;
		alice.heal();
		alice.get_map().get_heroes()[i].heal();
		map.load_alice(alice);
		if (enemie.get_hp() <= 0)
			map.remove_hero(alice.get_map().get_heroes()[i]);
	}
	else
	{
		std::cout << "Victory" << std::endl;
		alice.heal();
		map.remove_hero(alice.get_map().get_heroes()[i]);
		alice.remove_item();
	}
}

static void picking_item(Map& map,Alice& alice, size_t i) // i comes from matching_pos function below
{
	Items found_item = map.get_items()[i];
	if (!alice.item_in_invetrar(found_item))
	{
		alice.pick_item(map.get_items()[i]);
		std::cout << map.get_items()[i].get_name() << " picked!" << std::endl;
	}
	return;
}

static void matching_pos(Map& map, Alice& alice)
{
	if (!map.get_heroes().is_empty())
	{
		Character empty;
		for (size_t i = 0; i < map.get_heroes().get_size(); i++)
		{
			if (map.get_heroes()[i] != empty)
			{
				if (alice.get_pos() == map.get_heroes()[i].get_pos())
				{
					battle(map,alice, i);
				}
			}
		}
	}

	if (map.get_items().is_empty())
		return;

	Items empty_i;
	for (size_t i = 0; i < map.get_items().get_size(); i++)
	{
		if (map.get_items()[i] != empty_i)
		{
			if (alice.get_pos() == map.get_items()[i].get_pos())
			{
				picking_item(map,alice, i);
			}
		}
		
	}
}

static char player_input()   // https://cboard.cprogramming.com/cplusplus-programming/1656-how-do-you-represent-arrow-keys-cplusplus.html
{							// Using arrow keys #including <conio.h>, <stdlib.h>
	char key = _getch();
	if ((key == static_cast<char>(0xe0)) || (key == static_cast<char>(0x00)))
	{
		key = _getch();
	}

	switch (key)
	{
	case 'K': //left arrow 
	{
		return 'l';
	}
	case 'M': //right arrow 
	{
		return 'r';
	}
	case 'H': //up arrow 
	{
		return 'u';
	}
	case 'P': //down arrow
	{
		return 'd';
	}
	case 'I':
	case 'i': //inventory
	{

		return 'i';
	}
	case 'E':
	case 'e':
		return 'e';
	default:
	{
		break;
	}
	}
	return '0';
}

static void play(Alice& alice, container<Map>& maps)
{
	size_t maps_count = maps.get_size();
	bool exit_game = false;

	std::cout << "Hello! you need to find your way out of the " << maps_count << " mazes. But be careful there are heroes waiting for you and weapons you can use against them. Good luck" << std::endl;

	for (size_t i = 0; i < maps_count && !exit_game; i++)
	{
		alice.enter_map(maps[i]);


		while (!maps[i].pos_is_exit_portal(alice.get_pos()) && !exit_game)
		{
			std::cout << "Heroes left: " << maps[i].get_number_of_heroes() << "| Items left: " << maps[i].get_number_of_items() << std::endl;
			maps[i].visualize_map(alice.get_pos());
			switch (player_input())
			{
			case 'l': //left arrow 
			{
				alice.move('l');

				if (!valid_move(alice, maps[i]))
				{
					alice.move('r');
				}
				break;
			}
			case 'r': //right arrow 
			{
				alice.move('r');
				if (!valid_move(alice, maps[i]))
				{
					alice.move('l');
				}
				break;
				
			}
			case 'u': //up arrow 
			{
				alice.move('u');
				if (!valid_move(alice, maps[i]))
				{
					alice.move('d');
				}
				break;
				
			}
			case 'd': //down arrow
			{
				alice.move('d');
				if (!valid_move(alice, maps[i]))
				{
					alice.move('u');
				}
				break;
				
			}
			case 'I':
			case 'i': //inventory
			{
				alice.equip_item();
				break;
				
			}
			case 'E':
			case 'e':
				exit_game = true;
			default:
			{
				break;
			}
			}
			system("cls");
			matching_pos(maps[i], alice);

		}


	}
}