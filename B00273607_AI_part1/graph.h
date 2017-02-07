#ifndef GRAPH
#define GRAPH
#include <list>
#include <vector>
#include <iostream>
using namespace std;
template <typename vertex>
// rather use integers

class graph {
protected:
	void addEdge(int, int) = 0;
	int countNodes() const = 0;
	//given a vertex return list of vertex's adjacent to it
	virtual std::list<vertex> adjacent(int) = 0;
	std::vector<vertex> nodeList;
private:
	int numNodes;

};

// https://en.wikipedia.org/wiki/DOT_(graph_description_language)
// http://stackoverflow.com/questions/28313901/how-to-parse-a-dot-file-in-python
// http://www.graphviz.org/content/how-use-graphviz-library-c-project
// http://www.cplusplus.com/forum/lounge/65474/
// http://www.cplusplus.com/forum/beginner/65178/
// http://www.cplusplus.com/doc/tutorial/files/
// http://www.cplusplus.com/reference/fstream/ofstream/
// http://softwareengineering.stackexchange.com/questions/148313/what-is-the-most-space-efficient-way-to-implement-a-graph-data-structure
// http://www.redblobgames.com/pathfinding/a-star/implementation.html
// http://www.cplusplus.com/articles/2LywvCM9/
// http://www.cplusplus.com/forum/beginner/118340/
// http://www.cplusplus.com/forum/general/41244/
// http://www.sanfoundry.com/cpp-program-implement-adjacency-matrix/
// http://stackoverflow.com/questions/2893129/what-does-mean-in-c

class AdjacencyMatrix
{
	// http://mathworld.wolfram.com/AdjacencyMatrix.html
private:
	int n;
	int **adj;
	bool *visited;
public:
	AdjacencyMatrix(int n){
		this->n = n;
		visited = new bool[n];
		adj = new int*[n];
		for (int i = 0; i < n; i++){
			adj[i] = new int[n];
			for (int j = 0; j < n; j++)
				adj[i][j] = 0;
		}
	}
	/*
	* Adding Edge to Graph
	*/
	void add_edge(int origin, int destin){
		if (origin > n || destin > n || origin < 0 || destin < 0)
			cout << "Invalid edge!\n";
		else
			adj[origin - 1][destin - 1] = 1; // INSTEAD OF THIS I MAKE PAIR :thinking:
	}
	/*
	* Print the graph
	*/
	void display()
	{
		int i, j;
		for (i = 0;i < n;i++){
			for (j = 0; j < n; j++)
				cout << adj[i][j] << "  ";
			cout << endl;
		}
	}
};
#endif