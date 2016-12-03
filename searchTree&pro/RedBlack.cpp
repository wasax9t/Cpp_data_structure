#include"RedBlack.h"

template<typename T>
int RedBlack<T>::updateHeight(BNPosi(T) x)
{
	x->height = max(stature(x->lc), stature(x->rc));
	return IsBlack(x) ? x->height++ : x->height;
}

template<typename T>
BNPosi(T) RedBlack<T>::insert(T const & e)
{
	BNPosi(T) &x = search(e); if (x) return x;
	x = new BinNode<T>(e, _hot, NULL, NULL, -1); _size++;
	solveDoubleRed(x); return x ? x : _hot->parent;
}

template<typename T>
void RedBlack<T>::solveDoubleRed(BNPosi(T) x)
{
	if(IsRoot(*x)){
		_root->color = RB_BLACK; _root->height++; return;	
	}
	BNPosi(T) p = x->parent; if (IsBlack(p)) return;
	BNPosi(T) g = p->parent;
	BNPosi(T) u = uncle(x);
	if (IsBlack(u)) {
		if (IsLChild(*x) == IsLChild(*p))
			p->color = RB_BLACK;
		else
			x->color = RB_BLACK;
		g->color = RB_RED;
		BNPosi(T) gg = g->parent;
		BNPosi(T) r = FromParentTo(*g) = rotateAt(x);
		r->parent = gg;
	}
	else {
		p->color = RB_BLACK; p->height++;
		u->color = RB_BLACK; u->height++;
		if (!IsRoot(*g)) g->color = RB_RED;
		solveDoubleRed(g);
	}
}

template<typename T>
bool RedBlack<T>::remove(T const & e)
{
	BNPosi(T) &x = search(e); if(!x) return false;
	BNPosi(T) r = removeAt(x, _hot); if (!(--_size)) return true;
	if (!_hot) {
		_root->color = RB_BLACK; updateHeight(_root); return true;
	}
	if (BlackHeightUpdated(*_hot)) return true;
	if (IsRed(r)) {
		r->color = RB_BLACK; r->height++; return true;
	}
	solveDoubleBlack(r); return true;
}

template<typename T>
void RedBlack<T>::solveDoubleBlack(BNPosi(T) x)
{
	BNPosi(T) p = r ? r->parent : _hot; if (!p) return;
	BNPosi(T) s = (r == p->lc) ? p->rc : p->lc;
	if (IsBlack(s)) {
		BNPosi(T) t = NULL;//t将为s的红孩子，无则NULL
		if (IsRed(s->rc)) t = s->rc;
		if (IsRed(s->lc)) t = s->lc;
		if (t) {//BB-1
			RBColor oldColor = p->color;
			BNPosi(T) b = FromParentTo(*p) = rotateAt(t);
			if (HasLChild(*b)) { b->lc->color = RB_BLACK; updateHeight(b->lc); }
			if (HasRChild(*b)) { b->rc->color = RB_BLACK; updateHeight(b->rc); }
			b->color = oldColor; updateHeight(b);
		}
		else {
			s->color = RB_RED; s->height--;
			if (IsRed(p)) {//BB-2R
				p->color = RB_BLACK;
			}
			else {//BB-2B
				p->height--;
				solveDoubleBlack(p);//递归上溯
			}
		}
	}
	else {//BB-3
		s->color = RB_BLACK; p->color = RB_RED;
		BNPosi(T) t = IsLChild(*s) ? s->lc : s->rc;
		_hot = p; FromParentTo(*p) = rotateAt(t);
		solveDoubleBlack(r);
	}
}