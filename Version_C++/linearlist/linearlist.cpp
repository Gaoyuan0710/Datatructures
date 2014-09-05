// =====================================================================================
// 
//       Filename:  linearlist.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年09月05日 18时44分07秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include "linearlist.h"

namespace gaoyuan{

using std::cout;
using std::cin;
using std::endl;

template <class T>

class SeqList:public LinearList<T>{
	public:
		SeqList(int mSize);
		~SeqList(){
			delete [] element;
		}
		bool IsEmpty() const;
		int Length()   const;
		bool Find(int num, T & x) const;
		int  Search(int num, T & x) const;
		bool Insert(int num, T & x);
		bool Delete(int num);
		bool Update(int num, T & x);
		void Output(ostream &out)const ;
	private:
		int maxLength;
		T *element;
};

template <class T>
SeqList<T>::SeqList(int mSize) const{
	maxLength = maxLength;
	element = new T [maxLength];
	n = 0;
}

template <class T>
bool SeqList<T> ::IsEmpty() const{
	return n == 0;
}

template <class T>
int SeqList<T>::Length() const{
	return n;
}

template <class T>
bool SeqList<T>::Find(int num, T & x) const{
	if ( num < 0 || num > n - 1){
		cout << "Out of Bounds " << endl;

		return false;
	}
	x = element[i];
	return true; 
}

template <class T>
int SeqList<T> ::Search(int num, T & x) const{
	for (int j =0; j < n; j++){
		if (element[j] == x){
			return j;
		}
	}
	return -1;
}

template <class T>
int SeqList<T>::S

}
