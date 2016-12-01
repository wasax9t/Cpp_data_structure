#include<fstream>
typedef int Rank;
#define Posi(T) ListNode<T>*

template <typename T> struct ListNode {
	//成员
	T data; Posi(T) pred; Posi(T) succ;
	//构造函数
	ListNode(){}
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
		:date(e), pred(p), suss(s) {}
	//操作接口
	Posi(T) insertAsPred(T const& e); //在当前节点前插入
	Posi(T) insertAsSucc(T const& e); //在当前节点后插入
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

