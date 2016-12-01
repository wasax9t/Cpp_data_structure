#pragma once
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWORD } EType;

template<typename Tv, typename Te>
class Graph {
private:
	void reset() {
		for (int i = 0; i < n; i++) {
			status(i) = UNDISCOVERED; dTime(i) = fTime(i) = -1;
			parent(i) = -1; priority(i) = INT_MAX;
			for (int j = 0; j < n; j++)
				if (exists(i, j))type(i, j) = UNDETERMINED;
		}
	}
	void bfs(int s);
	
	void dfs(int s);
	
	Stack<Tv>* tSort(int s);
	bool TSort(int v, int & clock, Stack<Tv>* S);
	
public:
	int n;//vertex count
	int e;//edge count
	void BFS(int, int&);
	void DFS(int, int&);
	void BCC(int, int&, Stack<Tv>*);
};