// =====================================================================================
// 
//       Filename:  BTNode.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年09月09日 11时11分55秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>

template <class T>

class BTNode{
	public:
		BTNode(){
			rChild = lChild = NULL;
		}
		BTNode(const T &x){
			element = x;
			rChild = lChild = NULL;
		}
		BTNode(const T &x, BTNode<T> *l, BTNode<T> *r){
			element = x;
			rChild = r;
			lChild = l;
		}
	private:
		T element;
		BTNode<T> *lChild, *rChild;
}
