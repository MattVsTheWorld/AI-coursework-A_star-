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
void A_star::algorithm(vertex* start, vertex* end) {
	openSet.push_back(start);
	while (!openSet.empty()) {
		auto currentVert = openSet[0];
		for (int i = 1; i < openSet.size(); i++) {
			if (openSet[i]->getfCost() <= currentVert->getfCost())// || openSet[i]->getfCost() == currentVert->getfCost())
				if (openSet[i]->gethCost() < currentVert->gethCost())
					currentVert = openSet[i];
		}

		openSet.erase(remove(openSet.begin(), openSet.end(), currentVert), openSet.end());
		closedSet.insert(currentVert);

		if (currentVert == end) {
			cout << "Cost to goal: " << currentVert->getgCost() << endl;
			list<vertex*> foundPath = retracePath(start, end);
			cout << "Path is: " << start->getIndex() << " ";
			for (list<vertex*>::iterator pathIterator = foundPath.begin(); pathIterator != foundPath.end(); ++pathIterator)
			//for (const auto &pathIterator : foundPath)
				//cout << ((vertex*)*pathIterator)->getIndex() << " ";
				cout << (static_cast<vertex *>(*pathIterator))->getIndex() << " ";
				//cout << (static_cast<vertex *>(pathIterator))->getIndex() << " ";
			cout << endl;
			return;
		}

		list<pair<vertex*, int>> neighbourList;
		for (list<edge *>::iterator listIterator = ((list<edge*>*)(currentVert->getEdgeList()))->begin(); listIterator != ((list<edge*>*)(currentVert->getEdgeList()))->end(); ++listIterator) {
			auto neighbour = make_pair(((edge*)*listIterator)->getNeighbour(currentVert), ((edge*)*listIterator)->getWeight());
			//cout << neighbour.first->getIndex() << "[" << neighbour.second << "] ";
			neighbourList.push_back(neighbour);
		}
		// using name type
		for (list<pair<vertex*, int>>::iterator neighbourIterator = neighbourList.begin(); neighbourIterator != neighbourList.end(); ++neighbourIterator)
		{
			if (closedSet.find(((pair<vertex*, int>)*neighbourIterator).first) != closedSet.end()) { //should make sense
				//	cout << "Found in closed set" << endl;
				continue;
			}// else cout << "Not found in closed set" << endl;
			int newMovCostToVert = currentVert->getgCost() + ((pair<vertex*, int>)*neighbourIterator).second; //weight

			if (newMovCostToVert < (((pair<vertex*, int>)*neighbourIterator).first)->getgCost() || (find(openSet.begin(), openSet.end(), ((pair<vertex*, int>)*neighbourIterator).first) == openSet.end()))
			{
				((pair<vertex*, int>)*neighbourIterator).first->setgCost(newMovCostToVert);
				((pair<vertex*, int>)*neighbourIterator).first->sethCost(heuristic(currentVert->getCoords(), ((pair<vertex*, int>)*neighbourIterator).first->getCoords()));
				((pair<vertex*, int>)*neighbourIterator).first->setParent(currentVert);

				if (find(openSet.begin(), openSet.end(), ((pair<vertex*, int>)*neighbourIterator).first) == openSet.end())
					openSet.push_back(((pair<vertex*, int>)*neighbourIterator).first);
			}
		}
		this->iterations++;
	}
}

list<vertex*> A_star::retracePath(vertex* _start, vertex* _end)
{
	list<vertex*> path;
	vertex* currentVert = _end;
	while (currentVert != _start)
	{
		path.push_front(currentVert);
		currentVert = currentVert->getParent();
	}
	return path; // path is already in reverse order (pushed to front)
}

double A_star::heuristic(pair<int, int> coord_A, pair<int, int> coord_B) {
	return sqrt(pow((coord_A.first - coord_B.first), 2) + pow((coord_A.second - coord_B.second), 2)); // manhattan didn't work
}

int A_star::getIterationCount() {
	return this->iterations;
}
void A_star::resetIterationCount() {
	this->iterations = 0;
}