// =====================================================================================
// 
//       Filename:  SeqList.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年09月07日 12时27分28秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include "linearlist.h"


using std::cout;
using std::cin;
using std::endl;

namespace gaoyuan {

template <class T>
class SeqList:public LinearList<T> {
	public:
		SeqList(int mSize);
		~SeqList(){
			delete [] elements;
		}
		bool IsEmpty() const;
		int Length()   const;
		bool Find(int i, T & x) const;
		int Search(T &x) const;
		bool Insert(int i, T &x) const;
		bool Delete(int i);
		bool Update(int i, T &x);
		void Output() const;
	private:
		int maxLength;
		T * element;
};

template <class T>
SeqList<T>::SeqList(int mSize){
	maxLength = mSize;
	element = new T[maxLength];
	n = 0;
}

template <class T>
bool SeqList<T>::IsEmpty()const{
	return n == 0;
}

template <class T>
int SeqList<T>::Length const{
	return n;
}

template <class T>
bool SeqList<T>::Find(int i, T & x) const{
	if (i < 0 || i > n - 1){
		cout << "Out of Bounds " << endl;

		return false;
	}
	x = element[i];
	
	return true;
}


template <class T>
int SeqList<T>::Search( T & x){
	for (int i = 0; i < n; i ++){
		if (elements[i] == x){
			return i;
		}
	}
	return -1;
}


template <class T>
bool SeqList<T>::Insert(int i, T & x){
	if (i < -1 || i > n - 1){
		cout << "Out of Bounds" << endl;

		return false;
	}
	if (n == maxLength){
		cout << "OverFlow" << endl;

		return false;
	}

	for (int j = n - 1; j > i; j--){
		element[j + 1] = element[j];
	} 
	element[i + 1] = x;
	n++;

	return true;
}


template <class T>
bool SeqList<T>::Delete(int i){
	if (!n){
		cout << "UnderFlow" << endl;

		return false;
	}
	if (i < 0 || i > n - 1){
		cout << "Out Of Bounds" << endl;

		return false;
	}
	for (int j = i + 1; j < n; j++){
		element[j] = element[j + 1];
	}
	n--;
	return true;
}

template <class T>
bool SeqList<T>::Update(int i, T & x){
	if (i < 0 || i > n - 1){
		cout << " Out of Bounds " << endl;

		return false;
	}
	element[i] = x;

	return true;
}

template <class T>
void SeqList<T>::Output(){
	for (int i =0; i < n; i++){
		cout << element[i] << " ";
	}
	cout << endl;
}
}
