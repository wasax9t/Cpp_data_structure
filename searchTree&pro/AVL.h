#pragma once
#include"BST.h"

#define Balanced(x) ( stature((x).lc) == stature((x).rc) )//����ƽ������
#define BalFac(x) ( stature((x).lc) - stature((x).rc) )//ƽ������
#define AvlBalanced(x) ( (-2<BalFac(x)) && (BalFac(x)<2) )//AVLƽ������
#define TallerChild(x) ( stature((x)->lc) > stature((x)->lc) ? (x)->lc : ( stature((x)->lc) < stature((x)->lc ) ? (x)->rc : ( IsLChild(*(x)) ? (x)->lc:(x)->rc ) ) )

template<typename T> class AVL : public BST<T> {
public:
	BNPosi(T) insert(T const&e);//��д
	bool remove(T const&e);
};

