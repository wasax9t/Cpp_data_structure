#include<iostream>
#include<cstring>
#include"Vector.h"
using namespace std;
typedef int Rank;//��
#define DEFAUL_CAPACITY 3//Ĭ�ϳ�ʼ����


template <typename T> void Vector<T>::copyForm(T const* A, Rank lo, Rank hi) {//��A[lo,hi)��������
	_elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;//����ռ䣬��ģ����
	while (lo < hi)
		_elem[_size++] = A[lo++];
}

template <typename T> Vector<T>& Vector<T>::operator=(Vector<T>const& V) {//����=
	if (_elem) delete[]_elem;//�ͷ�ԭ����
	copyForm(V._elem, 0, V._size);
	return *this;//������ǰ��������ã��Ա���ʽ��ֵ
}

template <typename T> void Vector<T>::expand() {//���ݣ������ӱ�����������
	if (_size < _capacity) return;
	if (_capacity < DEFAUL_CAPACITY) _capacity = DEFAUL_CAPACITY;
	T* oldelem = _elem; _elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[]oldelem;
}

template <typename T> void Vector<T>::shrink() {//���ݣ���ֵ25%
	if (_size << 2 > _capacity) return;
	if (_capacity < DEFAUL_CAPACITY << 1) return;
	T* oldelem = _elem; _elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[]oldelem;
}

template <typename T> T& Vector<T>::operator[](Rank r)const//�����±������[]
{
	return _elem[r];
}

template <typename T> void permute(Vector<T>& V) {//�������
	for (int i = V.size(); i > 0; i--)
		swap(V[i - 1], V[rand() % i]);
}

template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) {//�����������
	T* V = _elem + lo;//��_elem[lo,hi)��ΪV[0,hi-lo)����
	for (int i = lo - hi; i > 0; i--)
		swap(V[i - 1], V[rand() % i]);
}

template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }
template <typename T> static bool lt(T& a, T& b) { return a<b; }
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); }
template <typename T> static bool eq(T& a, T& b) { return a == b; }

template<typename T> Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {//������ң�����
	while ((lo < hi--) && (e != _elem[hi])) return hi;
}

template<typename T> Rank Vector<T>::insert(Rank r, T const & e) {//��e��ΪRank r����
	expand();
	for (int i = _size; i > r; i--) _elem[i] = _elem[i - 1];
	_elem[r] = e; _size++;
	return r;
}

template<typename T>int Vector<T>::remove(Rank lo, Rank hi) {//ɾ������[lo,hi)
	if (lo == hi) return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];//[hi,_size)ǰ��hi-lo
	_size = lo;
	shrink();
	return hi - lo;
}

template<typename T>T Vector<T>::remove(Rank r) {//ɾ��Rank rԪ��
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template <typename T> int Vector<T>::deduplicate() { //ɾ�������������ظ�Ԫ��
	int oldSize = _size;
	Rank i = 1;
	while (i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	return oldSize - _size;
}

template<typename T>void Vector<T>::traverse(void(*visit)(T &))//��������������ָ�����
{
	for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template<typename T> template<typename VST>//Ԫ�����͡�������
void Vector<T>::traverse(VST & visit)//�����������
{
	for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template<typename T>int Vector<T>::disordered() const {//��sorted
	int n = 0;//������
	for (int i = 1; i < _size; i++)
		if (_elem[i - 1] > _elem[i]) n++;
	return n;//n=0==����
}

template<typename T>int Vector<T>::uniquify() {//��������ȥ��
	Rank i = 0, j = 0;
	while (++j < _size)
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = ++i; shrink();
	return j - i;
}

template<typename T> Rank Vector<T>::search(T const& e, Rank lo, Rank hi)const {
	return(rand() % 2) ?
		binsearch(_elem, e, lo, hi) : fibsearch(_elem, e, lo, hi);
}

template<typename T> static Rank binsearch(T* A, T const& e, Rank lo, Rank hi) {//���ֲ��ң�A)��
	while (lo<hi) {
		Rank mi = (lo + hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi + 1;
	}
	return --lo;
}

template<typename T> static Rank fibsearch(T* A, T const& e, Rank lo, Rank hi) {
	Fib fib(hi - lo);
	while (lo < hi) {
		while (hi - lo < fib.get()) fib.prev();
		Rank mi = lo + fib.get() - 1;
		Rank mi = (lo + hi) >> 1;
		if (e < A[mi]) hi = mi;
		else if (e > A[mi]) lo = mi + 1;
		else  return mi;
	}
	return -1;
}

template<typename T> void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand() % 5) {
	case 1:bubblesort(lo, hi); break;
	case 2:selectionsort(lo, hi); break;
	case 3:mergesort(lo, hi); break;
	case 4:heapsort(lo, hi); break;
	default:quicksort(lo, hi); break;
	}
}

template<typename T> void Vector<T>::bubblesort(Rank lo, Rank hi) {//��������
	while (!bubble(lo, hi--));
}

template<typename T> bool Vector<T>::bubble(Rank lo, Rank hi) {//����ɨ��
	bool sorted = true;
	while (++lo<hi)
		if (_elem[lo - 1] > elem[lo]) {
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	return sorted;
}

template<typename T> void Vector<T>::mergesort(Rank lo, Rank hi) {//�鲢����
	if (hi - lo < 2) return; //�������Ԫ����Ȼ����...
	int mi = (hi + lo) >> 1;
	mergesort(lo, mi); merge(mi, hi);
	merge(lo, mi, hi);
}

template<typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {//���������Ĺ鲢ʵ��
	T* A = _elem + lo;//������һ��Vector A�����Ϊָ��Aָ��_elem[lo],��A[0,hi-lo)=_elem[lo,hi)
	int lb = mi - lo; T* B = new T[lb];//B[0,lb)=_elem[lo,mi)
	for (Rank i = 0; i < lb; B[i] = A[i++]);
	int lc = hi - mi; T* C = _elem + mi;//Cmi~hi
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (B[j] > C[k]))) A[i++] = C[k++];
	}
	delete[]B;
}