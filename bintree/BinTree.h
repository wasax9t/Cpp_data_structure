#pragma once
#include"BinNode.h"
#include<memory>

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
	BNPosi(T) insertAsLC(BNPosi(T) x, T const& e);
	BNPosi(T) insertAsRC(BNPosi(T) x, T const& e);
	BNPosi(T) attachAsLC(BNPosi(T) x, BinTree<T>* &S);
	BNPosi(T) attachAsRC(BNPosi(T) x, BinTree<T>* &T);
	int remove(BNPosi(T) x);
	static int removeAt(BNPosi(T) x);
	BinTree<T>* secede(BNPosi(T) x);
	//遍历接口
	template<typename VST>
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }
	template<typename VST>
	void travPre(VST& visit) { if (_root) _root->travPre(visit); }
	template<typename VST>
	void travIn(VST& visit) { if (_root) _root->travIn(visit); }
	template<typename VST>
	void travPost(VST& visit) { if (_root) _root->travPost(visit); }
	//重载操作符
	bool operator<(BinTree<T> const& t)
	{return _root&&t._root&&lt(_root,t._root); }
	bool operator== (BinTree<T> const& t)
	{return _root&&t._root&&(_root==t._root); }
};

