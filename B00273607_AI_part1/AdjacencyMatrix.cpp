#include "AdjacencyMatrix.h"
AdjacencyMatrix::AdjacencyMatrix(int n) {
	this->n = n;
	visited = new bool[n];
	adj = new std::pair<int, int>*[n];
	for (int i = 0; i < n; i++) {
		adj[i] = new std::pair<int, int>[n];
		for (int j = 0; j < n; j++) {
			adj[i][j].first = 0;

		}
	}
}
/*
/*
* Adding Edge to Graph
*/
void AdjacencyMatrix::add_edge(int origin, int destin, int weight) {
	if (origin > n || destin > n || origin < 0 || destin < 0)
		cout << "Invalid edge!\n";
	else if (adj[origin - 1][destin - 1].first == 1)
		cout << "edge [" << origin << " to " << destin << "] already exists (This is an undirected graph)\n";
	else {
		adj[origin - 1][destin - 1].first = 1; // INSTEAD OF THIS I MAKE PAIR :thinking:
		adj[destin - 1][origin - 1].first = 1;
		adj[origin - 1][destin - 1].second = weight;
		adj[destin - 1][origin - 1].second = weight;
	}
}
/*
* Print the graph
*/
void AdjacencyMatrix::display() {
	int i, j;
	for (i = 0;i < n;i++) {
		for (j = 0; j < n; j++)
			cout << "[" << i + 1 << "<->" << j + 1 << "]" << adj[i][j].first << "[w:" << adj[i][j].second << "]  ";
		cout << endl;
	}
}
void AdjacencyMatrix::displayOnlyEdges() {
	int i, j;
	for (int i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (adj[i][j].first != 0)
				cout << "[" << i + 1 << "<->" << j + 1 << "]" << adj[i][j].first << "[w:" << adj[i][j].second << "]  ";
		}
		cout << endl;
	}
}
