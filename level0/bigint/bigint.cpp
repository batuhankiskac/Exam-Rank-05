#include "bigint.hpp"
#include <algorithm>
#include <cstdlib>

bigint::bigint() : str("0") {}

bigint::bigint(unsigned int num) {
	if (num == 0) {
		str = "0";
		return;
	}
	std::string tmp;
	while (num) {
		tmp.push_back((num % 10) + '0');
		num /= 10;
	}
	str.assign(tmp.rbegin(), tmp.rend());
}

bigint::bigint(const bigint& src) : str(src.str) {}

bigint& bigint::operator=(const bigint& src) {
	str = src.str;
	return *this;
}

bigint bigint::operator+(const bigint& o) const {
	std::string a = str, b = o.str;
	std::reverse(a.begin(), a.end());
	std::reverse(b.begin(), b.end());
	
	if (a.size() < b.size())
		a.append(b.size() - a.size(), '0');
	if (b.size() < a.size())
		b.append(a.size() - b.size(), '0');

	std::string res;
	int carry = 0;
	for (size_t i = 0; i < a.size(); i++) {
		int sum = (a[i] - '0') + (b[i] - '0') + carry;
		carry = sum / 10;
		res.push_back((sum % 10) + '0');
	}

	if (carry)
		res.push_back(carry + '0');

	std::reverse(res.begin(), res.end());

	bigint t;
	t.str = res;
	return t;
}

bigint& bigint::operator+=(const bigint& o) {
	return *this = *this + o;
}

bigint& bigint::operator++() {
	return *this = *this + bigint(1);
}

bigint bigint::operator++(int) {
	bigint tmp = *this;
	++(*this);
	return tmp;
}

bigint bigint::operator<<(unsigned int n) const {
	bigint t = *this;
	t.str.append(n, '0');
	return t;
}

bigint bigint::operator>>(unsigned int n) const {
	bigint t = *this;
	if (n >= t.str.size()) t.str = "0";
	else t.str.erase(t.str.size() - n);
	return t;
}

bigint& bigint::operator<<=(unsigned int n) {
	return *this = *this << n;
}

bigint& bigint::operator>>=(unsigned int n) {
	return *this = *this >> n;
}

bigint bigint::operator<<(const bigint& o) const {
	return *this << (unsigned)atoi(o.str.c_str());
}

bigint bigint::operator>>(const bigint& o) const {
	return *this >> (unsigned)atoi(o.str.c_str());
}

bigint& bigint::operator<<=(const bigint& o) {
	return *this = *this << o;
}

bigint& bigint::operator>>=(const bigint& o) {
	return *this = *this >> o;
}

bool bigint::operator==(const bigint& o) const {
	return str == o.str;
}

bool bigint::operator<(const bigint& o) const {
	if (str.size() != o.str.size())
		return str.size() < o.str.size();
	return str < o.str;
}

bool bigint::operator!=(const bigint& o) const {
	return !(*this == o);
}

bool bigint::operator>(const bigint& o) const {
	return o < *this;
}

bool bigint::operator<=(const bigint& o) const {
	return !(o < *this);
}

bool bigint::operator>=(const bigint& o) const {
	return !(*this < o);
}

std::ostream& operator<<(std::ostream& os, const bigint& b) {
	return os << b.str;
}
