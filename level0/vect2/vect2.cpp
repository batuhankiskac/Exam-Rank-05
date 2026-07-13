#include "vect2.hpp"

vect2::vect2() : x(0), y(0) { }

vect2::vect2(int nx, int ny) : x(nx), y(ny) { }

vect2::vect2(const vect2& src) : x(src.x), y(src.y) { }

vect2& vect2::operator=(const vect2& src) {
	x = src.x;
	y = src.y;
	return *this;
}

int vect2::operator[](int i) const {
	return i ? y : x;
}

int& vect2::operator[](int i) {
	return i ? y : x;
}

vect2 vect2::operator-() const {
	return vect2(-x, -y);
}

vect2 vect2::operator*(int n) const {
	return vect2(x * n, y * n);
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
	x -= o.x;
	y -= o.y;
	return *this;
}

vect2 vect2::operator+(const vect2& o) const {
	vect2 t = *this;
	return t += o;
}

vect2 vect2::operator-(const vect2& o) const {
	vect2 t = *this;
	return t -= o;
}

vect2& vect2::operator++() {
	++x;
	++y;
	return *this;
}

vect2 vect2::operator++(int) {
	vect2 t = *this;
	++(*this);
	return t;
}

vect2& vect2::operator--() {
	--x;
	--y;
	return *this;
}

vect2 vect2::operator--(int) {
	vect2 t = *this;
	--(*this);
	return t;
}

bool vect2::operator==(const vect2& o) const {
	return x == o.x && y == o.y;
}

bool vect2::operator!=(const vect2& o) const {
	return !(*this == o);
}

std::ostream& operator<<(std::ostream& os, const vect2& o) {
	return os << "{" << o[0] << ", " << o[1] << "}";
}

vect2 operator*(int n, const vect2& o) {
	return o * n;
}
