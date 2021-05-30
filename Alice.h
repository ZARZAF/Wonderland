#pragma once
#include "Characters.h" //including Position, String
#include "Items.h"
#include <chrono>
#include <thread>

class Map;

class Alice : public Character					     /*  /6 slot\  */
{												     /* |Backpack| */
	static const size_t Inventar_Max_Capacity = 6;	 /* |__ __ __| */
	static const size_t Alice_Base_Damage = 15;	     /* |__ __ __| */
	Items inventar[Inventar_Max_Capacity];		     
	size_t items_count;
	int equiped_weapon;
	size_t steps_made;
	const Map* current_map;

public:
	Alice();

	const Map& get_map() const;

	void pick_item(const Items& item);
	void equip_item();
	void move(char direction);
	void enter_map(const Map& map);
	bool item_in_invetrar(Items& item);
	void remove_item(Items item);
	void remove_item();
	size_t find_empty_space();
	Items get_equipped_item();
};