#pragma once
#include"..\list\List.h"
template <typename T> class Queue:public List<T> 
{
public:
	void enqueue(T const& e);//��ӣ�β������
	T dequeue();//���ӣ��ײ�ɾ��
	T& front();//��ȡ��������
};