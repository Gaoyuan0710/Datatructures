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

class BTNode{
	public:
		BTNode(){
			LChild = RChild = NULL;
		}
		BTNode(char element, BTNode *RChild = NULL, BTNode *LChild = NULL){
			this->element = element;
			this->LChild = LChild;
			this->RChild = RChild;
		}
		char element;
		BTNode *LChild;
		BTNode *RChild;
};

struct struct_Node{
	char element;
	struct_Node *LChild;
	struct_Node *RChild;
};

class BTree{
	public:
		BTree(){
			;
		}
		static void CreateBTree(struct_Node *root);
		static void PreOder(void (*Visit)(char ch), struct_Node *root);
};

void BTree::CreateBTree(struct_Node *root){
	char tmp;

	cout << "Please input the word ";
	cin >> tmp;

	if (tmp == '#'){
		root = NULL;
	}	
	else{
		//root = new BTNode(tmp, root->RChild, root->LChild);

		root = (struct_Node *)malloc(sizeof(struct_Node));
		root->element = tmp;
	
		cout << "the word is " << root->element << endl;

		CreateBTree(root->LChild);
		CreateBTree(root->RChild);
	}
}

void BTree::PreOder(void (*Visit)(char ch), struct_Node *root){
	//cout << "root " << root->element << endl;

	if (root != NULL){
		Visit(root->element);
		PreOder(Visit, root->LChild);
		PreOder(Visit, root->RChild);
	}
}

int main(int argc, char *argv[])
{
//	BTNode testNode;

	struct_Node testNode;
	BTree::CreateBTree(&testNode);
	cout << "OK" << endl;

	cout << "root->element is " << testNode.element << endl;

	BTree::PreOder(Visit, &testNode);
}
