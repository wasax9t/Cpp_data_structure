#include"ListNode.h"
#include"List.h"


template<typename T>
void List<T>::init()//初始化
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer; header->pred = NULL;
	trailer->succ = NULL; trailer->pred = header;
	_size = 0;
}

template<typename T>
int List<T>::clear()
{
	int oldsize = _size;
	while (_size > 0) remove(header->succ);
	return oldsize;
}

template<typename T>
void List<T>::mergesort(Posi(T)& p, int)
{
	if (n < 2) return; //若待排序范围已足够小，则直接返回；否则...
	int m = n >> 1; //以中点为界
	ListNodePosi(T) q = p; for (int i = 0; i < m; i++) q = q->succ; //均分列表
	mergeSort(p, m); mergeSort(q, n - m); //对前、后子列表分别排序
	merge(p, m, *this, q, n - m); //归并
}

template<typename T>
void List<T>::selectionsort(Posi(T) p, int n)
{
	ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++) tail = tail->succ; //待排序区间为(head, tail)
	    while (1 < n) { 
		       ListNodePosi(T) max = selectMax(head->succ, n); //找出最大者（歧义时后者优先）
		       insertB(tail, remove(max)); //将其移至无序区间末尾（作为有序区间新的首元素）
		       tail = tail->pred; n--;
		
	}	
}

template<typename T>
void List<T>::insertionsort(Posi(T) p, int n)
{
	for (int r = 0; r < n; r++) {
		insertsucc(search(p->data, r, p), p->data);
		p = p->succ; remove(p->pred);
	}
}

template<typename T>
void List<T>::copyNodes(Posi(T) p, int n)
{
	init();
	while (n--) { insertAslast(p->data); p = p->succ; }//p->succ才能保证顺序不变
}

template<typename T>
void List<T>::merge(Posi(T)& p, int n, List<T>& L, Posi(T) q, int m)
{
	ListNodePosi(T) pp = p->pred; //借助前驱（可能是header），以便返回前 ...
	while (0 < m) //在q尚未移出区间之前
	    if ((0 < n) && (p->data <= q->data)) //若p仍在区间内且v(p) <= v(q)，则
	       { if (q == (p = p->succ)) break; n--; } //p归入合并的列表，并替换为其直接后继
	    else //若p已超出右界或v(q) < v(p)，则
		   { insertB(p, L.remove((q = q->succ)->pred)); m--; } //将q转移至p之前
	    p = pp->succ; //确定归并后区间的（新）起点
}

template<typename T>
T & List<T>::operator[](Rank r) const
{
	ListNodePosi<T> p = frist();
	while (0 < r--) p = p->succ;
	return p->data;
}

template<typename T>
Posi(T) List<T>::find(T const & e, int n, Posi(T) p) const
{
	while (0 < n--)//自p向前查找n个位置
		if (e == (p = p->pred)->data) return p;
	return NULL;
}

template<typename T>
Posi(T) List<T>::search(T const & e, int n, Posi(T) p) const
{
	while (o <= n--)
		if (((p = p->pred)->data) <= e) break;
	return p;
}

template<typename T>
Posi(T) List<T>::selectmax(Posi(T) p, int n)
{
	Posi(T) max = p;
	for (Posi(T) cur = p; 1 < n; n--)
		if (!lt((cur = cur->succ)->data, max->data))
			max = cur;
	return max;
}

template<typename T>
Posi(T) List<T>::insertAsfrist(T const & e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
Posi(T) List<T>::insertAslast(T const & e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template<typename T>
Posi(T) List<T>::insertpred(Posi(T) p, T const & e)
{
	_size++;
	return p->insertAsPred(e);
}

template<typename T>
Posi(T) List<T>::insertsuss(Posi(T) p, T const & e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
T List<T>::remove(Posi(T) p)
{
	T e = p->data;
	p->succ->pred = p->pred; p->pred->succ = p->succ;
	delete p; _size--;
	return e;
}

template<typename T>
void List<T>::sort(Posi(T) p, int n)
{
	switch (rand() % 3) {
	case 1:insertionsort(p, n); break;
	case 2:selectionsort(p, n); break;
	default:mergesort(p, n); break;
	}
}

template<typename T>
int List<T>::deduplicate()
{
	if (_size < 2) return 0;
	int oldsize = _size;
	Posi(T) p = header; Rank r = 0;
	while (trailer != (p = p->succ)) {
		Posi(T) q = find(p->data, r, q);
		q ? remove(q) : r++;
	}
	return oldsize-_size;
}

template<typename T>
int List<T>::uniquify()
{
	if (_size < 2) return 0;
	int oldsize = _size;
	Posi(T) p = frist(); Posi(T) q;
	while (trailer != (q = p->succ)) {
		if (p->data!q->data) p = q;
		else remove(q);
	}
	return oldsize-_size;
}

