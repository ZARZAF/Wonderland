#pragma once
#include <cstdlib>


size_t crit_dmg_3x(size_t dmg)
{
	size_t	random_quotient = rand() % 20 + 11;
	return (dmg * random_quotient) / 10;
}