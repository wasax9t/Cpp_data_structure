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
#define uncle(x) ( IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)
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
	//构造函数
	BinNode() :parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BNPosi(T) p = NULL, BNPosi(T) lc = NULL, BNPosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED):
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c){}

	int size();
	BNPosi(T) insertAsLc(T const&);
	BNPosi(T) insertAsRc(T const&);
	BNPosi(T) succ();
	template <typename VST> void travLevel(VST&);//子树层次遍历
	template <typename VST> void travPre(VST&);//子树先序遍历
	template <typename VST> void travIn(VST&);//子树中序遍历
	template <typename VST> void travPost(VST&);//子树后序遍历

	bool operator< (BinNode const& bn) { return data < bn.data; }
	bool operator== (BinNode const& bn) { return data == bn.data; }
};

