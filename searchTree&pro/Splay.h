#pragma once
#include"BST.h"

template<typename T> class Splay : public BST<T> {
protected:
	BNPosi(T) splay(BNPosi(T) v);//���ڵ�v��չ����
public:
	BNPosi(T) & search(T const&e);
	BNPosi(T) insert(T const&e);
	bool remove(T const&e);
};