#include"AVL.h"

template<typename T>
BNPosi(T) AVL<T>::insert(T const & e)
{
	BNPosi(T) &x = search(e); if (x) return x;
	BNPosi(T) xx = x = new BinNode<T>(e, _hot); _size++;
	for (BNPosi(T) g = _hot; g; g = g->parent) {
		if (!AvlBalanced(*g)) {
			FromParentTo(*g) = rotateAt(TallerChild(TallerChild(g)));
			break;
		}
		else
			updateHeight(g);
	}
	return xx;
}

template<typename T>
bool AVL<T>::remove(T const & e)
{
	BNPosi(T) &x = search(e); if (!x) return false;
	removeAt(x, _hot); _size--;
	for (BNPosi(T) g = _hot; g; g = g->parent) {
		if (!AvlBalanced(*g)) 
			FromParentTo(*g) = rotateAt(TallerChild(TallerChild(g)));
		updateHeight(g);
	}
	return true;
}