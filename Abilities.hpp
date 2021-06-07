#pragma once
#include <cstdlib>
#include "Map.h"


static size_t crit_dmg_3x(size_t dmg)
{
	size_t	random_quotient = rand() % 21 + 10; // [0,20] + 10 = [10,30]
	return (dmg * random_quotient) / 10;
}

static Position gen_random_pos(const Map& map)
{
	Position rand_pos;
	do
	{
		size_t	random_x = rand() % map.get_size();
		size_t	random_y = rand() % map.get_size();
		rand_pos.x = random_x;
		rand_pos.y = random_y;
	} while (check_cell_unwalkable(map, rand_pos));
	return rand_pos;
}

static void teleport(const Map& map, Character& hero)
{
	Position random = gen_random_pos(map);
	hero.pos_set(random);
}

//abilities can be used by any hero!! abstract!!
static void action(const Map& map, Character& hero, bool& victorious, Alice& alice)
{
	switch (hero.get_ability())
	{
	case '0':
	{
		return;
	}
	case '1':
	{
		teleport(map, alice);
		victorious = true;
		return;
	}
	case '2':
	{
		if (victorious == true)
			teleport(map, alice);
		hero.set_dmg(crit_dmg_3x(10));
		victorious = false;
		return;
	}
	default: break;
	}
}
	

