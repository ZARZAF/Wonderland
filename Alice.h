#pragma once
#include "Characters.h" //including Position, String
#include "Items.h"

class Alice : public Character					     /*  /6 slot\  */
{												     /* |Backpack| */
	static const size_t Inventar_Max_Capacity = 6;   /* |__ __ __| */
	Items inventar[Inventar_Max_Capacity];		     /* |__ __ __| */
	size_t items_count;
	int equiped_weapon;
	size_t steps_made;
public:
	Alice();

	void pick_item(const Items& item);
	void equip_item();
	void move(char direction);
};// alice cpp op= .... if needed
//nesuznatelno nasledenite klasove gi pravq posledni 