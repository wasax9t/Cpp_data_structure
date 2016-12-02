#pragma once
#include"BST.h"

template<typename T> class Splay : public BST<T> {
protected:
	BNPosi(T) splay(BNPosi(T) v);//将节点v伸展至根
public:
	BNPosi(T) & search(T const&e);
	BNPosi(T) insert(T const&e);
	bool remove(T const&e);
};