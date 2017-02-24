#pragma once
#ifndef ADJACENCYLIST
#define ADJACENCYLIST
#include <list>
#include <vector>
#include <iostream>
using namespace std;

class vertex;										// class declaration

#define OUTOFBOUNDS	  1								// Attempt to access index out of bounds (unexisting vertex; edge connecting one or two unexsting vertex; etc.)	
#define EDGEDUPLICATE 2								// Attempt to add duplicate edge to vertex edge list

class edge {										// EDGE CLASS: represents path between two vertices
private:
	vertex *adjacent[2];							// Stores pointers to the two vertices connected by this edge
	int	weight;										// The weight value to traverse this edge
protected:
public:
	edge(vertex *A, vertex *B, int w);				// create edge object
	vertex** getEndPoints();						// return end points (pointers to two connected vertices)
	vertex* getNeighbour(vertex* startingVert);		// return neighbour (given one of the end points, return the other of this edge)
	int getWeight();								// return weight of current edge
	void displayEdgeInfo();							// display edge information (weight, index of two connected vertices)
};

class vertex {										// VERTEX CLASS: represents a position (often called node) in the graph
private:
	int vertexIndex;								// identifier of a vertex
	list<edge *> *edgeList;							// pointer to list of edges of current vertex. Neighbouring nodes are being pointed at by these edges
	double gCost;									// A* supporting variable; g contains the overall path cost from starting node to this vertex
	double hCost;									// A* supporting variable; h contains the value of the heuristic
	pair <int, int> vertexCoords;					// Coordinates of vertex in the graph
	vertex* parent;									// A* supporting variable; points to previous vertex visited in the current path
protected:
public:
	vertex(int index, pair<int, int> coords);		// create vertex object
	void displayVertexInfo();						// display vertex information
	int getIndex();									// return index number of the current vertex
	bool addEdge(edge *e);							// add edge to current vertex's edge list
	list<edge *> *getEdgeList();					// return the edge list of the current vertex
	void displayEdgeList();							// display list of edges and corresponding neighbours
	double getfCost();								// return f cost (calculated as sum of g + h values)
	double getgCost();								// return g cost (overall path cost)
	double gethCost();								// return h cost (heuristic)
	void setgCost(double _g);						// set overall path value g
	void sethCost(double _h);						// set heuristic value h 
	pair<int, int> getCoords();						// return coordinates of current vertex
	void setParent(vertex* _parent);				// set parent of current vertex
	vertex* getParent();							// return the parent of current vertex
};

class AdjacencyList {								// ADJACENCY LIST: data structure to contain graph data
private:
	int vertexNo;									// Overall number of vertices in the graph
	int edgeNo;										// Overall number of edges in the graph
	vector<vertex *> *vertices;						// Container of all vertices for quick access
protected:
public:
	AdjacencyList();								// create adjacency list object
	void addVertex(vertex *v);						// add vertex to adjacency list
	void addEdge(edge *e);							// add edge to edge list of BOTH vertices it connects
	vertex* getVertex(int index);					// return vertex at given index
	void displayVertices();							// display elements of the adjacency list (vertices and edges)
	void resetCosts();								// reset g and h costs for (e.g. for a second search)
};
#endif

//TODO: fix references
//// http://softwareengineering.stackexchange.com/questions/148313/what-is-the-most-space-efficient-way-to-implement-a-graph-data-structure // how to represent a graph
//// https://en.wikipedia.org/wiki/Graph_(abstract_data_type) // Why choose and Adj List
// http://stackoverflow.com/questions/12599143/what-is-the-distinction-between-sparse-and-dense-graphs // Sparse, as O(~2n) = O(n) hence sparse
/// http://www.redblobgames.com/pathfinding/a-star/implementation.html
// Useful for general idea, a* (although used differently
//// http://www.cplusplus.com/forum/beginner/118340/ // Weighted graphs intro
///
//* -- https://en.wikipedia.org/wiki/Adjacency_list --

/*
* SPARSE GRAPH
* https://en.wikipedia.org/wiki/Adjacency_list
* Goodrich and tamassia adjacency list
*/
