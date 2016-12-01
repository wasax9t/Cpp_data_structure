#pragma once
#include"..\list\List.h"
template <typename T> class Queue:public List<T> 
{
public:
	void enqueue(T const& e);//入队：尾部插入
	T dequeue();//出队：首部删除
	T& front();//读取队首数据
};