#pragma once
#include"..\stack&queue\Stack.h"
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWORD } EType;

template<typename Tv, typename Te>
class Graph {
	//²»·â×°ÁË
	void reset();
	void bfs(int s);
	void BFS(int, int&);
	void dfs(int s);
	void DFS(int, int&);
	Stack<Tv>* tSort(int s);
	bool TSort(int v, int & clock, Stack<Tv>* S);
	void bbc(int s);
	void BCC(int, int&, Stack<Tv>*);
	int n;//vertex count
	int e;//edge count
};