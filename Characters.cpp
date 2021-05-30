#include "Characters.h"

Character::Character() : pos()
{
	hp = MAX_HP;
	damage = 0;
	ability = '0';
	name = "";
}

Character::Character(size_t dmg, char ablty, string name)
{
	pos = Position(0, 0);
	hp = MAX_HP;
	damage = dmg;
	ability = ablty;
	this->name = name;
}

string Character::get_name() const
{
	return name;
}

Position Character::get_pos() const
{
	return pos;
}

char Character::get_ability() const
{
	return ability;
}

size_t Character::get_dmg() const
{
	return damage;
}

int Character::get_hp() const
{
	return hp;
}

void Character::pos_set(Position pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

void Character::heal()
{
	hp = MAX_HP;
}

void Character::inflict_dmg(size_t dmg)
{
	hp -= dmg;
}

void Character::set_dmg(size_t dmg)
{
	damage = dmg;
}

std::ostream& operator<<(std::ostream& stream, const Character& hero)
{
	stream.write((char*)&hero.damage, sizeof(size_t));
	stream.write((char*)&hero.ability, sizeof(char));
	stream << hero.pos;
	stream << hero.name;
	return stream;
}

std::istream& operator>>(std::istream& stream, Character& hero)
{
	stream.read((char*)&hero.damage, sizeof(size_t));
	stream.read((char*)&hero.ability, sizeof(char));
	stream >> hero.pos;
	stream >> hero.name;
	return stream;
}

bool operator==(const Character& lhs, const Character& rhs)
{
	return lhs.get_name() == rhs.get_name();
}

bool operator!=(const Character& lhs, const Character& rhs)
{
	return !(lhs == rhs);
}