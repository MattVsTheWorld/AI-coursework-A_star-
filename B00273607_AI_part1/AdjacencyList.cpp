#include "AdjacencyList.h"

//TODO: separate classes?
//////////////////////////
//// Edge class start ////
//////////////////////////

edge::edge(vertex *A, vertex *B, int w) {
	adjacent[0] = A; // assign pointers to connecting vertices
	adjacent[1] = B;
	weight = w;
}

vertex** edge::getEndPoints() {
	return this->adjacent;
}

vertex* edge::getNeighbour(vertex* startingVert) {
	if (startingVert->getIndex() == this->adjacent[0]->getIndex())
		return this->adjacent[1];
	else if (startingVert->getIndex() == this->adjacent[1]->getIndex())
		return this->adjacent[0];
}

int edge::getWeight() {
	return this->weight;
}

void edge::displayEdgeInfo() {
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
	edgeList = new list<edge *>;
}

void vertex::displayVertexInfo() {
	cout << "Index: [" << this->vertexIndex << "] ";
	cout << "Coords: [" << this->vertexCoords.first << "," << this->vertexCoords.second << "]\n";
}

int vertex::getIndex() {
	return this->vertexIndex;
}
bool vertex::addEdge(edge *e) {
	
	//for (list<edge *>::iterator listIterator = this->edgeList->begin();
	//listIterator != this->edgeList->end();
	//	++listIterator) 
	for (const auto edgeIterator : *(this->edgeList))
	{
		if ((static_cast<edge*>(edgeIterator)) == e)
			throw EDGEDUPLICATE;
	}
	this->edgeList->push_back(e);
	return true;
}

list<edge *>* vertex::getEdgeList() {
	return this->edgeList;
}

void vertex::displayEdgeList() {
	cout << ">Vertex [" << this->vertexIndex << "] has edges:\n";
	//for (list<edge *>::iterator listIterator = this->edgeList->begin();
	//listIterator != this->edgeList->end();
	//	++listIterator)
	for (const auto edgeIterator : *(this->edgeList))
		(static_cast<edge*>(edgeIterator))->displayEdgeInfo();
}

int vertex::getfCost() {
	return (this->gCost + this->hCost);
}

int vertex::getgCost() {
	return this->gCost;
}
int vertex::gethCost() {
	return this->hCost;
}

void vertex::setgCost(int _g) {
	this->gCost = _g;
}
void vertex::sethCost(int _h) {
	this->hCost = _h;
}

pair<int, int> vertex::getCoords() {
	return this->vertexCoords;
}

void vertex::setParent(vertex* _parent) {
	this->parent = _parent;
}

vertex* vertex::getParent() {
	return this->parent;
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
void AdjacencyList::addVertex(vertex *v) {
	// add a vertex to vector
	// we will assume vertices don't take the same position
	if (v->getIndex() > this->vertexNo)
		throw OUTOFBOUNDS;
	vertices->push_back(v);
	this->vertexNo++;
}

void AdjacencyList::addEdge(edge *e) {
	if (e->getEndPoints()[0]->getIndex() >= this->vertexNo
		|| e->getEndPoints()[1]->getIndex() >= this->vertexNo)
		throw OUTOFBOUNDS;
	// Assumes you won't try to enter the same edge twice
	vector<vertex *>::iterator vectorIterator = this->vertices->begin();
	int endPointsFound = 0;
	while (vectorIterator != this->vertices->end() || endPointsFound < 2) {
		if ((static_cast<vertex*>(*vectorIterator))->getIndex() == e->getEndPoints()[0]->getIndex()) {
			(static_cast<vertex*>(*vectorIterator))->addEdge(e);
			endPointsFound++;
		}
		else if ((static_cast<vertex*>(*vectorIterator))->getIndex() == e->getEndPoints()[1]->getIndex()) {
			(static_cast<vertex*>(*vectorIterator))->addEdge(e);
			endPointsFound++;
		}
		vectorIterator++;
	}
	this->edgeNo++;
}

vertex* AdjacencyList::getVertex(int index) {
	if (index >= this->vertexNo)
		throw OUTOFBOUNDS;
	vector<vertex *>::iterator vectorIterator = this->vertices->begin();
	while (vectorIterator != this->vertices->end()) {
		if ((static_cast<vertex*>(*vectorIterator))->getIndex() == index)
			return (static_cast<vertex*>(*vectorIterator));
		else
			vectorIterator++;
	}
}

void AdjacencyList::displayVertices() {
	//for (vector<vertex *>::iterator vectorIterator = this->vertices->begin();
	//vectorIterator != this->vertices->end();
	//	++vectorIterator) {
	for(const auto verticesIterator : *(this->vertices)){
		cout << "|| Vertex info ||\n";
		(static_cast<vertex*>(verticesIterator))->displayVertexInfo();
		cout << "|| Edge list ||\n";
		(static_cast<vertex*>(verticesIterator))->displayEdgeList();
		cout << endl;
	}
}

void AdjacencyList::resetCosts() {
	for (const auto &vectorIterator : *(vertices)) {
		vectorIterator->sethCost(0);
		vectorIterator->setgCost(0);
	}
}
/////////////////////////////////
//// AdjacencyList class end ////
////////////////////////////////

