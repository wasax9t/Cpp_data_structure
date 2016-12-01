
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