#pragma once
#include "VTree.hpp"


class VAkinator
{
public:
	VAkinator(VTree *tree);

	VTree *getTree() const;

private:
	VTree *m_tree;
};