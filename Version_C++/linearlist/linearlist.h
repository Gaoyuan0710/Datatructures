// =====================================================================================
// 
//       Filename:  linearlist.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年09月05日 17时57分24秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>

using std::ostream;

//namespace gaoyuan{

template <class T>

class LinearList{
	public:
		virtual bool IsEmpty() const = 0;
		virtual int Length()   const = 0;
		virtual bool Find(int i, T & x)    const = 0;
		virtual int Search(T &x)   const = 0;
		virtual bool Insert(int i, T & x)  = 0;
		virtual bool Delete(int i)  = 0;
		virtual bool Update(int i, T & x)  = 0;
		virtual void Output(ostream & out) const = 0;
	protected:
		int n;  
};
//}

