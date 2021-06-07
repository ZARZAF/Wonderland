#include "Alice.h"
#include "Map.h"

Alice::Alice() : Character()
{
	hp = MAX_HP;
	damage = Alice_Base_Damage;
	name = "Alice";
	items_count = 0;
	steps_made = 0;
	equiped_weapon = -1;
}

const Map& Alice::get_map() const
{
	return *current_map;
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
	{
		inventar[find_empty_space()] = item;
		items_count++;
	}
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

	if (equiped_weapon == 0)
	{
		set_dmg(Alice_Base_Damage);
		--equiped_weapon;
		return;
	}

	if (equiped_weapon > (int)items_count + 1)
	{
		equiped_weapon = -1;
		std::cout << "Invalid item";
		return;
	}

	inventar[equiped_weapon - 1].activate(*this);

	std::cout << inventar[equiped_weapon - 1].get_name() << " equipped!" << std::endl;

	--equiped_weapon;// index n-1

	remove_item();
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

void Alice::enter_map(const Map& map)
{
	current_map = &map;
	pos_set(map.get_entrance());
}

bool Alice::item_in_invetrar(Items& item)
{
	for (size_t i = 0; i < Inventar_Max_Capacity; i++)
	{
		if (item == inventar[i])
			return true;
	}
	return false;
}

void Alice::remove_item(Items item)
{
	if (item == Items())
		return;

	for (size_t i = 0; i < Inventar_Max_Capacity; i++)
	{
		if (item == inventar[i])
		{
			inventar[i] = Items();
			return;
		}		
	}
	--items_count;
}

void Alice::remove_item()
{
	if (equiped_weapon == -1)
		return;
	inventar[equiped_weapon] = Items();
	equiped_weapon = -1;
	--items_count;
}

size_t Alice::find_empty_space()
{
	Items empty = Items();
	for (size_t i = 0; i < Inventar_Max_Capacity; i++)
	{
		if (inventar[i] == empty)
			return i;
	};
	return -1;
}

Items Alice::get_equipped_item()
{
	if (equiped_weapon == -1)
		return Items();

	return inventar[equiped_weapon];
}
