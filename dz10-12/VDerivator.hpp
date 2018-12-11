#include "VTree.hpp"


class VDerivator
{
public:
	VTree *getTree() const;

	void setTree(VTree *tree);

private:
	VTree *m_tree;
};