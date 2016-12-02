#include"BST.h"

template<typename T>
static BNPosi(T) & searchIn(BNPosi(T)&v, T const&e, BNPosi(T) & hot) {
	if (!v || (e == v->data)) return v;
	hot = v;
	return searchIn(((e < v->data) ? r - lc : r->rc), e, hot);
}

//���ա�3+4���ṹ����3���ڵ㼰4�����������������þֲ��������ڵ�λ��
//�������ڵ����ϲ�ڵ�����ӽ����������ϲ���������
//������AVL��RedBlack�ľֲ�ƽ�����
template<typename T>
BNPosi(T) BST<T>::connect34(BNPosi(T) a, BNPosi(T) b, BNPosi(T) c, BNPosi(T) T0, BNPosi(T) T1, BNPosi(T) T2, BNPosi(T) T3)
{
	a->lc = T0; if (T0) T0->parent = a;
	a->rc = T1; if (T1) T1->parent = a;
	updateHeight(a);
	c->lc = T2; if (T2) T2->parent = c;
	c->rc = T3; if (T3) T3->parent = c;
	updateHeight(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b;
	updateHeight(b);
	return b;
}

template<typename T>
BNPosi(T) BST<T>::rotateAt(BNPosi(T) v)
{
	BNPosi(T) p = v->parent; BNPosi(T) g = p->parent;
	if(IsLChild(*p))
		if (IsLChild(*v)) {
			p->parent = g->parent;
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else {
			v->parent = g->parent;
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	else
		if (IsRChild(*v)) {
			p->parent = g->parent;
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
		else {
			v->parent = g->parent;
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
}

template<typename T>
BNPosi(T) & BST<T>::search(T const&e) {
	return searchIn(_root, e, _hot = NULL);
}

template<typename T>
BNPosi(T) BST<T>::insert(T const & e)
{
	BNPosi(T) & x = search(e);
	if (x) return x;
	x = new BinNode<T>(e, _hot);
	_size++;
	updateHeightAbove(x);
	return x;
}

template<typename T> 
bool BST<T>::remove(T const& e) {
	BNPosi(T) & x = search(e);
	if (!x) return false;
	removeAt(x, _hot); _size--;
	updateHeightAbove(x);
	return true;
}

template<typename T>
static BNPosi(T) removeAt(BNPosi(T) &x, BNPosi(T) &hot) {
	BNPosi(T) w = x;//w����Ϊʵ�ʱ�ժ���Ľڵ�
	BNPosi(T) succN = NULL;//succN����Ϊ����λ��
	if (!HasLChild(*x))
		succN = x = x->rc;
	else if (!HasRChild(*x))
		succN = x = x->lc;
	else {
		w = w->succ();
		swap(x->data, w->data);
		BNPosi(T) u = w->parent;
		((u == x) ? u->rc, u->lc) = succN = w->rc;
	}
	hot = w->parent;
	if (succN) succN->parent = hot;
	release(w->data); release(w); return succN;
}