#include "searchable_tree_bag.hpp"

bool searchable_tree_bag::has(int v) const {
	node *cur = tree;
	while (cur) {
		if (v == cur->value) return true;
		cur = (v < cur->value) ? cur->l : cur->r;
	}
	return false;
}
