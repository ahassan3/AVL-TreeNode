// Aimen Hassan
// 10/21/2015
// CS-361 Algorithims and Data Structures

#include <iostream>
#include <cassert>

using std::cerr;
using std::endl;

#define private public
#include "AVLTree.h"
#define DAssert(condition) do { if (!(condition)) { cerr << "DAssert failed: " << __FUNCTION__ << " : line " << __LINE__ << endl; }} while(0)


void test_left_single_rotate()
{
	AVLTree<int> t;
	t.insert(3);
	t.insert(2);
	t.insert(1);
	assert(t.root_->item_ == 2);
	assert(t.root_->left_->item_ == 1);
	assert(t.root_->right_->item_ == 3);
}
void test_copy() {
	AVLTree<double> t;
	t.insert(5.5);
	t.insert(5.6);
	t.insert(5.9);
	AVLTree<double> f(t);
	assert(f.root_->item_ == 5.6);
	assert(f.root_->left_->item_ == 5.5);
	assert(f.root_->right_->item_ == 5.9);
}
void test_left_right_rotate() {
	AVLTree<int> t;
	t.insert(10);
	t.insert(5);
	t.insert(20);
	t.insert(7);
	t.insert(6);
	assert(t.root_->item_ == 10);
	assert(t.root_->left_->item_ == 6);
	assert(t.root_->left_->right_->item_ == 7);
}
void test_right_left_rotate() {
	AVLTree<int> t;
	t.insert(10);
	t.insert(5);
	t.insert(20);
	t.insert(3);
	t.insert(4);
	assert(t.root_->item_ == 10);
	assert(t.root_->left_->item_ == 4);
	assert(t.root_->left_->right_->item_ == 5);
}
void test_inorder() {
	AVLTree<int> t;
	t.insert(10);
	t.insert(5);
	t.insert(20);
	t.insert(3);
	t.insert(4);
	t.printInorder();
}
void test_preorder() {
	AVLTree<int> t;
	t.insert(10);
	t.insert(5);
	t.insert(20);
	t.insert(3);
	t.insert(4);
	t.printPreorder();
}
void test_postorder() {
	AVLTree<int> t;
	t.insert(10);
	t.insert(5);
	t.insert(20);
	t.insert(3);
	t.insert(4);
	t.printPostorder();
}
void test_destructor() {
	AVLTree<int> t;
	t.insert(10);
	t.insert(5);
	t.insert(20);
	t.insert(3);
	t.insert(4);
	t.~AVLTree();
	AVLTree<int> x;
	x.~AVLTree();
	assert(x.root_ == NULL);
	assert(t.root_ == NULL);
	assert(t.size() == 0);
}
void test_find() {
	AVLTree<int> t;
	t.insert(10);
	t.insert(5);
	t.insert(20);
	t.insert(3);
	t.insert(4);
	assert(t.find(20)->item_ == 20);
	assert(t.find(200) == NULL);
	assert(t.find(10)->item_ == 10);
	AVLTree<double> x;
	x.insert(7.4);
	assert(x.find(7.4)->item_ == 7.4);
	assert(x.find(10.2) == NULL);
}
void test_operator() {
	AVLTree<int> t;
	t.insert(10);
	t.insert(5);
	t.insert(20);
	t.insert(3);
	t.insert(4);
	AVLTree<int> x;
	x.insert(10);
	x = t;
	AVLTree<int> d;
	d = x;
	assert(x.root_->right_->item_ == 20);
	assert(d.root_->right_->item_ == 20);
}
int main() {
	test_left_single_rotate();
	test_copy();
	test_left_right_rotate();
	test_right_left_rotate();
	test_inorder();
	test_preorder();
	test_postorder();
	test_destructor();
	test_find();
	test_operator();
	return 0;
}
