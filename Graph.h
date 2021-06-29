#include <iostream>
#include <time.h>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
class Graph
{
	int V;  
	vector<vector<int>*> adj;

public:
	Graph(int V);
	void addEdge(int v, int w);
	void BFS(int s, vector<int>&dist);
	int is_isolated();
	int connectivity();
	int diameter();
	void clear();
};