#include "Stack.h"

template<typename T>
inline void Stack<T>::push(T const & e) { insert(size(), e); }

template<typename T>
inline T Stack<T>::pop() { return remove(size() - 1); }

template<typename T>
inline T & Stack<T>::top() { return (*this)[size() - 1]; }
