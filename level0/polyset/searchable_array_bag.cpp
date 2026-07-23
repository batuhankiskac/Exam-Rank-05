#include "searchable_array_bag.hpp"

bool searchable_array_bag::has(int v) const {
	for (int i = 0; i < size; i++) {
		if (data[i] == v)
			return true;
	}
	return false;
}
