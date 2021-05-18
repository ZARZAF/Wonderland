#pragma once
#include "String.h"

struct Position
{
	size_t x;
	size_t y;

	Position()
	{
		x = y = 0;
	}

	Position(size_t x, size_t y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==( const Position& rhs)
	{
		return this->x == rhs.x && this->y == rhs.y;
	}

	Position move_up()
	{
		y--;
		return *this;
	}

	Position move_down()
	{
		y++;
		return *this;
	}

	Position move_left()
	{
		x--;
		return *this;
	}

	Position move_right()
	{
		x++;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Position& pos)
	{
		stream << pos.x << pos.y;
		return stream;
	}
	friend std::istream& operator>>(std::istream& stream, Position& pos)
	{
		stream >> pos.x >> pos.y;
		return stream;
	}
};
