#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() {}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& src) : tree_bag(src) {}
searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& src)
{
	tree_bag::operator=(src);
	return *this;
}
searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::has(int v) const
{
	node *cur = tree;
	while (cur)
	{
		if (v == cur->value) return true;
		cur = (v < cur->value) ? cur->l : cur->r;
	}
	return false;
}
