// =====================================================================================
// 
//       Filename:  BinaryTree.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年09月09日 17时45分58秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include "BTNode.h"

template <class T>

class BinaryTree{
	public:
		BinaryTree(){
			root = NULL;
		}
		~BinaryTree();
		void Clear();
		bool Root(T &x) const;
		void MakeTree(const T &x, BinaryTree<T> &left, BinaryTree<T> &right);
		void BreakTree(T &x, BinaryTree<T> &left, BinaryTree<T> &right);
		void PreOrder(void (*visit)(T &x));
		void InOrder(void (*visit)(T & x));
		void PostOrder(void (*visit)(T &x));
	protected:
		BTNode<T> *root;
	private:
		void Clear(BTNode<T> *& t);
		void PreOrder(void (*visit)(T &x), BTNode<T> *t);
		void InOrder(void (*visit) (T &x), BTNode<T> *t);
		void PostOrder(void (*visit)(T &x), BTNode<T> *t);
};

template <class T>
bool BinaryTree<T> ::Root(T &x) const{
	if (root){
		x = root->element;

		return true;
	}
	return false;
}

template <class T>
void BinaryTree<T> ::MakeTree(const T &x, BinaryTree<T> &left, BinaryTree<T> &right){
	if (root || &right == &left){
		return;
	}
	root = new BTNode<T>(x, left.root, right.root);
	left.root = right.root = NULL;
}

template <class T>
void BinaryTree<T>::BreakTree(T &x, BinaryTree<T> &left, BinaryTree<T> &right){
	if (!root || &left == &right || left.root || right.root){
		return;
	}
	x = root->element;
	left.root = root->lchild;
	right.root = root->rChild;
	delete root;
	root = NULL;
}

