#include "A_star.h"

// Credits to algorithm and tutorial to Sebastian Lague
// See references in main.cpp
// A* pseudocode
// -------------
// OPEN											// the set of nodes to be evaluated
// CLOSED										// the set of nodes already evaluated
// add the start node to OPEN
//
// loop
//		current = node in OPEN set with the lowest f_cost
//		remove current from OPEN set
//		add current to CLOSED set
// 
//		if current is the target node			//path has been found
//			return
//
//		foreach neighbour of the current node
//			if neighbour is not traversable or neighbour is in CLOSED
//				skip to the next neighbour
//
//			if new path to neighbour is shorter OR neighbour is not in OPEN
//				set f_cost of neighbour (set g and h costs)
//				set parent of neighbour to current
//				if neighbour is not in OPEN
//					add neighbour to OPEN
//		end foreach
// end loop

A_star::A_star(AdjacencyList *_adjList) {
	adjList = _adjList;
	iterations = 0;
}

void A_star::algorithm_standard(vertex* start, vertex* end) {
	openSet.push_back(start);
	while (!openSet.empty()) {
		auto currentVert = openSet[0];
		// Find vertex in open list with lowest f cost
		for (int i = 1; i < openSet.size(); i++) {																	
			if (openSet[i]->getfCost() <= currentVert->getfCost())
				if (openSet[i]->gethCost() < currentVert->gethCost())
					currentVert = openSet[i];
		}

		openSet.erase(remove(openSet.begin(), openSet.end(), currentVert), openSet.end());
		closedSet.insert(currentVert);
		// if current vertex is goal, path found
		if (currentVert == end) {																					
			cout << "Cost to goal: " << currentVert->getgCost() << endl;
			list<vertex*> foundPath = retracePath(start, end);
			cout << "Path is: " << start->getIndex() << " ";
			for (const auto &pathIterator : foundPath)
				cout << (static_cast<vertex *>(pathIterator))->getIndex() << " ";
			cout << endl;
			return;
		}
		using neighbour = pair<vertex*, int>;
		list<neighbour> neighbourList;
		// construct list of neighbours from edges of the vertex
		for (const auto &listIterator : *(static_cast<list<edge*>*>(currentVert->getEdgeList()))) {					
			//Small note: You don't necessarily need to cast to edge the iterator, but I feel it makes it clearer
			auto _neighbour = make_pair((static_cast<edge*>(listIterator))->getNeighbour(currentVert), (static_cast<edge*>(listIterator))->getWeight());
			neighbourList.push_back(_neighbour);
		}
		// iterate over neighbours and pick best alternative
		for (const auto &neighbourIterator : neighbourList) {														
			if (closedSet.find((static_cast<neighbour>(neighbourIterator)).first) != closedSet.end()) {
				continue;
			}
			// New overall cost is equal to cost of current path + cost of edge traversal (weight)
			double newMovCostToVert = currentVert->getgCost() + (static_cast<neighbour>(neighbourIterator)).second; 
			if (newMovCostToVert < ((static_cast<neighbour>(neighbourIterator)).first)->getgCost()
				|| (find(openSet.begin(), openSet.end(), (static_cast<neighbour>(neighbourIterator)).first) == openSet.end()))
			{	// set f_cost (through g and h costs) and set new parent
				(static_cast<neighbour>(neighbourIterator)).first->setgCost(newMovCostToVert);
				(static_cast<neighbour>(neighbourIterator)).first->sethCost(heuristic(static_cast<neighbour>(neighbourIterator).first->getCoords(), end->getCoords()));
				(static_cast<neighbour>(neighbourIterator)).first->setParent(currentVert);
				// add to open set if not already present
				if (find(openSet.begin(), openSet.end(), (static_cast<neighbour>(neighbourIterator)).first) == openSet.end()) {
					openSet.push_back((static_cast<neighbour>(neighbourIterator)).first);
				}
			}
		}
		this->iterations++;
	}
}

