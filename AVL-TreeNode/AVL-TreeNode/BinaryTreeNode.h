/*
*  BinaryTreeNode.h
*  AVLTreeTemplate
*
*  Aimen Hassan
*  10/20/2015
*  CS-361
*/

#ifndef __BINARYTREENODE_H__
#define __BINARYTREENODE_H__

//--------------------------------------------------------------------

#include <cstdlib>

//--------------------------------------------------------------------

template <typename Item>
class BinaryTreeNode {

	template<typename Item> friend class AVLTree;
	template <typename Item> friend int getHeight(BinaryTreeNode<Item> *node);

public:
	BinaryTreeNode(Item item, BinaryTreeNode<Item> *left = NULL,
		BinaryTreeNode<Item> *right = NULL);

	int height() { return height_; }
	void setHeight(int height) { height_ = height; }

private:
	Item item_;
	BinaryTreeNode<Item> *left_, *right_;
	int height_;
};

//--------------------------------------------------------------------

template <typename Item>
BinaryTreeNode<Item>::BinaryTreeNode(Item item,
	BinaryTreeNode<Item> *left,
	BinaryTreeNode<Item> *right)
{
	item_ = item;
	left_ = left;
	right_ = right;
}

//--------------------------------------------------------------------

template <typename Item>
int getHeight(BinaryTreeNode<Item> *node)
{
	if (!node)
		return -1;
	else
		return node->height();
}

//--------------------------------------------------------------------

#endif // __BINARYTREENODE_H__


