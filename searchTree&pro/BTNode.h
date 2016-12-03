#pragma once
#include"..\vector\Vector.h"
#define BTNPosi(T) BTNode<T>*

template<typename T> struct BTNode {
	BTNPosi(T) parent;//�ýڵ�ĸ��ڵ�
	Vector<T> key;//�ýڵ�Ĺؼ��룬key��ѭ�ȵ�
	Vector<BTNPosi(T)> child;//�ڵ㱻����ʱ���Դ�һ���յ��ӽڵ�
	BTNode() { parent = NULL; child.insert(0, NULL); }
	BTNode(T e, BTNPosi(T) lc = NULL, BTNPosi(T) rc = NULL) {
		parent = NULL;
		key.insert(0, e);
		child.insert(0, lc); child.insert(1, rc);
		if (lc) lc->parent = this; if (rc) rc->parent = this;
	}
};
