#pragma once
#include"..\bintree\BinTree.h"

template< typename T> class BST : public BinTree<T> {
protected:
	BNPosi(T) _hot;//father of selected?
	BNPosi(T) connect34(BNPosi(T) a, BNPosi(T) b, BNPosi(T) c,\
		BNPosi(T) T0, BNPosi(T) T1, BNPosi(T) T2, BNPosi(T) T3);//����3�ڵ㼰4����
	BNPosi(T) rotateAt(BNPosi(T) x);
public:
	virtual BNPosi(T) & search(T const& e);
	virtual BNPosi(T) insert(T const& e);
	virtual bool remove(T const& e);
};