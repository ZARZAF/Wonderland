#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

class string
{
	char* str;
	size_t len;

	void copy(const string& other);
	void free();
	void move_copy(string& other);
	void resize(size_t size);
public:
	string();
	string(const char* str);
	string(char c, size_t len);
	string(const string& other);
	string& operator=(const string& other);
	string(string&& other) noexcept;
	string& operator=(string&& other) noexcept;

	bool contains(const string& other)const;
	string substr(size_t k)const;
	string substr(size_t k, size_t t) const;

	const char* get_str() const;
	char& operator[](size_t pos);
	char operator[](size_t pos) const;
	string& operator+=(const string& other);
	string& operator*(size_t k);
	size_t strlen() const;

	bool operator<(const string& other) const;
	bool operator>(const string& other) const;
	bool operator<=(const string& other) const;
	bool operator>=(const string& other) const;
	bool operator==(const string& other) const;
	bool operator!=(const string& other) const;

	~string();

	friend std::ostream& operator<<(std::ostream& stream, const string& str);
	friend std::istream& operator>>(std::istream& stream, string& str);

	friend void fill(string& tb_fileld, const string& filler);
};

