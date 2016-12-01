#pragma once
#define BNPosi(T) BinNode<T>*
#define stature(P) ((P)? (P)->height:-1)
typedef	enum { RB_RED, RB_BLACK } RBColor;

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x)&&(&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x)&&(&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x)||HasRChild(x))
#define HasBothChild(x) (HasLChild(x)&&HasRChild(x))
#define Isleaf(x) (!HasChild(x))

#define sibling(p) ( IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc)
#define uncle(x) ( IsLChild(*((x)->parent))?(x)->parent->parent->rc:(x)->parent->parent->lc)
#define FromParentTo(x) (IsRoot(x)?_root:(IsLChild(x)?(x).parent->rc:(x).parent->lc))

template <typename T> struct BinNode
{
	T data;
	BNPosi(T) parent;
	BNPosi(T) lc;
	BNPosi(T) rc;
	int height;
	int npl;//Null Path Length左右堆
	RBColor color;

	BinNode() :parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
	BinNode()(T e, BNPosi(T) p = NULL,BNPosi(T) lc=NULL,BNPosi(T) rc=NULL,int h=0,int l=1.RBColor c=RB_RED):
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(RB_RED){}

	int size();
	BNPosi(T) insertAsLc(T const&);
	BNPosi(T) insertAsRc(T const&);
	BNPosi(T) succ();
	template <template VST> void travLevel(VST&);//子树层次遍历
	template <template VST> void travPre(VST&);//子树先序遍历
	template <template VST> void travIn(VST&);//子树中序遍历
	template <template VST> void travPost(VST&);//子树后序遍历

	bool operator< (BinNode const& bn) { return data < bn.data; }
	bool operator== (BinNode const& bn) { return data == bn.data; }
};

template<typename T>
inline BNPosi(T) BinNode<T>::insertAsLc(T const & e)
{
	return lc=new BinNode(e,this);
}

template<typename T>
inline BNPosi(T) BinNode<T>::insertAsRc(T const &)
{
	return rc=new BinNode(e,this);
}

template<typename T>
inline BNPosi(T) BinNode<T>::succ()//仅中序遍历下的直接后续如此
{
	BNPosi(T) s = this;
	if (rc) {
		s = rc;
		while (HasLChild(*s)) s = s->lc;
	}
	else {
		while (IsRChild(*s)) s = s->parent;
		s = s->parent;
	}
	return s;
}

template<typename T>
template<template VST>
inline void BinNode<T>::travIn(VST &visit)
{
	switch (rand()%5)
	{
	case 1:travIn_I1(this, visit); break;
	case 2:travIn_I2(this, visit); break;
	case 3:travIn_I3(this, visit); break;
	case 4:travIn_I4(this, visit); break;
	default:travIn_R(this, visit); break;
	}
}
