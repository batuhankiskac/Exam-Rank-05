#pragma once

#include "searchable_bag.hpp"

class set {
private:
	searchable_bag* bag;
public:
	set(searchable_bag& s_bag);
	set(const set& src) = default;
	set& operator=(const set& src) = default;
	bool has(int v) const;
	void insert(int v);
	void insert(int* data, int size);
	void print() const;
	void clear();
	const searchable_bag& get_bag() const;
	~set() = default;
};
