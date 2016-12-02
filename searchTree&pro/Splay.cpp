#include"Splay.h"

template<typename NodePosi>
inline void attachAsLC(NodePosi p, NodePosi lc) {
	p->lc = lc; if (lc) lc->parent = p;
}

template<typename NodePosi>
inline void attachAsRC(NodePosi p, NodePosi rc) {
	p->rc = rc; if (rc) rc->parent = p;
}

//Splay树伸展算法：从节点v出发逐层伸展
template<typename T>
BNPosi(T) Splay<T>::splay(BNPosi(T) v)
{
	if (!v) return NULL;
	BNPosi(T) p; BNPosi(T) g;
	while (p = v->parent&&g = p->parent) {
		BNPosi(T) gg = g->parent;
		if (IsLChild(*v))
			if (IsLChild(*p)) {//zig-zig
				attachAsLC(g, p->rc); attachAsLC(p, v->rc);
				attachAsRC(p, g); attachAsRC(v, p);
			}
			else {//zig-zag
				attachAsLC(p, v->rc); attachAsRC(g, v->lc);
				attachAsLC(v, g); attachAsRC(v, p);
			}
		else if (IsRChild(*p)) {//zag-zag
			attachAsRC(g, p->lc); attachAsRC(p, v->lc);
			attachAsLC(p, g); attachAsLC(v, p);
		}
		else {//zag-zig
			attachAsRC(p, v->rc); attachAsLC(g, v->rc);
			attachAsRC(v, g); attachAsLC(v, p);
		}
		if (!gg) v->parent = NULL;
		else (g == gg->lc) ? attachAsLC(gg, v) : attachAsRC(gg, v);
		updateHeight(g); updateHeight(p); updateHeight(v);
	}//双层伸展结束，必有g==NULL，p可能非空
	if (p = v->parent) {
		if (IsLChild(*v)) { attachAsLC(p, v->rc); attachAsRC(v, p); }
		else { attachAsRC(p, v->rc); attachAsLC(v, p); }
		updateHeight(p); updateHeight(v);
	}
	v->parent = NULL; return v;
}

template<typename T>
BNPosi(T)& Splay<T>::search(T const & e)
{
	BNPosi(T) p = searchIn(_root, e, _hot = NULL);
	_root = splay(p ? p : _hot);
	return _root;
}

template<typename T>
BNPosi(T) Splay<T>::insert(T const & e)
{
	if (!_root) { _size++; return _root = new BinNode<T>(e); }
	if (e == search(e)->data) return _root;//处理两平凡情况
	_size++; BNPosi(T) t = _root;
	if (_root->data < e) {
		t->parent = _root = new BinNode<T>(e, NULL, t, t->rc);
		if (HasRChild(*t)) { t->rc->parent = _root; t->rc = NULL; }
	}
	else {
		t->parent = _root = new BinNode<T>(e, NULL, t->lc, t);
		if (HasLChild(*t)) { t->lc->parent = _root; t->lc = NULL; }
	}
	updateHeightAbove(t);
	return _root;
}

template<typename T>
bool Splay<T>::remove(T const & e)
{
	if (!_root || (e != search(e)->data)) return false;
	BNPosi(T) w = _root;//上一行进行search,e在_root处
	if (!HasLChild(*_root)) {
		_root = _root->rc;
		if (_root) _root->parent = NULL;
	}
	else if (!HasRChild(*_root)) {
		_root = _root->lc;
		if (_root) _root->parent = NULL;
	}
	else {
		BNPosi(T) lTree = _root->lc;
		lTree->parent = NULL; _root->lc = NULL;
		_root = _root->rc; _root->parent = NULL;
		search(w->data);//整形？
		_root->lc = lTree; lTree->parent = _root;
	}
	release(w->data); release(w); _size--;
	if (_root) updateHeight(_root);
	return true;
}

