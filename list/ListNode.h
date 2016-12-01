
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