#ifndef ADJACENCYMATRIX
#define ADJACENCYMATRIX

#include <vector>
#include <iostream>
using namespace std;

class AdjacencyMatrix
{
	// http://www.sanfoundry.com/cpp-program-implement-adjacency-matrix/
	// http://mathworld.wolfram.com/AdjacencyMatrix.html
private:
	int n;
	//http://www.eskimo.com/~scs/cclass/int/sx8.html
	std::pair <int, int> **adj;
	//	int **adj;
	bool *visited;
public:
	//AdjacencyMatrix(int n){
	//	this->n = n;
	//	visited = new bool[n];
	//	adj = new int*[n];
	//	for (int i = 0; i < n; i++){
	//		adj[i] = new int[n];
	//		for (int j = 0; j < n; j++)
	//			adj[i][j] = 0;
	//	}
	//}
	AdjacencyMatrix(int n);
	/*
	/*
	* Adding Edge to Graph
	*/
	void add_edge(int origin, int destin, int weight);
	/*
	* Print the graph
	*/
	void display();
	void displayOnlyEdges();
};

#endif