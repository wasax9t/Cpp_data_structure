#include"Graph.h"

template<typename Tv,typename Te>//广度优先搜索算法BFS（全图）
void Graph<Tv, Te>::bfs(int s) {
	reset(); int clock = 0; int v = s;
	do
		if (UNDISCOVERED == status(v))
			BFS(v, clock);
	while (s != (v = (++v%n)));
}

template<typename Tv, typename Te>//广度优先搜索算法BFS（单个连通域）
void Graph<Tv, Te>::BFS(int v, int& clock) {
	Queue<int> Q;
	status(v) = DISCOVERED; Q.enqueue(v);
	while (!empty()) {
		int v = dequeue(); dTime(v) = ++clock;
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
			if (UNDISCOVERED == status(u)) {
				status(u) = DISCOVERED; Q.enqueue(u);
				type(v, u) = TREE; parent(u) = v;
			}
			else {
				type(v, u) = CROSS;
			}
		status(v) = VISITED;
	}
}

template<typename Tv, typename Te>//深度优先搜索算法BFS（全图）
void Graph<Tv, Te>::dfs(int s) {
	reset(); int clock = 0; int v = s;
	do
		if (UNDISCOVERED == status(v))
			DFS(v, clock);
	while (s != (v = (++v%n)));
}

template<typename Tv, typename Te>//深度优先搜索算法BFS
void Graph<Tv, Te>::DFS(int v, int& clock) {
	dTime(v) = ++clock; status(v) = DISCOVERED;
	for (int u = fristNbr(v); -1 < u; u = nextNbr(v, u))
		switch (status(u)) {
		case UNDISCOVERED:type(v, u) = TREE; parent(u) = v; DFS(u, clock); break;
		case DISCOVERED:type(v, u) = BACKWORD; break;
		default:type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
		}
	status(v) = VISITED; fTime(v) = ++clock;
}

template<typename Tv, typename Te>//基于DFS的拓扑排序算法
Stack<Tv>* Graph<Tv, Te>::tSort(int s) {
	reset(); int clock = 0; int v = s;
	Stack<Tv>* S = new Stack<Tv>;
	do {
		if (UNDISCOVERED == status(v))
			if (!TSort(v, clock, S)) {
				while (!S->empty())
					S->pop(); break;
			}
	} while (s != (v = (++v%n)));
	return S;
}

template<typename Tv, typename Te>//基于DFS的拓扑排序算法（单趟）
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S) {
	dTime(v) = ++clock; status(v) = DISCOVERED;
	for (int u = fristNbr(v); -1 < u; u = nextNbr(v, u))
		switch (status(u)) {
		case UNDISCOVERED:
			type(v, u) = TREE; parent(u) = v;
			if (!TSort(u, clock, S)) return false;
			break;
		case DISCOVERED:
			type(v, u) = BACKWORD; return false;
		default:type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
		}
	status(v) = VISITED; S->push(vertex(v));
	return true;
}

template<typename Tv, typename Te>//深度优先搜索算法BFS（全图）
void Graph<Tv, Te>::bbc(int s) {
	reset(); int clock; int v = s; Stack<int> S;
	do
		if (UNDISCOVERED == status(v)) {
			BBC(v, clock, S);
			S.pop();
		}
	while (s != (v = (++v%n)));
}

