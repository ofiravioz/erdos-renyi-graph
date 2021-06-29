#include "Graph.h"
Graph::Graph(int V)
{
	this->V = V;
	for (int i = 0; i < V; i++)
	{
		adj.push_back(new vector<int>());//create new vector for each V
	}
}

void Graph::addEdge(int v, int n)
{
	adj[v]->push_back(n);
	adj[n]->push_back(v);
}
void Graph::clear()
{
	for (int i = 0; i < 1000; i++) { delete adj[i]; }//delete previous vector to save memory
}
void build_random_graph(double p, int V, Graph& G)
{
	int vertex , nighbor, rand_num, probability = 1000 * p;//probability *1000 to compare random number
	srand(time(0));//zero time to make sure numbers are random
	for (vertex = 0; vertex < V; vertex++)
	{
		for (nighbor = vertex + 1; nighbor < V; nighbor++)
		{
			rand_num = (rand() % 1000)+1;//random number between 1-1000
			if (rand_num < probability) { G.addEdge(vertex, nighbor); }/*if probability recived 
																	   is higher the number creat new edge*/
		}
	}
}

void Graph::BFS(int s,vector<int>& dist)
{
	vector<bool> visited = vector<bool>(V, false);
	queue<int> q;// new queue
	vector<int>::iterator i;//new iterator to run on the list 
	visited[s] = true;//mark currend node as visited 
	dist[s] = 0;
	q.push(s);
	vector<int> &inner_graph = *adj[s];
	while (!q.empty())
	{
		if (inner_graph.size() == 0) { break; }
		else
		{
			s = q.front();
			vector<int> &inner_graph = *adj[s];
			q.pop();
			for (i = inner_graph.begin(); i != inner_graph.end(); i++)//check all the nighbors to the starting point
			{
				if (!visited[*i])
				{
					visited[*i] = true;//mark as visited
					dist[*i] = dist[s] + 1;
					q.push(*i);
				}
			}
		}
	}
}
int Graph::is_isolated()
{
	for (int i = 0; i < V; i++)
	{
		vector<int> &inner_graph = *adj[i];
		if (inner_graph.size()==0){return 1;}//if the list in location i has 0 size its isolated
	}
	return 0;
}
int Graph::connectivity()
{
	vector<int> dist = vector<int>(V, -1);
	BFS(0,dist);//send array starting point current diameter and max diameter found 
	for (int i = 0; i < V; i++)
	{
		if (dist[i]==-1){return 0;}//if you havent visited 1 of the nodes then graph is not connected
	}
	return 1;
}
int Graph::diameter()
{
	int vertex, i ,diam=0;

	for (vertex =0; vertex < V; vertex++)
	{
		vector<int> dist = vector<int>(V, -1);
		BFS(vertex, dist);	
		for (i = 0; i < V; i++)
		{
			if (dist[i] == -1) { return 10; }/*if graph is not connected then diameter is infinity
											we will mark it as 10>2*/
			if (diam < dist[i]) { diam = dist[i]; } 
		}

	}
	return diam;
	
}

void create_csv_file(string file_name, float output[10][2]) {
	fstream fout;
	int i;

	fout.open(file_name, ios::out | ios::app);

	fout << "p,";   // first row shows the probabilities
	for (i = 0; i < 10; i++)
		fout << output[i][0] << ", ";
	fout << "\n";

	fout << "probability for attribute, ";   // second row shows the probability of the attribute
	for (i = 0; i < 10; i++)
		fout << output[i][1] << ", ";
	fout << "\n";

	fout.close();
}
void isolated_file(float p[3][10], int num,int V)//export data to csv + simulation
{
	string name = "is_isolated.csv";
	float output[10][2], success;
	int x;
	cout <<"is isolated test " << endl;
	for (int i = 0; i < 10; i++)
	{
		success = 0;
		for (int j = 0; j < num; j++)
		{
			Graph g(V);
			build_random_graph(p[2][i], V, g);
			x = g.is_isolated();
			if (x == 1) { success++; }//check if there is isolated node
			g.clear();
		}
		cout << "finished graph " << i << endl;
		cout << "p is " << p[2][i] << endl;
		cout << "the probability is " << success / (float)num << endl;
		output[i][0] = p[2][i];
		output[i][1] = success / (float)num;
	}
	create_csv_file(name, output);
}
void connectivity_file(float p[3][10], int num, int V)//export data to csv + simulation
{
	string name = "connectivity.csv";
	float output[10][2], success;
	int x;
	cout << "connectivity test " << endl;
	for (int i = 0; i < 10; i++)
	{
		success = 0;
		for (int j = 0; j < num; j++)
		{
			Graph g(V);
			build_random_graph(p[0][i], V, g);
			x = g.connectivity();
			if (x == 1) { success++; }//check if graph is connected
			g.clear();
		}
		cout << "finished graph " << i << endl;
		cout << "p is " << p[0][i] << endl;
		cout << "the probability is " << success / (float)num << endl;
		output[i][0] = p[0][i];
		output[i][1] = success / (float)num;
	}
	create_csv_file(name, output);
}
void  diameter_file(float p[3][10], int num, int V)//export data to csv + simulation
{
	string name = "diameter.csv";
	float output[10][2], success;
	int x;
	cout << "diameter test " << endl;
	for (int i = 0; i < 10; i++)
	{
		success = 0;
		for (int j = 0; j < num; j++)
		{
			Graph g(V);
			build_random_graph(p[1][i], V, g);
			 x = g.diameter();
			 if (x == 2) { success++; }//check if diameter equals 2
			 g.clear();
		}
		cout << "finished graph " << i << endl;
		cout << "p is " << p[1][i] << endl;
		cout << "the probability is " << success / (float)num << endl;
		output[i][0] = p[1][i];
		output[i][1] = success / (float)num;
	}
	create_csv_file(name, output);
}
int main()
{
	float p[3][10] = 
	{
		{0.001,0.002,0.003,0.004,0.005,0.008,0.009,0.01,0.011,0.012},//connetivity
		{0.09,0.095,0.01,0.105,0.114,0.12,0.125,0.13,0.135,0.14},//diameter
		{0.001,0.002,0.003,0.004,0.005,0.008,0.009,0.01,0.011,0.012}//isolated
	};
	connectivity_file(p, 500, 1000);
	isolated_file(p, 500, 1000);
	diameter_file(p, 500, 1000);
}
