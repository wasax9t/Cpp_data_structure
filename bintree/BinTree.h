#pragma once
#include"BinNode.h"
#include<memory>
using namespace std;
template<typename T> class BinTree
{
protected:
	int _size;
	BNPosi(T) _root;
	virtual int updateHeight(BNPosi(T) x);
	void updateHeightAbove(BNPosi(T) x);
public:
	BinTree() :_size(0), _root(NULL) {}
	~BinTree() { if (0 < _size) remove(_root); }
	int size() const { return _size; }
	bool empty() const { return !_root; }
	BNPosi(T) root() const { return _root; }
	BNPosi(T) insertAsRoot(T const& e) { _size = 1; return _root = new BinNode<T>(e); }
	BNPosi(T) insertAsLC(BNPosi(T) x, T const& e) {
		_size++;
		x->insertAsLc(e);
		updateHeightAbove(x);
		return x->lc;
	}
	BNPosi(T) insertAsRC(BNPosi(T) x, T const& e) {
		_size++;
		x->insertAsRc(e);
		updateHeightAbove(x);
		return x->rc;
	}
	BNPosi(T) attachAsLC(BNPosi(T) x, BinTree<T>* &S) {
		if (x->lc = S->_root) x->lc->parent = x;
		_size += S->_size; updateHeightAbove(x);
		S->_root = NULL; S->_size = 0; release(S); S = NULL;
		return x;
	}
	BNPosi(T) attachAsRC(BNPosi(T) x, BinTree<T>* &T) {
		if (x->rc = S->_root) x->rc->parent = x;
		_size += S->_size; updateHeightAbove(x);
		S->_root = NULL; S->_size = 0; release(S); S = NULL;
		return x;
	}
	int remove(BNPosi(T) x) {//返回x子树规模
		FromParentTo(*x) = NULL;//切断父节点的指针
		updateHeightAbove(x - parent);
		int n = removeAt(x); _size -= n; return n;
	}
	static int removeAt(BNPosi(T) x) {
		if (!x) return 0;
		int n = 1 + removeAt(x->lc) + removeAt(x->rc);
		release(x->data); release(x);
		return n;
	}
	BinTree<T>* secede(BNPosi(T) x) {//删除x处子树，转换为独立子树
		FromParentTo(*x) = NULL;
		updateHeightAbove(x->parent);
		Bintree<T>* S = new BinTree<T>;
		S->_root = x; x->parent = NULL;
		S->_size = x->size(); _size -= S->_size;
		return S;
	}
	template<typename VST>
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }
	template<typename VST>
	void travPre(VST& visit) { if (_root) _root->travPre(visit); }
	template<typename VST>
	void travIn(VST& visit) { if (_root) _root->travIn(visit); }
	template<typename VST>
	void travPost(VST& visit) { if (_root) _root->travPost(visit); }
	bool operator<(BinTree<T> const& t)
	{return _root&&t._root&&lt(_root,t._root); }
	bool operator== (BinTree<T> const& t)
	{return _root&&t._root&&(_root==t._root); }
};

template<typename T>
int BinTree<T>::updateHeight(BNPosi(T) x)
{return x-height=1+max(stature(x-lc),stature(x-rc));}

template<typename T>
void BinTree<T>::updateHeightAbove(BNPosi(T) x)
{	while (x) { updateHeight(x); x = x->parent; }	}

template<typename T,typename VST>
void travPre_R(BNPosi(T) x, VST& visit) {
	if (!x) return;
	visit(x->data);//先序
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}

template<typename T,typename VST>
static void visitAlongLeftBranch(BNPosi(T) x, VST& visit, Stack<BNPosi(T)>& S) {
	while (x) {
		visit(x->data);
		S.push(x->rc);
		x = x->lc;
	}
}

template<typename T,typename VST>//先序遍历迭代版
void travPre_I2(BNPosi(T) x, VST& visit) {
	Stack<BNPosi(T)> S;
	while (true) {
		visitAlongLeftBranch(x, visit, S);
		if (S.empty())break;
		x = S.pop();
	}
}

template<typename T,typename VST>//中序
void travIn_I3(BNPosi(T) x, VST& visit) {
	bool backtrack = false;//回溯标志，当为true为已探索，别再往左子树走了
	while (true) 
		if (!backtrack&&HasLChild(*x)) {
			x = x->lc;
		}
		else {
			visit(x->data);
			if (HasRChild(*x)) {
				x = x->rc;
				backtrack = false;
			}
			else {
				if (!(x = x->succ()))break;
				backtrack = true;
			}
		}
}

template<typename T, typename VST>//中序
void travIn_I4(BNPosi(T) x, VST& visit) {
	while (true)
		if (HasLChild(*x)) {
			x = x->lc;
		}
		else {
			visit(x->data);
			while (!HasRChild(*x))
				if (!(x = x->succ())) return;
				else visit(x->data);
			x = x->rc;
		}
}