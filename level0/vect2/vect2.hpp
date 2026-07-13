#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2 {
private:
	int x;
	int y;

public:
	// Kurucular ve Atama
	vect2(int x = 0, int y = 0) : x(x), y(y) { }
	vect2(const vect2& other) : x(other.x), y(other.y) { };
	vect2& operator=(const vect2& other);

	// Eleman Erişimi
	int operator[](int i) const;
	int& operator[](int i);

	// Unary (Tekli) Operatör
	vect2 operator-() const;

	// Matematiksel ve Atama Operatörleri
	vect2& operator*=(int n);
	vect2& operator+=(const vect2& o);
	vect2& operator-=(const vect2& o);

	vect2 operator*(int n) const;
	vect2 operator+(const vect2& o) const;
	vect2 operator-(const vect2& o) const;

	// Artırma ve Azaltma Operatörleri
	vect2& operator++();
	vect2 operator++(int);
	vect2& operator--();
	vect2 operator--(int);

	// Karşılaştırma
	bool operator==(const vect2& o) const;
	bool operator!=(const vect2& o) const;
};

// Sınıf Dışı (Global) Operatörler
vect2 operator*(int n, const vect2& o);
std::ostream& operator<<(std::ostream& os, const vect2& o);

#endif
