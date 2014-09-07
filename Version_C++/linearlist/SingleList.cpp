// =====================================================================================
// 
//       Filename:  SingleList.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年09月07日 16时08分32秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include "linearlist.h"

using std::ostream;
using std::cout;
using std::cin;
using std::endl;

namespace gaoyuan{

template <class T> class SingleList;
template <class T>
class Node{
	private:
		T element;
		Node<T> *link;
		friend class SingleList<T>;
};

template <class T>
class SingleList:public LinearList<T>{
	public:
		SingleList(){
			first_node = NULL;
			n = 0;
		}
		~SingleList();
		bool IsEmpty() const;
		int Length() const;
		bool Find(int x, T & x) const;
		int Search(T x) const;
		bool Insert(int i, T &x);
		bool Delete(int i);
		bool Update(int i, T &x);
		void Clear();
		void Output(ostream & out) const;
	private:
		Node<T> *first_node;
};

template <class T>
SingleList<T>::~SingleList(){
	Node<T> *p;

	while (first_node){
		p = first_node->link;
		delete first_node;
		first_node = p;
	}
}

template <class T>
int SingleList<T>::Length() const{
	return n;
}

template <class T>
bool SingleList<T>::IsEmpty() const{
	return n == 0;
}

template <class T>
bool SingleList<T>::Find(int i, T & x) const{
	if (i < 0 || i > n - 1){
		cout << "Out of Bounds" << endl;

		return false;
	}
	Node<T> *p = first_node;

	for (int j = 0; j < i; j++){
		p = p->link;
	}
	x = p->element;

	return true;
}

template <class T>
int SingleList<T>::Search(T x)const{
	Node<T> *p = first_node;

	for (int j = 0; p && p->element != x; j++){
		p = p->link;
	}
	if (p){
		return j;
	}
	return -1;
}

}
int main(int argc, char *argv[])
{


	return 0;
}

