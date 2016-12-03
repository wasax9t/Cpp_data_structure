#pragma once
#include"BST.h"

#define IsBlack(p) ( !(p) || (RB_BLACK == (p)->color) )
#define IsRed(p) ( !IsBlack(p) )
#define BlackHeightUpdated(x) ( \
(stature((x).lc) == stature((x).rc)) && \
((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc)+1)) \
)

template<typename T> class RedBlack :public BST<T> {
protected:
	void solveDoubleRed(BNPosi(T) x);
	void solveDoubleBlack(BNPosi(T) x);
	int updateHeight(BNPosi(T) x);
public:
	BNPosi(T) insert(T const&e);
	bool remove(T const&e);
};