struct vertexComparator {
	bool operator()(vertex*& v1, vertex*v2)
	{
		return v1->getfCost() > v2->getfCost();
	}
};

// Either the heap implementation is flawed or the sorting takes too much time to justify the use of it in a restricted graph like this
// It's not used by the program, but provides an alternative to going through the entire open set
void A_star::algorithm_heap(vertex* start, vertex* end) {
	openSet.push_back(start);
	while (!openSet.empty()) {

		make_heap(openSet.begin(), openSet.end(), vertexComparator());
		sort_heap(openSet.begin(), openSet.end(), vertexComparator());									
		// Find vertex in open list with lowest f cost
		auto currentVert = openSet.back();
		make_heap(openSet.begin(), openSet.end(), vertexComparator());
		pop_heap(openSet.begin(), openSet.end(), vertexComparator()); openSet.pop_back();

		closedSet.insert(currentVert);
		// if current vertex is goal, path found
		if (currentVert == end) {
			cout << "Cost to goal: " << currentVert->getgCost() << endl;
			list<vertex*> foundPath = retracePath(start, end);
			cout << "Path is: " << start->getIndex() << " ";
			for (const auto &pathIterator : foundPath)
				cout << (static_cast<vertex *>(pathIterator))->getIndex() << " ";
			cout << endl;
			return;
		}
		using neighbour = pair<vertex*, int>;
		list<neighbour> neighbourList;
		// construct list of neighbours from edges of the vertex
		for (const auto &listIterator : *(static_cast<list<edge*>*>(currentVert->getEdgeList()))) {
			auto _neighbour = make_pair((static_cast<edge*>(listIterator))->getNeighbour(currentVert), (static_cast<edge*>(listIterator))->getWeight());
			neighbourList.push_back(_neighbour);
		}
		// iterate over neighbours and pick best alternative
		for (const auto &neighbourIterator : neighbourList) {
			if (closedSet.find((static_cast<neighbour>(neighbourIterator)).first) != closedSet.end())
				continue;
			// New overall cost is equal to cost of current path + cost of edge traversal (weight)
			double newMovCostToVert = currentVert->getgCost() + (static_cast<neighbour>(neighbourIterator)).second;
			if (newMovCostToVert < ((static_cast<neighbour>(neighbourIterator)).first)->getgCost()
				|| (find(openSet.begin(), openSet.end(), (static_cast<neighbour>(neighbourIterator)).first) == openSet.end()))
			{	// set f_cost (through g and h costs) and set new parent
				(static_cast<neighbour>(neighbourIterator)).first->setgCost(newMovCostToVert);
				(static_cast<neighbour>(neighbourIterator)).first->sethCost(heuristic(static_cast<neighbour>(neighbourIterator).first->getCoords(), end->getCoords()));
				(static_cast<neighbour>(neighbourIterator)).first->setParent(currentVert);
				// add to open set if not already present
				if (find(openSet.begin(), openSet.end(), (static_cast<neighbour>(neighbourIterator)).first) == openSet.end())
					openSet.push_back((static_cast<neighbour>(neighbourIterator)).first);
			}
		}
		this->iterations++;
	}
}

list<vertex*> A_star::retracePath(vertex* _start, vertex* _end) { 
	list<vertex*> path;
	vertex* currentVert = _end;
	while (currentVert != _start) {
		path.push_front(currentVert);																	// push to front to get reversed order									
		currentVert = currentVert->getParent();
	}
	return path;									
}

double A_star::heuristic(pair<int, int> coord_A, pair<int, int> coord_B) {
	return sqrt(pow((coord_A.first - coord_B.first), 2) + pow((coord_A.second - coord_B.second), 2));	// Euclidean distance
	//return abs(coord_A.first - coord_B.first) + abs(coord_A.second - coord_B.second);					// Manhattan distance; often overestimates
}

int A_star::getIterationCount() {
	return this->iterations;
}
void A_star::resetIterationCount() {
	this->iterations = 0;
}