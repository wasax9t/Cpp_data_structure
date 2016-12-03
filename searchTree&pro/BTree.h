#pragma once
#include"BTNode.h"

template<typename T> class BTree {
protected:
	int _size;
	int _order;//B���Ľ״Σ�����Ϊ3,����·��
	BTNPosi(T) _root;
	BTNPosi(T) _hot;//search()�����ʵķǿսڵ�λ��
	void solveOverflow(BTNPosi(T) v);//��������
	void solveUnderflow(BTNPosi(T) v);//����ϲ�
public:
	BTree(int order = 3) :_order(order), _size(0) { _root = new BTNode<T>(); }
	~BTree() { if (_root) release(_root); }
	int const order() { return _order; }
	int const size() { return _size; }
	BTNPosi(T) & root() { return _root; }
	bool empty() const { return !_root; }
	BTNPosi(T) search(T const &e);
	bool insert(T const &e);
	bool remove(T const &e);
};
