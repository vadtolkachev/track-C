#pragma once


class VTTreeNode
{
public:
	VTTreeNode(const int &numb);
	
	int getNumb() const;
	VTTreeNode *getLeft() const;
	VTTreeNode *getRight() const;	
	
	void setLeft(VTTreeNode *left);
	void setRight(VTTreeNode *right);

private:
	int m_numb;
	VTTreeNode *m_left;
	VTTreeNode *m_right;
};