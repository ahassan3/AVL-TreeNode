/*
*  AVLTree.h
*  AVLTreeTemplate
*
*  Aimen Hassan 
*  10/19/2015
*
*/

#ifndef __AVLTREE_H__
#define __AVLTREE_H__

//--------------------------------------------------------------------

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <algorithm>

#include "BinaryTreeNode.h"

//--------------------------------------------------------------------

template <typename Item>
class AVLTree {

public:
	/*! constructor
	*/
	AVLTree();

	/*! destructor
	*/
	~AVLTree();

	/*! copy constructor
	* \param source AVLTree to copy
	*/
	AVLTree(const AVLTree &source);

	/*! assignment operator
	* \param source object to copy
	* \returns *this which is now a copy of src
	*/
	AVLTree& operator=(const AVLTree &source);

	/*! insert item into tree
	* \param item value to insert
	* \pre item is not already in the tree
	* \post item is inserted into tree and tree is balanced according to AVL rules
	*/
	void insert(const Item item);

	/*! search for item in tree
	* \param item value to search for
	* \returns BinaryTreeNode containing item or NULL if not item not found
	*/
	BinaryTreeNode<Item>* find(const Item item);

	/*! print items (one item per line) tree using inorder traversal;
	* \pre items in tree must support operator<<
	* \post items are output to stdout one per line in postorder order
	*/
	void printInorder();

	/*! print items (one item per line) tree using preorder traversal;
	* \pre items in tree must support operator<<
	* \post items are output to stdout one per line in postorder order
	*/
	void printPreorder();

	/*! print items (one item per line) tree using postorder traversal;
	* \pre items in tree must support operator<<
	* \post items are output to stdout one per line in postorder order
	*/
	void printPostorder();

	/*! returns number of items in tree
	* \returns number of items in tree
	*/
	int size() const { return size_; }

private:
	/*! recursively makes a copy of the subtree rooted at node
	* \param node root of the subtree to copy
	* \post a deep copy of the entire subtree rooted at node is created
	* \returns the root BinaryTreeNode of a deepcopy of the subtree rooted at node
	*/
	BinaryTreeNode<Item>* copy(const BinaryTreeNode<Item> *node);


	/*! search for item in subtree rooted at node
	* \param node BinaryTreeNode root of subtree to search in
	* \param item value to search for
	* \returns BinaryTreeNode containing item or NULL if item not found
	*/
	BinaryTreeNode<Item>* findHelp(BinaryTreeNode<Item> *node, const Item item);


	/*! deallocates entire subtree rooted at node
	* \param root of subtree to deallocate
	* \post entire subtree at node is deallocated and node is set to NULL
	*/
	void dealloc(BinaryTreeNode<Item> *&node);

	/*! insert item into subtree with root node
	* \param node BinaryTreeNode root of tree to insert into
	* \param item value to insert
	* \pre item is not already in the tree
	* \post item is inserted into tree and tree is balanced according to AVL rules
	*/
	void insertHelp(BinaryTreeNode<Item> *&node, Item item);

	/*! print items (one item per line) in subtree rooted at node using inorder traversal;
	* \pre items in tree must support operator<<
	* \post items in subtree are output to stdout one per line in postorder order
	*/
	void printInorderHelp(BinaryTreeNode<Item> *node);

	/*! print items (one item per line) in subtree rooted at node using preorder traversal;
	* \pre items in tree must support operator<<
	* \post items in subtree are output to stdout one per line in postorder order
	*/
	void printPreorderHelp(BinaryTreeNode<Item> *node);

	/*! print items (one item per line) in subtree rooted at node using postorder traversal;
	* \pre items in tree must support operator<<
	* \post items in subtree are output to stdout one per line in postorder order
	*/
	void printPostorderHelp(BinaryTreeNode<Item> *node);

	/*! rebalances tree when node's left subtree has height two more than its right subtree and insertion was made into left subtree of left child of node by performing a clockwise rotation
	* \param node root of subtree that needs rebalanced and only one insertion has been performed since tree was balanced
	* \pre node is deepest node whose left subtree has height two more than its right subtree and only one insertion has been performed since tree was balanced
	* \post tree is rebalanced
	*/
	void leftSingleRotate(BinaryTreeNode<Item> *&node);

	/*! rebalances tree when node's right subtree has height two more than its left subtree and insertion was made into right subtree of right child of node by performing a counter-clockwise rotation
	* \param node root of subtree that needs rebalanced
	* \pre node is deepest node whose right subtree has height two more than its left subtree and only one insertion has been performed since tree was balanced
	* \post tree is rebalanced
	*/
	void rightSingleRotate(BinaryTreeNode<Item> *&node);

	/*! rebalances tree when node's left subtree has height two more than its right subtree and insertion was made into right subtree of left child of node by performing two rotations
	* \param node root of subtree that needs rebalanced
	* \pre node is deepest node whose left subtree has height two more than its right subtree
	* \post tree is rebalanced
	*/
	void rightLeftRotate(BinaryTreeNode<Item> *&node);

