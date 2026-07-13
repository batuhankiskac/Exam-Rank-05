#include "set.hpp"

set::set(searchable_bag& s_bag) : bag(s_bag) {}

bool set::has(int v) const { return bag.has(v); }

void set::insert(int v) { if (!has(v)) bag.insert(v); }

void set::insert(int* data, int size)
{
	for (int i = 0; i < size; i++) insert(data[i]);
}

void set::print() const { bag.print(); }
void set::clear() { bag.clear(); }
const searchable_bag& set::get_bag() const { return bag; }
set::~set() {}
