#include "bigint.hpp"
#include <algorithm>

bigint::bigint() : str("0") {}

bigint::bigint(unsigned int num) : str(std::to_string(num)) {}

bigint bigint::operator+(const bigint& o) const {
	std::string res;
	int i = str.size() - 1;
	int j = o.str.size() - 1;
	int carry = 0;

	while (i >= 0 || j >= 0 || carry) {
		int sum = carry;
		if (i >= 0)
			sum += str[i--] - '0';
		if (j >= 0)
			sum += o.str[j--] - '0';
		carry = sum / 10;
		res.push_back((sum % 10) + '0');
	}
	std::reverse(res.begin(), res.end());
	bigint t;
	t.str = res;
	return t;
}

bigint& bigint::operator+=(const bigint& o) {
	return *this = *this + o;
}

bigint& bigint::operator++() {
	return *this += 1;
}

bigint bigint::operator++(int) {
	bigint tmp = *this;
	++(*this);
	return tmp;
}

bigint bigint::operator<<(unsigned int n) const {
	bigint t = *this;
	if (t.str != "0")
		t.str.append(n, '0');
	return t;
}

bigint bigint::operator>>(unsigned int n) const {
	bigint t = *this;
	if (n >= t.str.size())
		t.str = "0";
	else
		t.str.erase(t.str.size() - n);
	
	return t;
}

bigint& bigint::operator<<=(unsigned int n) {
	return *this = *this << n;
}

bigint& bigint::operator>>=(unsigned int n) {
	return *this = *this >> n;
}

bigint bigint::operator<<(const bigint& o) const {
	if (str == "0")
		return *this;
	return *this << o.to_uint();
}

bigint bigint::operator>>(const bigint& o) const {
	if (o >= bigint(str.size()))
		return bigint();
	return *this >> o.to_uint();
}

bigint& bigint::operator<<=(const bigint& o) {
	return *this = *this << o;
}

bigint& bigint::operator>>=(const bigint& o) {
	return *this = *this >> o;
}

unsigned int bigint::to_uint() const {
	unsigned int n = 0;
	for (size_t i = 0; i < str.size(); i++)
		n = n * 10 + str[i] - '0';
	return n;
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
