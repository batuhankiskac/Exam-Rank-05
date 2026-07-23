#include "bigint.hpp"

bigint::bigint() : str("0") {}

bigint::bigint(unsigned int num) : str(std::to_string(num)) {}

bigint bigint::operator+(const bigint& other) const {
	std::string result;
	int i = str.size() - 1;
	int j = other.str.size() - 1;
	int carry = 0;

	while (i >= 0 || j >= 0 || carry) {
		int sum = carry;
		if (i >= 0)
			sum += str[i--] - '0';
		if (j >= 0)
			sum += other.str[j--] - '0';
		carry = sum / 10;
		result.push_back(sum % 10 + '0');
	}
	std::reverse(result.begin(), result.end());
	bigint t;
	t.str = result;
	return t;
}

bigint& bigint::operator+=(const bigint& other) {
	return *this = *this + other;
}

bigint& bigint::operator++() {
	return *this += 1;
}

bigint bigint::operator++(int) {
	bigint temp = *this;
	++(*this);
	return temp;
}

bigint bigint::operator<<(unsigned int num) const {
	bigint t = *this;
	if (t.str != "0")
		t.str.append(num, '0');
	return t;
}

bigint bigint::operator>>(unsigned int num) const {
	bigint t = *this;
	if (num >= t.str.size())
		t.str = "0";
	else
		t.str.erase(t.str.size() - num);
	return t;
}

bigint& bigint::operator<<=(unsigned int num) {
	return *this = *this << num;
}

bigint& bigint::operator>>=(unsigned int num) {
	return *this = *this >> num;
}

unsigned int bigint::to_uint() const {
	unsigned int result = 0;
	for (char c : str)
		result = result * 10 + (c - '0');
	return result;
}

bigint bigint::operator<<(const bigint& other) const {
	return *this << other.to_uint();
}

bigint bigint::operator>>(const bigint& other) const {
	return *this >> other.to_uint();
}

bigint& bigint::operator<<=(const bigint& other) {
	return *this = *this << other;
}

bigint& bigint::operator>>=(const bigint& other) {
	return *this = *this >> other;
}

bool bigint::operator==(const bigint& other) const {
	return str == other.str;
}

bool bigint::operator!=(const bigint& other) const {
	return !(*this == other);
}

bool bigint::operator<(const bigint& other) const {
	if (str.size() != other.str.size())
		return str.size() < other.str.size();
	return str < other.str;
}

bool bigint::operator>(const bigint& other) const {
	return other < *this;
}

bool bigint::operator<=(const bigint& other) const {
	return !(*this > other);
}

bool bigint::operator>=(const bigint& other) const {
	return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const bigint& b) {
	os << b.str;
	return os;
}
