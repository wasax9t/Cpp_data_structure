#include"ListNode.h"

template <typename T> class List {

private:
	int _size; Posi(T) header; Posi(T) trailer;//��ģ��ͷ�ڱ���β�ڱ�

protected:
	void init();
	int clear();
	void copyNodes(Posi(T) p, int n);
	void merge(Posi(T)& p, int n, List<T>& L, Posi(T) q, int m);
	void mergesort(Posi(T)& p, int);
	void selectionsort(Posi(T) p, int n);
	void insertionsort(Posi(T) p, int n);

public:
	List() { init(); }
	List(List<T> const& L) { copyNodes(L.frist(), L._size); }
	List(List<T> const& L, Rank r, int n) { copyNodes(L[r], n); }
	List(Posi(T) p, int n) { copyNodes(p, n); }
	~List() { clear(); delete header; delete trailer; }
	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	T& operator[] (Rank r) const;//���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
	Posi(T) frist() const { return header->suss; }
	Posi(T) last() const { return trailer->pred; }
	bool valid(Posi(T) p)
	{
		return p && (trailer != p) && (header != p);
	}
	int dissordered() const;//�ж�������
	Posi(T) find(T const& e, int n, Posi(T) p)const;//�������
	Posi(T) find(T const& e)const { return find(e, _size, trailer); }
	Posi(T) search(T const& e)const { return search(e, _size, trailer); }
	Posi(T) search(T const& e, int n, Posi(T) p)const;
	Posi(T) selectmax(Posi(T) p, int n);
	Posi(T) selectmax() { return selectMax(header->succ, _size); }
	Posi(T) insertAsfrist(T const&e);
	Posi(T) insertAslast(T const&e);
	Posi(T) insertpred(Posi(T) p, T const&e);
	Posi(T) insertsuss(Posi(T) p, T const&e);
	T remove(Posi(T) p);
	void merge(List<T>& L) { merge(frist(), size, L, L.frist, L._size); }//ȫ�б�鲢
	void sort(Posi(T) p, int n);
	void sort() { sort(frist(), _size); }
	int deduplicate();
	int uniquify();
	//����
	void traverse(void(*visit)(T&)) {
		for (Posi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
	}
	template<typename VST> void traverse(VST& visit) {
		for (Posi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
	}
};

