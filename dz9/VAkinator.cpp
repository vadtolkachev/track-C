#include "VAkinator.hpp"


VAkinator::VAkinator(VTree *tree)
{
	m_tree = tree;
}


VTree *VAkinator::getTree() const
{
	return m_tree;
}


