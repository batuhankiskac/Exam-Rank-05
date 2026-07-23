#include "vect2.hpp"

int vect2::operator[](int i) const {
	return (i == 0) ? x : y;
}

int& vect2::operator[](int i) {
	return (i == 0) ? x : y;
}

vect2 vect2::operator+(const vect2& other) const {
	return vect2(x + other.x, y + other.y);
}

vect2 vect2::operator-(const vect2& other) const {
	return vect2(x - other.x, y - other.y);
}

vect2 vect2::operator-() const {
	return vect2(-x, -y);
}

vect2 vect2::operator*(int scalar) const {
	return vect2(x * scalar, y * scalar);
}

vect2& vect2::operator+=(const vect2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

vect2& vect2::operator-=(const vect2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

vect2& vect2::operator*=(int scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

vect2& vect2::operator++() {
	++x;
	++y;
	return *this;
}

vect2 vect2::operator++(int) {
	vect2 temp(*this);
	++(*this);
	return temp;
}

vect2& vect2::operator--() {
	--x;
	--y;
	return *this;
}

vect2 vect2::operator--(int) {
	vect2 temp(*this);
	--(*this);
	return temp;
}

bool vect2::operator==(const vect2& other) const {
	return (x == other.x && y == other.y);
}

bool vect2::operator!=(const vect2& other) const {
	return !(*this == other);
}

vect2 operator*(int scalar, const vect2& v) {
	return v * scalar;
}

std::ostream& operator<<(std::ostream& os, const vect2& v) {
	os << "{" << v[0] << ", " << v[1] << "}";
	return os;
}
