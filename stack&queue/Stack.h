#pragma once
#include "..\vector\Vector.h"

template <typename T> class Stack :public Vector<T> {
public://size(),empty()���������Žӿڣ�����ֱ������
	void push(T const& e);//��ջ
	T pop();//��ջ
	T& top();//��ȡջ��
};

