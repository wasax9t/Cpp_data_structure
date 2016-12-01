#include "List.h"
#include "Queue.h"

template<typename T> void Queue<T>::enqueue(T const& e) {
	insertAslast(e);
}

template<typename T> T Queue<T>::dequeue() {
	return remove(frist());
}

template<typename T> T & Queue<T>::front()
{
	return first()-> data;
}

