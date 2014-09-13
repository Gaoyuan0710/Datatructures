// =====================================================================================
// 
//       Filename:  Btree.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年09月11日 21时24分43秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <malloc.h>

using std::cout;
using std::cin;
using std::endl;


void Visit(char ch){
	cout << " " << ch;
}

class BTNode;
class BTNode{
	public:
		BTNode(){
			element = '\0';
			LChild = NULL;
			RChild = NULL;
		}
		char element;
		BTNode &LChild;
		BTNode &RChild;
};
class BTree{
	public:
		BTree(){
			;
		}
		void CreatBTree(BTNode &root);
		void PreOder(void (*Visit(char ch)), BTNode &root);
};

void BTree::CreatBTree(BTNode &root){
	char tmp;

	cout << "Please input the word: ";
	cin >> tmp;

	if (tmp == '#') {
		root = new BTNode();
	}
	else{
		root = new BTNode();
		root.element = tmp;
		CreatBTree(root.LChild);
		CreatBTree(root.RChild);

	}
}
void BTree::PreOder(void (*Visit)(char ch), BTNode &root){
	if (!root){
		Visit(root.element);
		PreOder(Visit, root->LChild);
		PreOder(Visit, root->RChild);
	}
}
int main(int argc, char *argv[])
{
	BTree testTree;
	BTNode testNode;

	testTree.CreatBTree(testNode);
	testTree.PreOder(Visit, testNode);

	return 0;
}

