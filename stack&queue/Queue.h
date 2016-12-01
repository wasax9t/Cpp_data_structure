#include"List.h"
template <typename T> class Queue:public List<T> 
{
public:
	void enqueue(T const& e);
	T dequeue();
	T& front();
};