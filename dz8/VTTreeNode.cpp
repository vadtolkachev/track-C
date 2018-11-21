#include "VTTreeNode.hpp"


VTTreeNode::VTTreeNode(const int &numb)
{
	m_numb = numb;
	m_left = nullptr;
	m_right = nullptr;
}

	
int VTTreeNode::getNumb() const
{
	return m_numb;
}


VTTreeNode *VTTreeNode::VTTreeNode::getLeft() const
{
	return m_left;
}


VTTreeNode *VTTreeNode::getRight() const
{
	return m_right;
}


void VTTreeNode::setLeft(VTTreeNode *left)
{
	m_left = left;
}


void VTTreeNode::setRight(VTTreeNode *right)
{
	m_right = right;
}
