#ifndef GRAPH
#define GRAPH
#include <list>
#include <vector>
#include <iostream>
using namespace std;
//template <typename vertex>
// rather use integers

//class graph {
//protected:
//	virtual void addEdge(int, int) = 0;
//	virtual int countNodes() const = 0;
//	//given a vertex return list of vertex's adjacent to it
//	virtual std::list<vertex> adjacent(int) = 0;
//	std::vector<vertex> nodeList;
//private:
//	int numNodes;
//
//};

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

/* The object oriented incidence list structure suggested by Goodrich and Tamassia has special classes of vertex objects and edge objects. 
 * Each vertex object has an instance variable pointing to a collection object that lists the neighboring edge objects. 
 * In turn, each edge object points to the two vertex objects at its endpoints. 
 * This version of the adjacency list uses more memory than the version in which adjacent vertices are listed directly, 
 * but the existence of explicit edge objects allows it extra flexibility in storing additional information about edges.*/

class edge;

class vertex {
private:
	int vertexIndex;
	std::pair <int, int> vertexCoords;
	std::list<edge> *edgeList; // std::forward_list  ?
protected:
public:
	vertex(int index, std::pair<int,int> coords) {
		this->vertexIndex = index;
		this->vertexCoords = coords;
		edgeList = new std::list<edge>;
//		cout << this->vertexCoords.first << " - " << this->vertexIndex;
	}
};

class edge {
private:
	vertex *adjacent[2];
	int weight;
protected:
public:
	edge(vertex A, vertex B) {
		adjacent[0] = &A;
		adjacent[1] = &B;
	}
};


class AdjacencyList {
private:
	int vertexNo;
	int edgeNo;
	std::vector<vertex> *vertices;
protected:
public:
	AdjacencyList() {

	}
	// returns
	bool addVertex(vertex v) {
		return false;
	}
	// returns
	bool addEdge(edge e) {
		return false;
	}
	bool areAdjacent(vertex v, vertex w) {
		return false;
	}

	// if vertices <= 1 don't

};

#endif