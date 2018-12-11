#include "VTreeNode.hpp"


VTreeNode::VTreeNode()
{
	m_left = nullptr;
	m_right = nullptr;
	m_type = VNumbType;
	m_data = 0;
}


VType VTreeNode::getType() const
{
	return m_type;
}


VTreeNode *VTreeNode::getLeft() const
{
	return m_left;
}


VTreeNode *VTreeNode::getRight() const
{
	return m_right;
}


double VTreeNode::getDouble() const
{
	return m_data;
}


char VTreeNode::getChar() const
{
	return *((char *)(&m_data));
}


VFunc VTreeNode::getFunc() const
{
	return *((VFunc *)(&m_data));
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
	if((c >= 'a') && (c <= 'z'))
	{
		m_type = VVarType;
		*((char *)(&m_data)) = c;
		return SUCCESS;
	}
	else
		return TYPE_ERR;
}


int VTreeNode::fprintData(FILE *file) const
{
	if(!file)
		return NULLPTR_ERR;

	if(m_type == VNumbType)
		fprintf(file, "%lg", m_data);
	else if(m_type == VVarType)
		fprintf(file, "%c", *((char *)(&m_data)));
	else
	{
		#define FUNC_DEF(name, str, numb, der_code)	\
		if(getFunc() == numb)				\
			fprintf(file, "%s", #str);

		FUNCS_DEF;

		#undef FUNC_DEF
	}

	return SUCCESS;
}


int VTreeNode::fprintType(FILE *file) const
{
	if(!file)
		return NULLPTR_ERR;

	if(m_type == VNumbType)
		fprintf(file, "VNumbType");
	else if(m_type == VVarType)
		fprintf(file, "VVarType");
	else
		fprintf(file, "VFuncType");

	return SUCCESS;
}


int VTreeNode::copy(VTreeNode *node)
{
	if(!node)
		return NULLPTR_ERR;


	int checkErr = copyNode(node, this);
	return checkErr;
}


int VTreeNode::copyNode(VTreeNode *nodeFrom, VTreeNode *nodeTo)
{
	int checkErr;

	VType type = nodeFrom->getType();

	if(type == VFuncType)
		nodeTo->setFunc(nodeFrom->getFunc());

	if(type == VVarType)
		nodeTo->setChar(nodeFrom->getChar());

	if(type == VNumbType)
		nodeTo->setDouble(nodeFrom->getDouble());

	if(nodeFrom->getLeft())
	{
		checkErr = nodeTo->createLeft();
		CHECKERR();
		checkErr = copyNode(nodeFrom->getLeft(), nodeTo->getLeft());
		CHECKERR();
	}

	if(nodeFrom->getRight())
	{
		checkErr = nodeTo->createRight();
		CHECKERR();
		checkErr = copyNode(nodeFrom->getRight(), nodeTo->getRight());
		CHECKERR();
	}


	return SUCCESS;
}


void VTreeNode::setFunc(VFunc func)
{
	m_type = VFuncType;
	*((VFunc *)(&m_data)) = func;
}


void VTreeNode::setDouble(const double &numb)
{
	m_data = numb;
	m_type = VNumbType;
}

