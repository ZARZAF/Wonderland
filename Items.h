#pragma once
#include "Position.hpp"
#include "String.h"

class Items
{
	string name;
	Position pos;
	char ability;
public:
	Items() : name(), pos()
	{
		ability = '0';
	}
	Items(string name, char ablty);
	string get_name() const;
	Position get_pos() const;
	void set_pos(Position setter);

	friend std::ostream& operator<<(std::ostream& stream, const Items& item);
	friend std::istream& operator>>(std::istream& stream, Items& item);
};

bool operator==(const Items& lhs, const Items& rhs);
bool operator!=(const Items& lhs, const Items& rhs);