// =====================================================================================
// 
//       Filename:  test_SeqList.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年09月07日 14时07分32秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
//#include "../linearlist.h"
#include "../SeqList.h"

//using namespace gaoyuan;

using std::cout;
using std::cin;
using std::endl;

template <class T>
void Union(SeqList <T> & La, SeqList <T> & Lb){
	T x;

	for (int i = 0; i < Lb.Length(); i++){
		Lb.Find(i, x);

		if (La.Search(x) == -1){
			La.Insert(La.Length() - 1, x);
		}
	}
}

const int SIZE = 20;

int main(int argc, char *argv[])
{
	SeqList <int> La(SIZE);
	SeqList <int> Lb(SIZE);

	for (int i = 0; i < 5; i++){
		La.Insert(i - 1, i);
	}
	for (int i = 5; i < 10; i++){
		Lb.Insert(i - 1, i);
	}

	int a = 0, b = 2, c = 4;

	Lb.Insert(-1, a);
	La.Insert(3, b);

	Lb.Insert(Lb.Length() - 1, c);
	Union(La, Lb);
	La.Output(cout);

	return 0;
}

