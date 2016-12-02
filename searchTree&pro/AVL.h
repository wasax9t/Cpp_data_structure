#pragma once
#include"BST.h"

#define Balanced(x) ( stature((x).lc) == stature((x).rc) )//理想平衡条件
#define BalFac(x) ( stature((x).lc) - stature((x).rc) )//平衡因子
#define AvlBalanced(x) ( (-2<BalFac(x)) && (BalFac(x)<2) )//AVL平衡条件
#define TallerChild(x) ( stature((x)->lc) > stature((x)->lc) ? (x)->lc : ( stature((x)->lc) < stature((x)->lc ) ? (x)->rc : ( IsLChild(*(x)) ? (x)->lc:(x)->rc ) ) )

template<typename T> class AVL : public BST<T> {
public:
	BNPosi(T) insert(T const&e);//重写
	bool remove(T const&e);
};

