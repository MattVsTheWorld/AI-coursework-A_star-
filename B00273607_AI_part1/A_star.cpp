#include "A_star.h"

A_star::A_star(AdjacencyList *_adjList) {
	adjList = _adjList;
	iterations = 0;
}

// Pseudocode by Sebastian Lague
// https://github.com/SebLague/Pathfinding/blob/master/Episode%2001%20-%20pseudocode/Pseudocode#L3
//OPEN //the set of nodes to be evaluated
//CLOSED //the set of nodes already evaluated
//add the start node to OPEN
//
//loop
//current = node in OPEN with the lowest f_cost
//remove current from OPEN
//add current to CLOSED
//
//if current is the target node //path has been found
//return
//
//foreach neighbour of the current node
//if neighbour is not traversable or neighbour is in CLOSED
//skip to the next neighbour
//
//if new path to neighbour is shorter OR neighbour is not in OPEN
//set f_cost of neighbour
//set parent of neighbour to current
//if neighbour is not in OPEN
//add neighbour to OPEN

// TODO: Convert to heap? prio queue?

struct vertexComparator {
	bool operator()(vertex*& v1, vertex*v2)
	{
		return v1->getfCost() > v2->getfCost();
	}
};
void A_star::algorithm(vertex* start, vertex* end) {
	openSet.push_back(start);
	while (!openSet.empty()) {
		//auto currentVert = openSet[0];
		//++
		make_heap(openSet.begin(), openSet.end(), vertexComparator());
		sort_heap(openSet.begin(), openSet.end(), vertexComparator());
		//++
		//for (int i = 1; i < openSet.size(); i++) {
		//	if (openSet[i]->getfCost() <= currentVert->getfCost())// || openSet[i]->getfCost() == currentVert->getfCost())
		//		if (openSet[i]->gethCost() < currentVert->gethCost())
		//			currentVert = openSet[i];
		//}
		auto currentVert = openSet.back();
		make_heap(openSet.begin(), openSet.end(), vertexComparator());
		pop_heap(openSet.begin(), openSet.end(), vertexComparator()); openSet.pop_back();

		//openSet.erase(remove(openSet.begin(), openSet.end(), currentVert), openSet.end()); 
		closedSet.insert(currentVert);
		
		if (currentVert == end) {
			cout << "Cost to goal: " << currentVert->getgCost() << endl;
			// cout << "Open: " << openSet.size() << " Closed: " << closedSet.size() << endl;
			list<vertex*> foundPath = retracePath(start, end);
			cout << "Path is: " << start->getIndex() << " ";
			//for (list<vertex*>::iterator pathIterator = foundPath.begin(); pathIterator != foundPath.end(); ++pathIterator)
			for (const auto &pathIterator : foundPath)
				//cout << ((vertex*)*pathIterator)->getIndex() << " ";
				//cout << (static_cast<vertex *>(*pathIterator))->getIndex() << " ";
				cout << (static_cast<vertex *>(pathIterator))->getIndex() << " ";
			cout << endl;
			return;
		}
		using neighbour = pair<vertex*, int>;
		list<neighbour> neighbourList;
		// how to auto a pointer // DONE
		//static_cast<list<edge*>*>(currentVert->getEdgeList())->begin()
		//for (list<edge *>::iterator listIterator = (static_cast<list<edge*>*>(currentVert->getEdgeList()))->begin(); listIterator != (static_cast<list<edge*>*>(currentVert->getEdgeList()))->end(); ++listIterator) {
		for(const auto &listIterator : *(static_cast<list<edge*>*>(currentVert->getEdgeList()))) {
			// You don't need to cast but it's more understandable I feel
			auto _neighbour = make_pair((static_cast<edge*>(listIterator))->getNeighbour(currentVert), (static_cast<edge*>(listIterator))->getWeight());
			//cout << neighbour.first->getIndex() << "[" << neighbour.second << "] ";
			neighbourList.push_back(_neighbour);
		}
		// using name type
		for (const auto &neighbourIterator : neighbourList) {
		//for (list<neighbour>::iterator neighbourIterator = neighbourList.begin(); neighbourIterator != neighbourList.end(); ++neighbourIterator)
		//{
			if (closedSet.find((static_cast<neighbour>(neighbourIterator)).first) != closedSet.end()) { //should make sense
				// cout << "Found in closed set" << endl;
				continue;
			} // else cout << "Not found in closed set" << endl;
			double newMovCostToVert = currentVert->getgCost() + (static_cast<neighbour>(neighbourIterator)).second; //weight
			// Uncertain - but am I
			if (newMovCostToVert < ((static_cast<neighbour>(neighbourIterator)).first)->getgCost() 
				|| (find(openSet.begin(), openSet.end(), (static_cast<neighbour>(neighbourIterator)).first) == openSet.end()))
			{
				(static_cast<neighbour>(neighbourIterator)).first->setgCost(newMovCostToVert);
				(static_cast<neighbour>(neighbourIterator)).first->sethCost(heuristic(currentVert->getCoords(), (static_cast<neighbour>(neighbourIterator)).first->getCoords()));
				(static_cast<neighbour>(neighbourIterator)).first->setParent(currentVert);

				if (find(openSet.begin(), openSet.end(), (static_cast<neighbour>(neighbourIterator)).first) == openSet.end()) {
					openSet.push_back((static_cast<neighbour>(neighbourIterator)).first);
				}
			}
		}
		this->iterations++;
	}
}

list<vertex*> A_star::retracePath(vertex* _start, vertex* _end)
{
	list<vertex*> path;
	vertex* currentVert = _end;
	while (currentVert != _start) {
		path.push_front(currentVert);
		currentVert = currentVert->getParent();
	}
	return path; // path is already in reverse order (pushed to front)
}

double A_star::heuristic(pair<int, int> coord_A, pair<int, int> coord_B) {
	return sqrt(pow((coord_A.first - coord_B.first), 2) + pow((coord_A.second - coord_B.second), 2)); // manhattan didn't work
	//return abs(coord_A.first - coord_B.first) + abs(coord_A.second - coord_B.second); // simple ? not good?
}

int A_star::getIterationCount() {
	return this->iterations;
}
void A_star::resetIterationCount() {
	this->iterations = 0;
}