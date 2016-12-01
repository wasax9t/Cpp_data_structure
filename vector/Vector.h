#pragma once
#include<iostream>
#include<cstring>
#include"..\Fib.h"
using namespace std;
typedef int Rank;//��
#define DEFAUL_CAPACITY 3//Ĭ�ϳ�ʼ����

template <typename T> class Vector {
protected:
	Rank _size; int _capacity; T* _elem;//��ģ(��С�������������ô�С����������
	void copyForm(T const* A, Rank lo, Rank hi);//������������A[lo,hi)
	void expand();//��������ʱ����
	void shrink();
	bool bubble(Rank lo, Rank hi);
	void bubblesort(Rank lo, Rank hi);
	Rank max(Rank lo, Rank hi);//ѡȡ���Ԫ��
	void selectionsort(Rank lo, Rank hi);
	void merge(Rank lo, Rank mi, Rank hi);//�鲢�㷨
	void mergesort(Rank lo, Rank hi);
	Rank partition(Rank lo, Rank hi);//��㹹���㷨
	void quicksort(Rank lo, Rank hi);
	void heapsort(Rank lo, Rank hi);//������
public:
	//���캯��
	Vector(int c = DEFAUL_CAPACITY, int s = 0, T v = 0)//����Ϊc����ģΪs������Ԫ�س�ʼ��Ϊv
	{
		_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
	}//s<=c
	Vector(T const* A, Rank n) { copyForm(A, 0, n); }//�������帴��
	Vector(T const* A, Rank lo, Rank hi) { copyForm(A, lo, hi); }
	Vector(Vector<T> const& V) { copyForm(V._elem, 0, V._size); }//�������帴��
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyForm(V._elem, lo, hi); }
	//��������
	~Vector() { delete[] _elem; }
	//ֻ�����ʽӿ�
	Rank size()const { return _size; }
	bool empty()const { return !_size; }//�п�
	int disordered()const;//�ж��Ƿ�������
	Rank find(T const& e)const { return find(e, 0, _size); }//������������
	Rank find(T const& e, Rank lo, Rank hi)const;
	Rank search(T const& e)const
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}//������������
	Rank search(T const& e, Rank lo, Rank hi)const;
	//��д���ʽӿ�
	T& operator[](Rank r)const;	//�����±������[]
	Vector<T>& operator=(Vector<T>const&);//����=
	T remove(Rank r);
	int remove(Rank lo, Rank hi);
	Rank insert(Rank r, T const& e);//����Ԫ��
	Rank insert(T const& e) { return insert(_size, e); }
	void sort(Rank lo, Rank hi);
	void sort() { sort(0, _size); }
	void unsort(Rank lo, Rank hi);//����
	void unsort() { sort(0, _size); }
	int deduplicate();//����ȥ��
	int uniquify();//����ȥ��
				   //����
	void traverse(void(*)(T&));//������ʹ�ú���ָ�룬ֻ����ֲ��޸ģ�
	template <typename VST> void traverse(VST&);
};
