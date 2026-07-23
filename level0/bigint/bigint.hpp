#pragma once

#include <iostream>
#include <string>
#include <algorithm>

class bigint {
private:
	std::string str;
	unsigned int to_uint() const;
public:
	bigint();
	bigint(unsigned int num);

	bigint operator+(const bigint& other) const;
	bigint& operator+=(const bigint& other);
	bigint& operator++();
	bigint operator++(int);

	bigint operator<<(unsigned int num) const;
	bigint operator>>(unsigned int num) const;
	bigint& operator<<=(unsigned int num);
	bigint& operator>>=(unsigned int num);

	bigint operator<<(const bigint& other) const;
	bigint operator>>(const bigint& other) const;
	bigint& operator<<=(const bigint& other);
	bigint& operator>>=(const bigint& other);

	bool operator==(const bigint& other) const;
	bool operator!=(const bigint& other) const;
	bool operator<(const bigint& other) const;
	bool operator>(const bigint& other) const;
	bool operator<=(const bigint& other) const;
	bool operator>=(const bigint& other) const;
	friend std::ostream& operator<<(std::ostream& os, const bigint& b);
};
