#pragma once
#include"..\bintree\BinTree.h"

template< typename T> class BST : public BinTree<T> {
protected:
	BNPosi(T) _hot;//father of selected?
	BNPosi(T) connect34(BNPosi(T), BNPosi(T), BNPosi(T),BNPosi(T), BNPosi(T), BNPosi(T), BNPosi(T));//����3�ڵ㼰4����
	BNPosi(T) rotateAt(BNPosi(T) x);
public:
	virtual BNPosi(T) & search(T const& e);
	virtual BNPosi(T) insert(T const& e);
	virtual bool remove(T const& e);
};