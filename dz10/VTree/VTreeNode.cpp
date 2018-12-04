#include "VTreeNode.hpp"


VTreeNode::VTreeNode()
{
	m_left = nullptr;
	m_right = nullptr;
	m_type = VNumb;
	m_data = 0;
}


VType VTreeNode::getType() const
{
	return m_type;
}


double VTreeNode::getDouble() const
{
	return m_data;
}


char VTreeNode::getChar() const
{
	return *((char *)(&m_data));
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


int VTreeNode::setChar(const char &c)
{
	if((c == '+') || (c == '-') || (c == '*') || (c == '/'))
	{
		m_type = VSign;
		*((char *)(&m_data)) = c;
		return SUCCESS;
	}
	else if((c >= 'a') && (c <= 'z'))
	{
		m_type = VVar;
		*((char *)(&m_data)) = c;
		return SUCCESS;
	}
	else
		return TYPE_ERR;
}


void VTreeNode::setDouble(const double &numb)
{
	m_data = numb;
	m_type = VNumb;
}

