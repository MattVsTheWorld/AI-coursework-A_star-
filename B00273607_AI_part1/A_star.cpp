#include "A_star.h"

A_star::A_star(AdjacencyList *_adjList) {
	adjList = _adjList; // assigning pointers... right? right? :thinking:
}

void A_star::algorithm(vertex* start, vertex* end) {
	openSet.push_back(start);
	while (!openSet.empty()) {
		auto currentVert = openSet[0];
		for (int i = 1; i < openSet.size(); i++) {
			if (openSet[i]->getfCost() < currentVert->getfCost() || openSet[i]->getfCost() == currentVert->getfCost())
				if (openSet[i]->gethCost() < currentVert->gethCost())
					currentVert = openSet[i];
		}

		openSet.erase(remove(openSet.begin(), openSet.end(), currentVert), openSet.end());
		closedSet.insert(currentVert);

		if (currentVert == end) { // point at the same, right? :thinking:
			list<vertex*> foundPath = retracePath(start, end);
			cout << "Path is: " << start->getIndex() << " ";
			for (list<vertex*>::iterator pathIterator = foundPath.begin(); pathIterator != foundPath.end(); ++pathIterator)
				cout << ((vertex*)*pathIterator)->getIndex() << " ";
			cout << endl;
			return;
		}
		list<pair<vertex*, int>> neighbourList;

		for (list<edge *>::iterator listIterator = ((list<edge*>*)(currentVert->getEdgeList()))->begin(); listIterator != ((list<edge*>*)(currentVert->getEdgeList()))->end(); ++listIterator) {
			auto neighbour = make_pair(((edge*)*listIterator)->getNeighbour(currentVert), ((edge*)*listIterator)->getWeight());
			//cout << neighbour.first->getIndex() << "[" << neighbour.second << "] ";
			neighbourList.push_back(neighbour);
		}

		for (list<pair<vertex*, int>>::iterator neighbourIterator = neighbourList.begin(); neighbourIterator != neighbourList.end(); ++neighbourIterator)
		{
			if (closedSet.find(((pair<vertex*, int>)*neighbourIterator).first) != closedSet.end()) { //should make sense
				//	cout << "Found in closed set" << endl;
				continue;
			}// else cout << "Not found in closed set" << endl;
			int newMovCostToVert = currentVert->getgCost() + ((pair<vertex*, int>)*neighbourIterator).second; //weight
																											  //cout << "New movement cost to vertex: " << newMovCostToVert << endl;
			if (newMovCostToVert < (((pair<vertex*, int>)*neighbourIterator).first)->getgCost() || (find(openSet.begin(), openSet.end(), ((pair<vertex*, int>)*neighbourIterator).first) == openSet.end()))
			{
				//cout << "Found to be smaller..." << endl;
				((pair<vertex*, int>)*neighbourIterator).first->setgCost(newMovCostToVert);
				((pair<vertex*, int>)*neighbourIterator).first->sethCost(heuristic(currentVert->getCoords(), ((pair<vertex*, int>)*neighbourIterator).first->getCoords()));
				((pair<vertex*, int>)*neighbourIterator).first->setParent(currentVert);

				if (find(openSet.begin(), openSet.end(), ((pair<vertex*, int>)*neighbourIterator).first) == openSet.end())
					openSet.push_back(((pair<vertex*, int>)*neighbourIterator).first);
			}
		}
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
	return abs(coord_A.first - coord_B.first) + abs(coord_A.second - coord_B.second); // simple ? not good?
}