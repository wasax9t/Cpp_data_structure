#include"List.h"


template<typename T>
void List<T>::init()//��ʼ��
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
	if (n < 2) return; //��������Χ���㹻С����ֱ�ӷ��أ�����...
	int m = n >> 1; //���е�Ϊ��
	ListNodePosi(T) q = p; for (int i = 0; i < m; i++) q = q->succ; //�����б�
	mergeSort(p, m); mergeSort(q, n - m); //��ǰ�������б�ֱ�����
	merge(p, m, *this, q, n - m); //�鲢
}

template<typename T>
void List<T>::selectionsort(Posi(T) p, int n)
{
	ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++) tail = tail->succ; //����������Ϊ(head, tail)
	    while (1 < n) { 
		       ListNodePosi(T) max = selectMax(head->succ, n); //�ҳ�����ߣ�����ʱ�������ȣ�
		       insertB(tail, remove(max)); //����������������ĩβ����Ϊ���������µ���Ԫ�أ�
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
	while (n--) { insertAslast(p->data); p = p->succ; }//p->succ���ܱ�֤˳�򲻱�
}

template<typename T>
void List<T>::merge(Posi(T)& p, int n, List<T>& L, Posi(T) q, int m)
{
	ListNodePosi(T) pp = p->pred; //����ǰ����������header�����Ա㷵��ǰ ...
	while (0 < m) //��q��δ�Ƴ�����֮ǰ
	    if ((0 < n) && (p->data <= q->data)) //��p������������v(p) <= v(q)����
	       { if (q == (p = p->succ)) break; n--; } //p����ϲ����б����滻Ϊ��ֱ�Ӻ��
	    else //��p�ѳ����ҽ��v(q) < v(p)����
		   { insertB(p, L.remove((q = q->succ)->pred)); m--; } //��qת����p֮ǰ
	    p = pp->succ; //ȷ���鲢������ģ��£����
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
	while (0 < n--)//��p��ǰ����n��λ��
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

