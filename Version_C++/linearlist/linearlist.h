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

namespace gaoyuan{

template <class T>

class LinearList{
	public:
		virtual bool IsEmpty() const = 0;
		virtual int Length()   const = 0;
		virtual bool Find()    const = 0;
		virtual int Search()   const = 0;
		virtual bool Insert()  = 0;
		virtual bool Delete()  = 0;
		virtual bool Update()  = 0;
		virtual void Output(ostream & out) const = 0;
	protected:
		int length_of_linear_list;  
}
}

