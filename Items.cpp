#include "items.h"



Items::Items(string name, char ablty) : pos()
{
	this->name = name;
	this->ability = ablty;
}

void Items::set_pos(Position setter)
{
	pos = setter;
}

string Items::get_name() const
{
	return name;
}

Position Items::get_pos() const
{
	return pos;
}

std::ostream& operator<<(std::ostream& stream, const Items& item)
{
	stream.write((char*)&item.pos, sizeof(Position));
	stream.write((char*)&item.ability, sizeof(char));
	stream << item.name;
	return stream;
}

std::istream& operator>>(std::istream& stream, Items& item)
{
	stream.read((char*)&item.pos, sizeof(Position));
	stream.read((char*)&item.ability, sizeof(char));
	stream >> item.name;
	return stream;
}

bool operator==(const Items& lhs, const Items& rhs)
{
	return lhs.get_name() == rhs.get_name();
}

bool operator!=(const Items& lhs, const Items& rhs)
{
	return !(lhs == rhs);
}