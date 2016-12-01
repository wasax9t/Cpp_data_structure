#pragma once
#include"..\stack&queue\Stack.h"
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWORD } EType;

template<typename Tv, typename Te>
class Graph {
private:
	void reset();
	void bfs(int s);
	
	void dfs(int s);
	
	Stack<Tv>* tSort(int s);
	bool TSort(int v, int & clock, Stack<Tv>* S);

	void bbc(int s);
	
public:
	int n;//vertex count
	int e;//edge count
	void BFS(int, int&);
	void DFS(int, int&);
	void BCC(int, int&, Stack<Tv>*);
};