#include "AdjacencyList.h"

//////////////////////////
//// Edge class start ////
//////////////////////////

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

//vertex* edge::getOtherEnd(vertex* startingVert) {
//	if (startingVert->getIndex() == this->adjacent[0]->getIndex())
//		return this->adjacent[1];
//	else if (startingVert->getIndex() == this->adjacent[1]->getIndex())
//		return this->adjacent[0];
//}

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

////////////////////////
//// Edge class end ////
///////////////////////

////////////////////////////
//// Vertex class start ////
///////////////////////////
vertex::vertex(int index, pair<int, int> coords) {
	this->vertexIndex = index;
	this->vertexCoords = coords;
	edgeList = new list<edge *>; // :thinking:
	//	cout << "Coords of added: " <<  this->vertexCoords.first << " - " << this->vertexCoords.second << endl;
}

void vertex::displayVertexInfo() {
	cout << "Index: [" << this->vertexIndex << "] ";
	cout << "Coords: [" << this->vertexCoords.first << "," << this->vertexCoords.second << "]\n";
}

int vertex::getIndex() {
	return this->vertexIndex;
}
bool vertex::addEdge(edge *e) {
	for (list<edge *>::iterator listIterator = this->edgeList->begin();
	listIterator != this->edgeList->end();
		++listIterator) {

		if (((edge*)*listIterator) == e) {
			//cout << "Edge already in current vertex list\n";
			throw EDGEDUPLICATE;
			//return false; // ?
		}
	}
	this->edgeList->push_back(e);
	//cout << "Edge added\n";
	return true;
}
//
//list<edge *>* vertex::getEdgeList() {
//	return this->edgeList;
//}

//int vertex::getNeighours() {
//	for (list<edge *>::iterator listIterator = this->edgeList->begin();
//	listIterator != this->edgeList->end();
//		++listIterator)
//		((edge*)*listIterator)->getOtherEnd(this);
//
//}

void vertex::displayEdgeList() {
	cout << ">Vertex [" << this->vertexIndex << "] has edges:\n";
	for (list<edge *>::iterator listIterator = this->edgeList->begin();
	listIterator != this->edgeList->end();
		++listIterator)
		((edge*)*listIterator)->displayEdgeInfo();
}
//////////////////////////
//// Vertex class end ////
/////////////////////////

///////////////////////////////////
//// AdjacencyList class start ////
//////////////////////////////////
AdjacencyList::AdjacencyList() {
	// initialize collection
	vertices = new vector<vertex *>;
	vertexNo = 0;
	edgeNo = 0;
}
bool AdjacencyList::addVertex(vertex *v) {
	// add a vertex to vector
	// we will assume vertices don't take the same position
	if (v->getIndex() > this->vertexNo)
		throw OUTOFBOUNDS;
	vertices->push_back(v);
	vertexNo++;
	//cout << "Vertex added\n";
	return true;
}
//	 returns
bool AdjacencyList::addEdge(edge *e) {
	if (e->getEndPoints()[0]->getIndex() >= this->vertexNo
		|| e->getEndPoints()[1]->getIndex() >= this->vertexNo)
	{
		//cout << "Edge connects unexisting vertices\n"; // put these in main program
		throw OUTOFBOUNDS;
		//return false; // ? 
	}
	// Assumes you won't try to enter the same edge twice
	vector<vertex *>::iterator vectorIterator = this->vertices->begin();
	int endPointsFound = 0;
	while (vectorIterator != this->vertices->end() || endPointsFound < 2) {
		if (((vertex*)*vectorIterator)->getIndex() == e->getEndPoints()[0]->getIndex()) {
			//	endPointA = ((vertex*)*vectorIterator);
			((vertex*)*vectorIterator)->addEdge(e);
			endPointsFound++;
		}
		else if (((vertex*)*vectorIterator)->getIndex() == e->getEndPoints()[1]->getIndex()) {
			((vertex*)*vectorIterator)->addEdge(e);
			endPointsFound++;
		}
		vectorIterator++;
	}
	return true;
}

//bool AdjacencyList::areAdjacent(vertex *v, vertex *w) {
//	// if one of edges contains both vertices
//	// needed?
//	return false;
//}

vertex* AdjacencyList::getVertex(int index) {
	if (index >= this->vertexNo)
		throw OUTOFBOUNDS;
	vector<vertex *>::iterator vectorIterator = this->vertices->begin();
	while (vectorIterator != this->vertices->end()) {
		if (((vertex*)*vectorIterator)->getIndex() == index)
			return ((vertex*)*vectorIterator);
		else
			vectorIterator++;
	}
}
void AdjacencyList::displayVertices() {
	for (vector<vertex *>::iterator vectorIterator = this->vertices->begin();
	vectorIterator != this->vertices->end();
		++vectorIterator) {
		cout << "|| Vertex info ||\n";
		((vertex*)*vectorIterator)->displayVertexInfo();
		cout << "|| Edge list ||\n";
		((vertex*)*vectorIterator)->displayEdgeList();
		cout << endl;
	}
}
/////////////////////////////////
//// AdjacencyList class end ////
////////////////////////////////

