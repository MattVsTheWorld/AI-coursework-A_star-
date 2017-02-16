#ifndef ADJACENCYLIST
#define ADJACENCYLIST
#include <list>
#include <vector>
#include <iostream>
using namespace std;

//// template <typename vertex>
//// rather use integers
//
////class graph {
////protected:
////	virtual void addEdge(int, int) = 0;
////	virtual int countNodes() const = 0;
////	//given a vertex return list of vertex's adjacent to it
////	virtual std::list<vertex> adjacent(int) = 0;
////	std::vector<vertex> nodeList;
////private:
////	int numNodes;
////
////};
//
//// https://en.wikipedia.org/wiki/DOT_(graph_description_language)
//// http://stackoverflow.com/questions/28313901/how-to-parse-a-dot-file-in-python
//// http://www.graphviz.org/content/how-use-graphviz-library-c-project
//// http://www.cplusplus.com/forum/lounge/65474/
//// http://www.cplusplus.com/forum/beginner/65178/
//// http://www.cplusplus.com/doc/tutorial/files/
//// http://www.cplusplus.com/reference/fstream/ofstream/
//// http://softwareengineering.stackexchange.com/questions/148313/what-is-the-most-space-efficient-way-to-implement-a-graph-data-structure
//// http://www.redblobgames.com/pathfinding/a-star/implementation.html
//// http://www.cplusplus.com/articles/2LywvCM9/
//// http://www.cplusplus.com/forum/beginner/118340/
//// http://www.cplusplus.com/forum/general/41244/
//// http://www.sanfoundry.com/cpp-program-implement-adjacency-matrix/
//// http://stackoverflow.com/questions/2893129/what-does-mean-in-c
//
///* The object oriented incidence list structure suggested by Goodrich and Tamassia has special classes of vertex objects and edge objects. 
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
	int		weight;
protected:
public:
	edge(vertex *A, vertex *B, int w);
	vertex** getEndPoints();
	//vertex* getOtherEnd(vertex* startingVert);
	int getWeight();
	void displayEdgeInfo();
};

class vertex {
private:
	int vertexIndex; // unnecessary, but supports change to name of vertex
	pair <int, int> vertexCoords;
	list<edge *> *edgeList; // std::forward_list instead? Is difference Noticeable?
	
protected:	
//	list<edge *> *getEdgeList();
public:
	vertex(int index, pair<int, int> coords);
	void displayVertexInfo();
	int getIndex();
	bool addEdge(edge *e);
//	int getNeighours();
	void displayEdgeList();

	int getfCost() {
		return (this->gCost + this->hCost);
	}
	// +++
	int gCost, hCost;
};

// I NEED DELETOS
class AdjacencyList {
private:
	int vertexNo;
	int edgeNo;
	vector<vertex *> *vertices;
protected:
public:
	AdjacencyList();
	bool addVertex(vertex *v);
	bool addEdge(edge *e);
	//list
//	bool areAdjacent(vertex *v, vertex *w);
	vertex* getVertex(int index);
	void displayVertices();
};

#endif