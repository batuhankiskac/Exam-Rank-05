#include "vect2.hpp"

vect2& vect2::operator=(const vect2& other) {
	x = other.x;
	y = other.y;
	return *this;
}

int vect2::operator[](int i) const {
	return i == 0 ? x : y;
}

int& vect2::operator[](int i) {
	return i == 0 ? x : y;
}

vect2 vect2::operator-() const {
	return vect2(-x, -y);
}

vect2& vect2::operator*=(int n) {
	x *= n;
	y *= n;
	return *this;
}

vect2& vect2::operator+=(const vect2& o) {
	x += o.x;
	y += o.y;
	return *this;
}

vect2& vect2::operator-=(const vect2& o) {
	return *this += -o;
}

vect2 vect2::operator*(int n) const {
	return vect2(x * n, y * n);
}

vect2 vect2::operator+(const vect2& o) const {
	vect2 tmp(*this);
	return tmp += o;
}

vect2 vect2::operator-(const vect2& o) const {
	vect2 tmp(*this);
	return tmp -= o;
}

vect2& vect2::operator++() {
	++x;
	++y;
	return *this;
}

vect2 vect2::operator++(int) {
	vect2 tmp(*this);
	++(*this);
	return tmp;
}

vect2& vect2::operator--() {
	return *this += vect2(-1, -1);
}

vect2 vect2::operator--(int) {
	vect2 tmp(*this);
	--(*this);
	return tmp;
}

bool vect2::operator==(const vect2& o) const {
	return x == o.x && y == o.y;
}

bool vect2::operator!=(const vect2& o) const {
	return !(*this == o);
}

vect2 operator*(int n, const vect2& o) {
	return o * n;
}

std::ostream& operator<<(std::ostream& os, const vect2& o) {
	os << "{" << o[0] << ", " << o[1] << "}";
	return os;
}
