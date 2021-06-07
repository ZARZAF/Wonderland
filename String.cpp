#include "String.h"
#include <cstring>
#include <stdexcept>


string::string()
{
	len = 0;
	str = new char[len + 1];
	str[0] = '\0';
}

string::string(char c, size_t len)
{
	this->len = len;
	str = new char[len + 1];
	for (size_t i = 0; i < len; i++)
	{
		str[i] = c;
	}
	str[len] = '\0';
}

string::string(const char* str)
{
	len = std::strlen(str);
	this->str = new char[len + 1];
	strcpy(this->str, str);
}

string::string(const string& other)
{
	copy(other);
}

string& string::operator=(const string& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

string::~string()
{
	
	free();
}

void string::copy(const string& other)
{
	len = other.len;
	str = new char[len + 1];
	strcpy(this->str, other.str);
}

string::string(string&& other) noexcept
{
	move_copy(other);
}

string& string::operator=(string&& other) noexcept
{
	free();
	move_copy(other);
	return *this;
}

void string::move_copy(string& other)
{
	len = other.len;
	str = other.str;
	other.str = nullptr;
}

void string::free()
{
	delete[] str;
}

bool string::contains(const string& other) const
{
	return (strstr(str, other.str) != nullptr);
}

void string::resize(size_t size)
{
	delete[] str;
	str = new char[size];
	len = size - 1;
}

string string::substr(size_t k) const
{
	string new_str;
	if (len >= k)
	{
		new_str.resize(len - k + 1);
		int i = k;
		do
		{
			new_str.str[i-k] = str[i];
		}while (str[i++] != '\0');
	}
	return new_str;
}

string string::substr(size_t k, size_t t) const
{
	string new_str;
	if (len >= k && t >= 0 && (k <=t))
	{
		int resize = t - k + 1;
		if (str[t] != '\0') resize++;
		new_str.resize(resize);
		for (size_t i = k; i <= t; i++)
		{
			new_str.str[i - k] = str[i];
		}
		new_str.str[resize-1] = '\0';
	}
	return new_str;
}

const char* string::get_str() const
{
	return str;
}

char& string::operator[](size_t pos)
{
	if (pos > len)
		throw std::invalid_argument("Invalid position");

	return str[pos];
}

char string::operator[](size_t pos) const
{
	if ( pos > len)
		throw std::invalid_argument("Invalid position");

	return str[pos];
}

std::ostream& operator<<(std::ostream& stream, const string& str)
{
	size_t read_len = str.strlen() + 1;
	for (size_t i = 0; i < read_len; i++)
	{
		stream << str[i];
	}
	return stream;
}

void fill(string& tb_fileld, const string& filler)
{
	for (size_t i = 0; i < filler.len; i++)
	{
		tb_fileld[i] = filler[i];
	}
}

std::istream& operator>>(std::istream& stream, string& str)
{
	int i = 0;
	string temp;
	char c;
	str.resize(4);

	while(true)
	{
		if (i == str.len)
		{
			str[i] = '\0';
			temp = str;
			str.resize(str.len * 2);
			fill(str, temp);
		}
		stream.get(c);
		if (c == '\n' || c == '\0') break;
		str[i++] = c;
	}

	if (i == 0)
	{
		str = temp;
		return stream;
	}

	temp = str.substr(0, i-1); //i-1 because op= takes care of '\0'
	str = temp;

	return stream;
}

string& string::operator+=(const string& other)
{

	if (len == 0)
		return *this;
	string temp;
	temp = *this;
	resize(temp.len + other.len + 1);
	for (size_t i = 0; i < temp.len; i++)
	{
		str[i] = temp.str[i];
	}
	
	for (size_t i = 0; i < other.len; i++)
	{
		str[i+ temp.len] = other.str[i];
	}
	str[temp.len + other.len] = '\0';
	return *this;
}

const string operator+(const string& lhs, const string& rhs)
{
	string lhs_copy = lhs;
	lhs_copy += rhs;

	return lhs_copy;
}

string& string::operator*(size_t k)
{
	string temp = *this;
	for (size_t i = 0; i < k-1; i++) // k-1 *this already contains 1 copy of itself
	{
		*this += temp;
	}
	return *this;
}

size_t string::strlen() const
{
	return len;
}



size_t min(size_t x, size_t y)
{
	return x > y ? x : y;
}

bool string::operator<(const string& other) const
{
	size_t min_len = min(len, other.len);
	for (size_t i = 0; i < min_len; i++)
	{
		if (str[i] < other.str[i]) return true;
	}
	return false;
}

bool string::operator>(const string& other) const
{
	size_t min_len = min(len, other.len);
	for (size_t i = 0; i < min_len; i++)
	{
		if (str[i] > other.str[i]) return true;
	}
	return false;
}

bool string::operator<=(const string& other) const
{
	return operator<(other) || operator==(other);
}
bool string::operator>=(const string& other) const
{
	return operator>(other) || operator==(other);
}
bool string::operator==(const string& other) const
{
	if (len == other.len)
	{
		for (size_t i = 0; i < len; i++)
		{
			if (str[i] != other.str[i]) return false;
		}
		return true;
	}
	return false;
}
bool string::operator!=(const string& other) const
{
	return !operator==(other);
}
