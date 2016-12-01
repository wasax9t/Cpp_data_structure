#pragma once
#include "..\vector\Vector.h"

template <typename T> class Stack :public Vector<T> {
public://size(),empty()等其他开放接口，均可直接沿用
	void push(T const& e);//入栈
	T pop();//出栈
	T& top();//读取栈顶
};

