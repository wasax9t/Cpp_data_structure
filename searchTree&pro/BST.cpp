#include"BST.h"

template<typename T>
static BNPosi(T) & searchIn(BNPosi(T)&v, T const&e, BNPosi(T) & hot) {
	if (!v || (e == v->data)) return v;
	hot = v;
	return searchIn(((e < v->data) ? r - lc : r->rc), e, hot);
}

//按照“3+4”结构联接3个节点及4棵子树，返回重组后该局部子树根节点位置
//子树根节点与上层节点的联接建立，将由上层调用者完成
//可用于AVL和RedBlack的局部平衡调整
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
	BNPosi(T) w = x;//w将作为实际被摘除的节点
	BNPosi(T) succN = NULL;//succN将作为返回位置
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