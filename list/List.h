#include"ListNode.h"

template <typename T> class List {

private:
	int _size; Posi(T) header; Posi(T) trailer;//规模、头哨兵、尾哨兵

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
	T& operator[] (Rank r) const;//重载，支持循秩访问（效率低）
	Posi(T) frist() const { return header->suss; }
	Posi(T) last() const { return trailer->pred; }
	bool valid(Posi(T) p)
	{
		return p && (trailer != p) && (header != p);
	}
	int dissordered() const;//判断已排序
	Posi(T) find(T const& e, int n, Posi(T) p)const;//无序查找
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
	void merge(List<T>& L) { merge(frist(), size, L, L.frist, L._size); }//全列表归并
	void sort(Posi(T) p, int n);
	void sort() { sort(frist(), _size); }
	int deduplicate();
	int uniquify();
	//遍历
	void traverse(void(*visit)(T&)) {
		for (Posi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
	}
	template<typename VST> void traverse(VST& visit) {
		for (Posi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
	}
};

