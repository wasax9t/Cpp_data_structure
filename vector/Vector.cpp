#include<iostream>
#include<cstring>
#include"Fib.h"
using namespace std;
typedef int Rank;//秩
#define DEFAUL_CAPACITY 3//默认初始容量

template <typename T> class Vector {
protected:
	Rank _size; int _capacity; T* _elem;//规模(大小）、容量（可用大小）、数据区
	void copyForm(T const* A, Rank lo, Rank hi);//复制数组区间A[lo,hi)
	void expand();//容量不足时扩容
	void shrink();
	bool bubble(Rank lo, Rank hi);
	void bubblesort(Rank lo, Rank hi);
	Rank max(Rank lo, Rank hi);//选取最大元素
	void selectionsort(Rank lo, Rank hi);
	void merge(Rank lo, Rank mi, Rank hi);//归并算法
	void mergesort(Rank lo, Rank hi);
	Rank partition(Rank lo, Rank hi);//轴点构造算法
	void quicksort(Rank lo, Rank hi);
	void heapsort(Rank lo, Rank hi);//堆排序
public:
	//构造函数
	Vector(int c = DEFAUL_CAPACITY, int s = 0, T v = 0)//容量为c、规模为s、所有元素初始化为v
	{
		_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
	}//s<=c
	Vector(T const* A, Rank n) { copyForm(A, 0, n); }//数组整体复制
	Vector(T const* A, Rank lo, Rank hi) { copyForm(A, lo, hi); }
	Vector(Vector<T> const& V) { copyForm(V._elem, 0, V._size); }//向量整体复制
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyForm(V._elem, lo, hi); }
	//析构函数
	~Vector() { delete[] _elem; }
	//只读访问接口
	Rank size()const { return _size; }
	bool empty()const { return !_size; }//判空
	int disordered()const;//判断是否已排序
	Rank find(T const& e)const { return find(e, 0, _size); }//无序向量查找
	Rank find(T const& e, Rank lo, Rank hi)const;
	Rank search(T const& e)const
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}//有序向量查找
	Rank search(T const& e, Rank lo, Rank hi)const;
	//可写访问接口
	T& operator[](Rank r)const;	//重载下标操作符[]
	Vector<T>& operator=(Vector<T>const&);//重载=
	T remove(Rank r);
	int remove(Rank lo, Rank hi);
	Rank insert(Rank r, T const& e);//插入元素
	Rank insert(T const& e) { return insert(_size, e); }
	void sort(Rank lo, Rank hi);
	void sort() { sort(0, _size); }
	void unsort(Rank lo, Rank hi);//置乱
	void unsort() { sort(0, _size); }
	int deduplicate();//无序去重
	int uniquify();//有序去重
				   //遍历
	void traverse(void(*)(T&));//遍历（使用函数指针，只读或局部修改）
	template <typename VST> void traverse(VST&);
};

template <typename T> void Vector<T>::copyForm(T const* A, Rank lo, Rank hi) {//从A[lo,hi)复制向量
	_elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;//分配空间，规模清零
	while (lo < hi)
		_elem[_size++] = A[lo++];
}

template <typename T> Vector<T>& Vector<T>::operator=(Vector<T>const& V) {//重载=
	if (_elem) delete[]_elem;//释放原内容
	copyForm(V._elem, 0, V._size);
	return *this;//返还当前对象的引用，以便链式赋值
}

template <typename T> void Vector<T>::expand() {//扩容，容量加倍，申请新区
	if (_size < _capacity) return;
	if (_capacity < DEFAUL_CAPACITY) _capacity = DEFAUL_CAPACITY;
	T* oldelem = _elem; _elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[]oldelem;
}

template <typename T> void Vector<T>::shrink() {//缩容，阈值25%
	if (_size << 2 > _capacity) return;
	if (_capacity < DEFAUL_CAPACITY << 1) return;
	T* oldelem = _elem; _elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[]oldelem;
}

template <typename T> T& Vector<T>::operator[](Rank r)const//重载下标操作符[]
{
	return _elem[r];
}

template <typename T> void permute(Vector<T>& V) {//随机置乱
	for (int i = V.size(); i > 0; i--)
		swap(V[i - 1], V[rand() % i]);
}

template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) {//区间随机置乱
	T* V = _elem + lo;//将_elem[lo,hi)视为V[0,hi-lo)方便
	for (int i = lo - hi; i > 0; i--)
		swap(V[i - 1], V[rand() % i]);
}

template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }
template <typename T> static bool lt(T& a, T& b) { return a<b; }
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); }
template <typename T> static bool eq(T& a, T& b) { return a == b; }

template<typename T> Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {//无序查找，蛮力
	while ((lo < hi--) && (e != _elem[hi])) return hi;
}

template<typename T> Rank Vector<T>::insert(Rank r, T const & e) {//将e作为Rank r插入
	expand();
	for (int i = _size; i > r; i--) _elem[i] = _elem[i - 1];
	_elem[r] = e; _size++;
	return r;
}

template<typename T>int Vector<T>::remove(Rank lo, Rank hi) {//删除区间[lo,hi)
	if (lo == hi) return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];//[hi,_size)前移hi-lo
	_size = lo;
	shrink();
	return hi - lo;
}

template<typename T>T Vector<T>::remove(Rank r) {//删除Rank r元素
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template <typename T> int Vector<T>::deduplicate() { //删除无序向量中重复元素
	int oldSize = _size;
	Rank i = 1;
	while (i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	return oldSize - _size;
}

template<typename T>void Vector<T>::traverse(void(*visit)(T &))//遍历向量，函数指针机制
{
	for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template<typename T> template<typename VST>//元素类型、操作器
void Vector<T>::traverse(VST & visit)//函数对象机制
{
	for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template<typename T>int Vector<T>::disordered() const {//判sorted
	int n = 0;//计数器
	for (int i = 1; i < _size; i++)
		if (_elem[i - 1] > _elem[i]) n++;
	return n;//n=0==有序
}

template<typename T>int Vector<T>::uniquify() {//有序向量去重
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

template<typename T> static Rank binsearch(T* A, T const& e, Rank lo, Rank hi) {//二分查找（A)版
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

template<typename T> void Vector<T>::bubblesort(Rank lo, Rank hi) {//起泡排序
	while (!bubble(lo, hi--));
}

template<typename T> bool Vector<T>::bubble(Rank lo, Rank hi) {//单趟扫描
	bool sorted = true;
	while (++lo<hi)
		if (_elem[lo - 1] > elem[lo]) {
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	return sorted;
}

template<typename T> void Vector<T>::mergesort(Rank lo, Rank hi) {//归并排序
	if (hi - lo < 2) return; //拆分至单元格，自然有序...
	int mi = (hi + lo) >> 1;
	mergesort(lo, mi); merge(mi, hi);
	merge(lo, mi, hi);
}

template<typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {//有序向量的归并实现
	T* A = _elem + lo;//定义了一个Vector A，理解为指针A指向_elem[lo],则A[0,hi-lo)=_elem[lo,hi)
	int lb = mi - lo; T* B = new T[lb];//B[0,lb)=_elem[lo,mi)
	for (Rank i = 0; i < lb; B[i] = A[i++]);
	int lc = hi - mi; T* C = _elem + mi;//Cmi~hi
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (B[j] > C[k]))) A[i++] = C[k++];
	}
	delete[]B;
}