#pragma once
#include"Position.hpp"
#include <cstring>
#include "String.h"

class Character
{
protected:
	static const size_t MAX_HP = 100;
	Position pos;
	int hp;
	size_t damage;
	char ability;
	string name;
public:
	Character();
	Character(size_t dmg, char ablty, string name);

	void pos_set(Position pos);
	void inflict_dmg(size_t dmg);
	void set_dmg(size_t dmg);
	void heal();
	string get_name() const;
	Position get_pos() const;
	char get_ability() const;
	size_t get_dmg() const;
	int get_hp() const;

	friend std::ostream& operator<<(std::ostream& stream, const Character& hero);
	friend std::istream& operator>>(std::istream& stream, Character& hero);

};

bool operator==(const Character& lhs, const Character& rhs);
bool operator!=(const Character& lhs, const Character& rhs);