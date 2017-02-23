#pragma once
#ifndef ADJACENCYLIST
#define ADJACENCYLIST
#include <list>
#include <vector>
#include <iostream>
using namespace std;

//TODO: fix references
//// http://softwareengineering.stackexchange.com/questions/148313/what-is-the-most-space-efficient-way-to-implement-a-graph-data-structure // how to represent a graph
//// https://en.wikipedia.org/wiki/Graph_(abstract_data_type) // Why choose and Adj List
// http://stackoverflow.com/questions/12599143/what-is-the-distinction-between-sparse-and-dense-graphs // Sparse, as O(~2n) = O(n) hence sparse
/// http://www.redblobgames.com/pathfinding/a-star/implementation.html
// Useful for general idea, a* (although used differently
//// http://www.cplusplus.com/forum/beginner/118340/ // Weighted graphs intro
///
//* -- https://en.wikipedia.org/wiki/Adjacency_list --
// * The object oriented incidence list structure suggested by Goodrich and Tamassia has special classes of vertex objects and edge objects. 
// * Each vertex object has an instance variable pointing to a collection object that lists the neighboring edge objects. 
// * In turn, each edge object points to the two vertex objects at its endpoints. 
// * This version of the adjacency list uses more memory than the version in which adjacent vertices are listed directly, 
// * but the existence of explicit edge objects allows it extra flexibility in storing additional information about edges.*/
//
class vertex; // class declaration

#define OUTOFBOUNDS	  1 // Attempt to access index out of bounds (unexisting vertex; edge connecting one or two unexsting vertex; etc.)	
#define EDGEDUPLICATE 2 // Attempt to add duplicate edge to vertex edge list

class edge {
private:
	vertex *adjacent[2];
	int	weight;
protected:
public:
	edge(vertex *A, vertex *B, int w);
	vertex** getEndPoints();
	vertex* getNeighbour(vertex* startingVert);
	int getWeight();
	void displayEdgeInfo();
};

class vertex {
private:
	int vertexIndex;
	list<edge *> *edgeList; // std::forward_list instead? Is difference Noticeable?
	double gCost, hCost;
	pair <int, int> vertexCoords;
	vertex* parent;
protected:
public:
	vertex(int index, pair<int, int> coords);
	void displayVertexInfo();
	int getIndex();
	bool addEdge(edge *e);
	list<edge *> *getEdgeList();
	void displayEdgeList();
	double getfCost();
	double getgCost();
	double gethCost();
	void setgCost(double _g);
	void sethCost(double _h);
	pair<int, int> getCoords();
	void setParent(vertex* _parent);
	vertex* getParent();
};

class AdjacencyList {
private:
	int vertexNo;
	int edgeNo;
	vector<vertex *> *vertices;
protected:
public:
	AdjacencyList();
	void addVertex(vertex *v);
	void addEdge(edge *e);
	vertex* getVertex(int index);
	void displayVertices();
	void resetCosts();
};

#endif