#include "Alice.h"

Alice::Alice() : Character()
{
	hp = MAX_HP;
	damage = 15; // Alice's dmg = 15
	name = "Alice";
	items_count = 0;
	steps_made = 0;
	equiped_weapon = -1;
}

void Alice::pick_item(const Items& item)
{
	if (items_count >= Inventar_Max_Capacity)
	{
		std::cout << "Inventory's full" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return;
	}
	else
	inventar[items_count++] = item;
}

void Alice::equip_item()
{
	if (items_count == 0)
	{
		std::cout << "Inventory's empty!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return;
	}

	std::cout << "0. exit" << std::endl;
	for (size_t i = 0; i < items_count; i++)
	{
		std::cout << i + 1 << ". " << inventar[i].get_name() << std::endl;
	}

	std::cout << "Please select an item: ";
	std::cin >> equiped_weapon;

	if (equiped_weapon > (int)items_count + 1)
	{
		equiped_weapon = -1;
		std::cout << "Invalid item";
		return;
	}

	std::cout << inventar[equiped_weapon - 1].get_name() << " equipped!" << std::endl;
}

void Alice::move(char direction)
{
	switch (direction)
	{
		case 'u':
		{
			pos.move_up();
			break;
		}
		case 'd':
		{
			pos.move_down();
			break;
		}
		case 'l':
		{
			pos.move_left();
			break;
		}
		case 'r':
		{
			pos.move_right();
			break;
		}
		default:
			break;
	}
}