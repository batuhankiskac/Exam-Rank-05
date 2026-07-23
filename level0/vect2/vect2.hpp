#pragma once

#include <iostream>
#include <string>

class vect2 {
private:
	int x;
	int y;
public:
	vect2(int x = 0, int y = 0) : x(x), y(y) {}

	int operator[](int i) const;
	int& operator[](int i);

	vect2 operator+(const vect2& other) const;
	vect2 operator-(const vect2& other) const;
	vect2 operator-() const;
	vect2 operator*(int scalar) const;

	vect2& operator+=(const vect2& other);
	vect2& operator-=(const vect2& other);
	vect2& operator*=(int scalar);

	vect2& operator++();
	vect2 operator++(int);
	vect2& operator--();
	vect2 operator--(int);

	bool operator==(const vect2& other) const;
	bool operator!=(const vect2& other) const;
};

std::ostream& operator<<(std::ostream& os, const vect2& v);
vect2 operator*(int scalar, const vect2& v);
