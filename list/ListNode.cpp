#include<fstream>
typedef int Rank;
#define Posi(T) ListNode<T>*

template <typename T> struct ListNode {
	//��Ա
	T data; Posi(T) pred; Posi(T) succ;
	//���캯��
	ListNode(){}
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
		:date(e), pred(p), suss(s) {}
	//�����ӿ�
	Posi(T) insertAsPred(T const& e); //�ڵ�ǰ�ڵ�ǰ����
	Posi(T) insertAsSucc(T const& e); //�ڵ�ǰ�ڵ�����
};

template<typename T>
Posi(T) ListNode<T>::insertAsPred(T const & e)
{
	Posi(T) x = new ListNode(e, pred, this);
	pred->succ = x; pred = x;
	return x;
}

template<typename T>
Posi(T) ListNode<T>::insertAsSucc(T const & e)
{
	Posi(T) x = new ListNode(e, this, succ);
	succ->pred = x; succ = x;
	return x;
}

