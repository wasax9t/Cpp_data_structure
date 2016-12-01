#pragma once
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