	/*! rebalances tree when node's right subtree has height two more than its left subtree and insertion was made into left subtree of right child of node by performing two rotations
	* \param node root of subtree that needs rebalanced
	* \pre node is deepest node whose right subtree has height two more than its left subtree and only one insertion has been performed since tree was balanced
	* \post tree is rebalanced
	*/
	void leftRightRotate(BinaryTreeNode<Item> *&node);

	// pointer to root node of tree
	BinaryTreeNode<Item> *root_;
	// number of items in the tree
	int size_;
};

//--------------------------------------------------------------------
template<typename Item>
AVLTree<Item>::AVLTree() {
	// intialize the instance variables
	root_ = NULL;
	size_ = 0;
}
//-------------------------------------------------------
template<typename Item>
AVLTree<Item>::~AVLTree() {
	// call delloc method
	dealloc(root_);
	// reset instance variables
	root_ = NULL;
	size_ = 0;
}
//---------------------------------------
template<typename Item>
void AVLTree<Item>::insert(const Item item) {
	// call helper function
	insertHelp(root_, item); 
}
template<typename Item>
void AVLTree<Item>::insertHelp(BinaryTreeNode<Item> *&node, Item item) {
	// if the node equals null
	if (node == NULL) {
		// create new tree node
		node = new BinaryTreeNode<Item>(item);
		// increment size
		size_++;
	}
	// if item is less than item at node
	else if (item < node->item_) {
		// recursively call the inserthelp method
		insertHelp(node->left_, item);
		// if the height of the left minus the right equals two, then do a rotation
		if ((getHeight(node->left_) - getHeight(node->right_)) == 2) {
			// if item is less than the item of teh left node
			if (item < node->left_->item_) {
				// call the left single rotate method
				leftSingleRotate(node);
			}
			else {
				// call the right left rotate method
				rightLeftRotate(node);
			}
		}
	}
	else {
		// recursively call the inserthelp method
		insertHelp(node->right_, item);
		// if the hegiht of the right minus the height of the left equals two then do a rotation
		if ((getHeight(node->right_) - getHeight(node->left_)) == 2) {
			// if the item is greater than the item of the right node, do a right singel rotation
			if (item > node->right_->item_) {
				rightSingleRotate(node);
			}
			// otherwise do a left right rotate
			else {
				leftRightRotate(node);
			}
		}
	}
	// if the height of the right subtree is greater than the left
	if (getHeight(node->right_) > getHeight(node->left_)) {
		node->height_ = getHeight(node->right_) + 1;
	}
	else {
		// otherwise give the height is set to the other subtree
		node->height_ = getHeight(node->left_) + 1;
	}
}
template<typename Item>
void AVLTree<Item>::rightLeftRotate(BinaryTreeNode<Item> *&node){
	// call the right rotata on the left node
	rightSingleRotate(node->left_);
	// call the left single rotate on the node
	leftSingleRotate(node);
}
template<typename Item>
void AVLTree<Item>::leftSingleRotate(BinaryTreeNode<Item> *&node) {
	// make a variable hold the root to be adjusted
	BinaryTreeNode<Item> *grandparent = node;
	// make another variable hold the left of the root 
	BinaryTreeNode<Item> *parent = node->left_;
	// the root's left is set to the root's left right
	grandparent->left_ = parent->right_;
	// the roots left right is set to the root
	parent->right_ = grandparent;
	// the node is set to the parent
	node = parent;
	// if the height of the grandparent's left is greater the right then the grandparent's height is set to the longer subtree
	if (getHeight(grandparent->left_) > getHeight(grandparent->right_)) {
		// add one in the end
		grandparent->height_ = getHeight(grandparent->left_) + 1;
	}
	else {
		// otherwise the height of the grandparent is set to the 
		grandparent->height_ = getHeight(grandparent->right_) + 1;
	}
	// set the height of the parent to the longer subtree
	if (getHeight(parent->left_) > getHeight(parent->right_)) {
		// add one at the end
		parent->height_ = getHeight(parent->left_) + 1;
	}
	else {
		// otherwise the parent's height is set to other 
		parent->height_ = getHeight(parent->right_) + 1;
	}
}
template<typename Item>
void AVLTree<Item>::rightSingleRotate(BinaryTreeNode<Item> *&node) {
	// make a variable hold the root to be adjusted
	BinaryTreeNode<Item> *grandparent = node;
	// the parent is set to the root's right 
	BinaryTreeNode<Item> *parent = node->right_;
	// the grandparent's right is set to the parent's left
	grandparent->right_ = parent->left_;
	// the parent's left is the root
	parent->left_ = grandparent;
	// node equals the parent
	node = parent;
	// set the height of the grand parent
	if (getHeight(grandparent->left_) > getHeight(grandparent->right_)) {
		grandparent->height_ = getHeight(grandparent->left_) + 1;
	}
	else {
		grandparent->height_ = getHeight(grandparent->right_) + 1;
	}
	// set the height of the parent
	if (getHeight(parent->left_) > getHeight(parent->right_)) {
		parent->height_ = getHeight(parent->left_) + 1;
	}
	else {
		parent->height_ = getHeight(parent->right_) + 1;
	}
}
//-----------------------------------
template<typename Item>
void AVLTree<Item>::leftRightRotate(BinaryTreeNode<Item> *&node) {
	// call the left single rotate on root's right node
	leftSingleRotate(node->right_);
	// call the right single rotate on the root
	rightSingleRotate(node);
}
template<typename Item>
BinaryTreeNode<Item>* AVLTree<Item>::find(const Item item) {
	// call the find help method
	BinaryTreeNode<Item> *node = findHelp(root_, item);
	return node;
}
template<typename Item>
BinaryTreeNode<Item>* AVLTree<Item>::findHelp(BinaryTreeNode<Item>*node, const Item item) {
	// if the node is null return null
	if (node == NULL) {
		return node;
	}
	// if the item is greater than the node's 
	else if (item > node->item_) {
		// recursively call the right node
		node = findHelp(node->right_, item);
	}
	// if the item is less than the node
	else if (item < node->item_) {
		//recursively call the left node
		node = findHelp(node->left_, item);
	}
	return node;
}
//---------------------------
template<typename Item>
AVLTree<Item>::AVLTree(const AVLTree &source) {
	// call the copy method to return the root of the deep copied tree
	root_ = copy(source.root_);
	// set the size to be the same as the source's
	size_ = source.size_;
}
//-------------------------------
template<typename Item>
BinaryTreeNode<Item>* AVLTree<Item>::copy(const BinaryTreeNode<Item> *node) {
	// create new node
	BinaryTreeNode<Item> *newNode;
	// if the node is null return null
	if (node == NULL) {
		newNode = NULL;
		return newNode;
	}
	else {
		// create new node given certain item
		newNode = new BinaryTreeNode<Item>(node->item_);
		// set the heigth of that newnode to node's height
		newNode->height_ = node->height_;
		// recursively call the copy method on the root's right
		newNode->right_ = copy(node->right_);
		// recursively call the copy method on the root's left
		newNode->left_ = copy(node->left_);
	}
	return newNode;
}
//-------------------------------
template<typename Item>
void AVLTree<Item>::dealloc(BinaryTreeNode<Item> *&node) {
	// if node doesnt equal null
	if (node != NULL) {
		// recursively call the dealloc method on the root's right
		dealloc(node->right_);
		// recursively call the dealloc method on the root's left
		dealloc(node->left_);
		// delete the node
		delete node;
	}
}
//-----------------------
template<typename Item>
AVLTree<Item>& AVLTree<Item>::operator=(const AVLTree &source) {
	// if the current tree desnt equal the source
	if (this != &source) {
		// call dealloc on root
		dealloc(root_);
		// call the copy method on the root
		root_ = copy(source.root_);
		// set the size equal to the sources's size
		size_ = source.size_;
	}
	return *this;
}
//----------------------
template<typename Item>
void AVLTree<Item>::printInorder() {
	// call the print inorder method
	printInorderHelp(root_);
}
//----------------------
template<typename Item>
void AVLTree<Item>::printInorderHelp(BinaryTreeNode<Item> *node) {
	// if node deosnt equal null
	if (node != NULL) {
		// recusively call it on the right node of the root
		printInorderHelp(node->left_);
		// print item
		std::cout << node->item_ << endl;
		// recusively call it on the left node of the root
		printInorderHelp(node->right_);
	}
}
template<typename Item>
void AVLTree<Item>::printPreorder() {
	// call preorder help
	printPreorderHelp(root_);
}
//------------------------------------
template<typename Item>
void AVLTree<Item>::printPreorderHelp(BinaryTreeNode<Item> *node) {
	// if node deosnt equal null
	if (node != NULL) {
		//print root
		std::cout << node->item_ << endl;
		// recusively call it on the left node of the root
		printPreorderHelp(node->left_);
		// recusively call it on the right node of the root
		printPreorderHelp(node->right_); 
	} 
}
//---------------------------
template<typename Item>
void AVLTree<Item>::printPostorder() {
	// call the post order method
	printPostorderHelp(root_);
}
//------------------------------------------------
template<typename Item>
void AVLTree<Item>::printPostorderHelp(BinaryTreeNode<Item> *node) {
	// if node deosnt equal NULL
	if (node != NULL) {
		// recusively call it on the left node of the root
		printPostorderHelp(node->left_);
		// recusively call it on the right node of the root
		printPostorderHelp(node->right_);
		// print item
		std::cout << node->item_ << endl;
	}
}



#endif // __AVLTREE_H__


