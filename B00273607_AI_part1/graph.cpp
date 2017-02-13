#include "graph.h"

/////////////////
//// <<EDGE ////
////////////////

edge::edge(vertex *A, vertex *B, int w) {
	adjacent[0] = A; // assign pointers to vertex
	adjacent[1] = B;
	weight = w;
}
//	 JESUS CHRIST IT'S A POINTER TO POINTER
//	 NO WAIT IT'S NOT
//	 WHAT IS IT
vertex** edge::getEndPoints() {
	return this->adjacent;
}

int edge::getWeight() {
	return this->weight;
}

void edge::displayEdgeInfo() {
	//	 WORKS NOW!!!
	cout << ">Edge with weight: " << this->weight << endl;
	cout << "Edge connects vertex [" << this->adjacent[0]->getIndex() << "]\n";
	this->adjacent[0]->displayVertexInfo();
	cout << "And vertex [" << this->adjacent[1]->getIndex() << "]\n";
	this->adjacent[1]->displayVertexInfo();
}

/////////////////
//// >>EDGE ////

////////////////
///////////////////
//// <<VERTEX ////
//////////////////
vertex::vertex(int index, std::pair<int, int> coords) {
	this->vertexIndex = index;
	this->vertexCoords = coords;
	edgeList = new std::list<edge *>; // :thinking:
//	cout << "Coords of added: " <<  this->vertexCoords.first << " - " << this->vertexCoords.second << endl;
}
vertex::vertex() {
	;
}
void vertex::displayVertexInfo() {
	cout << "Index: [" << this->vertexIndex << "] ";
	cout << "Coords: [" << this->vertexCoords.first << "," << this->vertexCoords.second << "]\n";
}

int vertex::getIndex() {
	return this->vertexIndex;
}
bool vertex::addEdge(edge *e) {
	for (std::list<edge *>::iterator listIterator = this->edgeList->begin();
	listIterator != this->edgeList->end();
		++listIterator) {
		
		if (((edge*)*listIterator) == e) {
			//cout << "Edge already in current vertex list\n";
			throw EDGEREDEFINITION;
			return false; // ?
		}
	}
	this->edgeList->push_back(e);
	//cout << "Edge added\n";
	return true;
}

void vertex::displayEdgeList() {
	cout << ">Vertex [" << this->vertexIndex << "] has edges:\n";
	for (std::list<edge *>::iterator listIterator = this->edgeList->begin();
		listIterator != this->edgeList->end();
		++listIterator) 
			((edge*)*listIterator)->displayEdgeInfo();
}
///////////////////
//// >>VERTEX ////
//////////////////

