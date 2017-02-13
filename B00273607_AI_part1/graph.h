#ifndef GRAPH
#define GRAPH
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
class vertex;

class edge {
private:
	vertex *adjacent[2];
	int		weight;
protected:
public:
	edge(vertex *A, vertex *B, int w);
	vertex** getEndPoints();
	int getWeight();
	void displayEdgeInfo();
};

class vertex {
private:
	int vertexIndex; // unnecessary, but supports change to name of vertex
	std::pair <int, int> vertexCoords;
	std::list<edge *> *edgeList; // std::forward_list  ?
protected:
public:
	vertex(int index, std::pair<int, int> coords);
	vertex();
	void displayVertexInfo();
	int getIndex();
	bool addEdge(edge *e);
	void displayEdgeList();
};

// I NEED DELETOS
class AdjacencyList {
private:
	int vertexNo;
	int edgeNo;
	std::vector<vertex *> *vertices;
protected:
public:
	AdjacencyList() {
		// initialize collection
		vertices = new std::vector<vertex *>;
		vertexNo = 0;
		edgeNo = 0;
	}
	// returns
	bool addVertex(vertex *v) {
		// add a vertex to vector
		// we will assume vertices don't take the same position
		vertices->push_back(v);
		vertexNo++;
		cout << "Vertex added\n";
		return true;

	//	return false;
	}
//	 returns
	bool addEdge(edge *e) {
		// Assumes you won't try to enter the same edge twice
		std::vector<vertex *>::iterator vectorIterator = this->vertices->begin();
		vertex* endPointA = new vertex();
		vertex* endPointB = new vertex();
		int endPointsFound = 0;
		while (vectorIterator != this->vertices->end() || endPointsFound == 2){
			if (((vertex*)*vectorIterator)->getIndex() == e->getEndPoints()[0]->getIndex())
			{
				endPointA = ((vertex*)*vectorIterator);
				endPointsFound++;
			}
			else if (((vertex*)*vectorIterator)->getIndex() == e->getEndPoints()[1]->getIndex())
			{
				endPointB = ((vertex*)*vectorIterator);
				endPointsFound++;
			}
			else
				vectorIterator++;
		}
		if (endPointsFound < 2) {
			delete endPointA;
			delete endPointA;
			return false;
		}
		else {
			endPointA->addEdge(e);
			endPointB->addEdge(e);
			delete endPointA;
			delete endPointA;
			return true;
		}
		/*for (std::vector<vertex *>::iterator vectorIterator = this->vertices->begin();
		vectorIterator != this->vertices->end();
			++vectorIterator) {*/
		/*	((vertex*)*vectorIterator)->getIndex();
			e->getEndPoints()[0]->getIndex();
			e->getEndPoints()[1]->getIndex();*/
		/*}*/
		//	((vertex*)&vertices[i])->getIndex(); //???
		// go to vertices
		// add edge to both
		// check if either of end points is vertex, otherwise false
	//	return false;
	}
	bool areAdjacent(vertex v, vertex w) {
		// if one of edges contains both vertices
		return false;
	}
	void displayVertices() {
		for (std::vector<vertex *>::iterator vectorIterator = this->vertices->begin();
			vectorIterator != this->vertices->end();
			++vectorIterator) {
			cout << "|| Vertex info ||\n";
			((vertex*)*vectorIterator)->displayVertexInfo();
			cout << "|| Edge list ||\n";
			((vertex*)*vectorIterator)->displayEdgeList();
		}
	}
//	 if vertices <= 1 don't
};

#endif