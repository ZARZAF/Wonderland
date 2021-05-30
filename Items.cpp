#include "items.h"
#include "Alice.h"
#include "Functions.hpp"

Items::Items() : name(), pos()
{
	ability = '0';
}

Items::Items(string name, char ablty) : pos()
{
	this->name = name;
	this->ability = ablty;
}

void Items::set_pos(Position setter)
{
	pos = setter;
}

void Items::activate(Alice& alice)
{
	switch (ability)
	{
	case '1':
	{
		size_t num_of_moves = 3;

		std::cout << "Enter direction to move 3 spaces. Use arrow keys:";
		char direction = player_input();

		Position valitadting(alice.get_pos());

		for (size_t i = 0; i < num_of_moves; i++)
		{
			alice.move(direction);
		}
		if (!valid_move(alice, alice.get_map()))
		{
			alice.move(direction);
			if (!valid_move(alice, alice.get_map()))
			{
				switch (direction)
				{
				case 'r': direction = 'l';
				case 'l': direction = 'r';
				case 'u': direction = 'd';
				case 'd': direction = 'u';
				}
				for (size_t i = 0; i < num_of_moves + 1; i++)
				{
					alice.move(direction);
				}
			}
		}
		
		break;
	}
	
	case '3':
	{
		alice.set_dmg(10);
		break;
	}
	case '4':
	{
		alice.set_dmg(40);
		break;
	}
	case '5':
	{
		alice.set_dmg(35);
		break;
	}
	case '6':
	{
		size_t allowed_moves = 2;
		for (size_t i = 0; i < allowed_moves; i++)
		{
			switch (player_input())
			{
			case 'l': //left arrow 
			{
				alice.move('l');

				if (!valid_move(alice, alice.get_map()))
				{
					alice.move('r');
				}
				break;
			}
			case 'r': //right arrow 
			{
				alice.move('r');
				if (!valid_move(alice, alice.get_map()))
				{
					alice.move('l');
				}
				break;

			}
			case 'u': //up arrow 
			{
				alice.move('u');
				if (!valid_move(alice, alice.get_map()))
				{
					alice.move('d');
				}
				break;

			}
			case 'd': //down arrow
			{
				alice.move('d');
				if (!valid_move(alice, alice.get_map()))
				{
					alice.move('u');
				}
				break;

			}
			case 'I':
			case 'i': //inventory
			{
				alice.equip_item();
				break;

			}
			default:
			{
				break;
			}
			}
			system("cls");
			alice.get_map().visualize_map(alice.get_pos());
		}
		break;
	}
	case '7':
	{
		int rose_dmg = rand() % 2;
		if (rose_dmg == 0)
			alice.set_dmg(40);
		else alice.set_dmg(10);
		break;
	}
	default: break;
	}
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
	stream << item.pos;
	stream.write((char*)&item.ability, sizeof(char));
	stream << item.name;
	return stream;
}

std::istream& operator>>(std::istream& stream, Items& item)
{
	stream >> item.pos;
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