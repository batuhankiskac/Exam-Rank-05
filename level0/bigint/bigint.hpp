#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>

class bigint
{
private:
	std::string str;
	unsigned int to_uint() const;

public:
	bigint();
	bigint(unsigned int num);
	bigint(const bigint& src) = default;
	bigint& operator=(const bigint& src) = default;

	bigint operator+(const bigint& o) const;
	bigint& operator+=(const bigint& o);
	bigint& operator++();
	bigint operator++(int);

	bigint operator<<(unsigned int n) const;
	bigint operator>>(unsigned int n) const;
	bigint& operator<<=(unsigned int n);
	bigint& operator>>=(unsigned int n);

	bigint operator<<(const bigint& o) const;
	bigint operator>>(const bigint& o) const;
	bigint& operator<<=(const bigint& o);
	bigint& operator>>=(const bigint& o);

	bool operator==(const bigint& o) const;
	bool operator<(const bigint& o) const;
	bool operator!=(const bigint& o) const;
	bool operator>(const bigint& o) const;
	bool operator<=(const bigint& o) const;
	bool operator>=(const bigint& o) const;

	friend std::ostream& operator<<(std::ostream& os, const bigint& b);
};

#endif
