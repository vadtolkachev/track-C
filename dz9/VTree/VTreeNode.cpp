#include "VTreeNode.hpp"


VTreeNode::VTreeNode()
{
	m_str = nullptr;
	m_left = nullptr;
	m_right = nullptr;
}


VTreeNode::~VTreeNode()
{
	if(m_str)
		delete[] m_str;
}


char *VTreeNode::getStr() const
{
	return m_str;
}


VTreeNode *VTreeNode::getLeft() const
{
	return m_left;
}


VTreeNode *VTreeNode::getRight() const
{
	return m_right;
}


int VTreeNode::createLeft()
{
	if(m_left)
		return OVERFLOW_ERR;

	m_left = new (std::nothrow) VTreeNode();
	
	if(!m_left)
		return ALLOC_ERR;

	return SUCCESS;
}


int VTreeNode::createRight()
{
	if(m_right)
		return OVERFLOW_ERR;

	m_right = new (std::nothrow) VTreeNode();
	
	if(!m_right)
		return ALLOC_ERR;

	return SUCCESS;
}


int VTreeNode::setStr(const char *str)
{
	if(m_str)
		delete[] m_str;

	m_str = new (std::nothrow) char[strlen(str)+1]();
	
	if(!m_str)
		return ALLOC_ERR;

	strcpy(m_str, str);

	return SUCCESS;
}

