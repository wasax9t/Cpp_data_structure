#pragma once
#include"..\vector\Vector.h"
#define BTNPosi(T) BTNode<T>*

template<typename T> struct BTNode {
	BTNPosi(T) parent;//该节点的父节点
	Vector<T> key;//该节点的关键码，key是循秩的
	Vector<BTNPosi(T)> child;//节点被创建时将自带一个空的子节点
	BTNode() { parent = NULL; child.insert(0, NULL); }
	BTNode(T e, BTNPosi(T) lc = NULL, BTNPosi(T) rc = NULL) {
		parent = NULL;
		key.insert(0, e);
		child.insert(0, lc); child.insert(1, rc);
		if (lc) lc->parent = this; if (rc) rc->parent = this;
	}
};
