#ifndef A_STAR
#define A_STAR
#include <iostream>
#include <queue>
#include "AdjacencyList.h"
//#include <hash_set>
#include <unordered_set>
using namespace std;
/// *** 1 ***
/// That one sebastian on youtubez
// https://github.com/SebLague/Pathfinding/blob/master/Episode%2003%20-%20astar/Assets/Scripts/Pathfinding.cs
// ty
// OPEN // open nodes // to be evaluated
// CLOSED // nodes already evaluated
// add the start node to open
// loop
	// current (temp var) (beginning = starting) = node in OPEN with lowest f()
	// remove current from OPEN
	// add current to CLOSED

// if current is target -> PATH FOUND
	// return

// for each neighjbour of current node (LOOP ALL NEIGHBOURS)
//++
	// if neighbour is CLOSED or BNOT TRAVERSABLE
		// skip to next

// if new path to neighbour is shorter  || OR || neighbour is not open (!OPEN)
	// set f() of NEIGHBOUR
	// set parent of neighbour to current
	// if neighbour not in OPEN list
		// add to OPEN
/// *** 1 ***
/// -----------

/// *** 2 ***
/// Redblob
//frontier = PriorityQueue()
//frontier.put(start, 0)
//came_from = {}
//cost_so_far = {}
//came_from[start] = None
//cost_so_far[start] = 0
//
//while not frontier.empty() :
//	current = frontier.get()
//
//	if current == goal :
//		break
//
//		for next in graph.neighbors(current) :
//			new_cost = cost_so_far[current] + graph.cost(current, next)
//			if next not in cost_so_far or new_cost < cost_so_far[next] :
//				cost_so_far[next] = new_cost
//				priority = new_cost + heuristic(goal, next)
//				frontier.put(next, priority)
//				came_from[next] = current
//#include <unordered_set>

/*
Attempt of human translation of that pseudocode
Aight so we have a frontier = unexplored nodes
///frontier is a priority Queue;
- Add start to frontier, priority 0
- we came from {} (nowhere, it's start)
- cost so far {} (0, it's start)
- came_from[start] = none; (set to just started)
- cost_so_far[start] = 0 (set cost to 0)

- while the frontier (explorable nodes) not empty
	{
	current = frontier.get() (Which I immagine gets the higher priority node (lower value, closer to end) in the queue)
	if current == goal,
		end found; break

		for - loop neighbours of current
		{
			new_cost = cost_so_far[current] + weight to get to next (== this neighbor)
			if [next] (neighbour) is not in cost_so_far (first neighbor, cost_so_far[next] =~ null) or new_cost < cost_so_far[next] (meaning the cost to this neighbor is less = more efficent)
			{
				cost_so_far[next] = new_cost (replace)
				priority = new_cost + heuristic (goal, next (current neighbor)
				frontier.put(next (current neighbor, priority);
				came_from[next] = current (parent of neighbor)
			}
		}

	}

*/
/// *** 2 ***
/*
image test
frontier = prio queue;
frontier.add(start, 0);
[came_from] = {};
[cost_so_far[ = {};
-- START = 0 --
came_from[0] = null;
cost_so_far[0] = 0;

while (!frontier.isEmpty())
{
	vertex current = frontier.get() ((( gets start ))))
	if (current == goal)
		break;
	for(iterate [edges] of [current]; get [next_vertex] that isn't [current]; until list of [edges[ is end())
		[new_cost] = cost_so_far[current] + [current to [next_vertex]->edge->weight];
		if [next_vertex] not in [cost_so_far] (first considered) (aka if cost_so_far[i++])
			||
		[new_cost] < cost_so_far[next] (this particular neighbor is seemingly more efficent than previous)
			{
				cost_so_far[next] = new_cost (replace)
				priority = [new_cost]+ heuristic (goal, next (current neighbor)
				frontier.put(next, priority) (current neighbor w/ priority);
				came_from[next] = current (parent of neighbor) (POINT WHERE YOU CAME FROM
			}
}
// ****
int INDEX = 0;
current = 0;
not goal
iterate edges
	// EDGE 0-6 (assume h = 6)
	new cost = 0 + 147 = 147
	cost so far empty, hence add
		cost_so_far[++INDEX] = 147;
		priority = 147 + 6 = 153;
		push to frontier [6, 153];
		came_from[INDEX] = 0; (start)

	// EDGE 0-7 (assume h = 5)
	new cost = 0 + 106 = 106
	cost < than 147, hence
		cost_so_far[What index? same I think But maybe not. Maybe...] = new_cost (106) 
		prio 106+ 5 = 111
		frontier.put(next,prio)
	// EDGE 0-13 (assume h = 3)
	// EDGE 0-3 (assume h = 9)
// ***

*/
/// -----------
class A_star {
private:
	//unordered_set<vertex*> visited;
	//queue <vertex*> frontier;
	//queue <vertex*> closed;
	vector<vertex*> openSet;
	unordered_set<vertex*> closedSet; //?
	AdjacencyList* adjList;
protected:
public:
	A_star(AdjacencyList *_adjList) {
		// do stuff
		adjList = _adjList; // assigning pointers... right? right? :thinking:
	}

	void algorithm(vertex* start, vertex* end) {
		openSet.push_back(start);
		while (!openSet.empty()) {
			auto currentVert = openSet[0];
			for (int i = 1; i < openSet.size(); i++)
			{
				if (openSet[i]->getfCost() < currentVert->getfCost() || openSet[i]->getfCost() == currentVert->getfCost() )
					if (openSet[i]->gethCost() < currentVert->gethCost())
						currentVert = openSet[i];
			}
		//	openSet.
			/*auto it = find(openSet.begin(), openSet.end(), currentVert);
			if (it != openSet.end())
				openSet.erase(it);*/
			openSet.erase(remove(openSet.begin(), openSet.end(), currentVert), openSet.end()); // :thinking:
			//closedSet.push(currentVert);
			closedSet.insert(currentVert);

			if (currentVert == end) // point at the same??
			{
				list<vertex*> foundPath = retracePath(start, end);
				cout << "Path is: " << start->getIndex() << " ";
				for (list<vertex*>::iterator listIterator = foundPath.begin(); listIterator != foundPath.end(); ++listIterator)
					cout <<( (vertex*)*listIterator)->getIndex() << " ";
				cout << endl;
				//cout << end->getIndex();
				return;
			}
			list<pair<vertex*, int>> neighbourList;
			//list<edge*> *currentEdgeList = currentVert->getEdgeList();
			//(list<edge*>*)*(currentVert->getEdgeList())->begin();
			// DEBUG
		//	int count = 0;
			//cout << "\nFinding neighbour of current vert: " << currentVert->getIndex();
		//	cout << endl;
			// DEBUG
			for (list<edge *>::iterator listIterator = ((list<edge*>*)(currentVert->getEdgeList()))->begin(); listIterator != ((list<edge*>*)(currentVert->getEdgeList()))->end(); ++listIterator)
			{
				// DEBUG
			//	count++;
				
			//	cout << "Neighbour " << count <<  " ID: ";
			//	cout << ((edge*)*listIterator)->getNeighbour(currentVert)->getIndex();
		//		cout << endl;
				// DEBUG
				auto neighbour = make_pair(((edge*)*listIterator)->getNeighbour(currentVert), ((edge*)*listIterator)->getWeight());
				//cout << neighbour.first->getIndex() << "[" << neighbour.second << "] ";
				neighbourList.push_back(neighbour);
			}
		//	cout << "Neighbour list size: " << neighbourList.size() << endl;
			//cout << endl;
				// GET NEIGHBORS
					// for each neigbor of current
					// if (closetSet.contains(neighbaaa)
					// continue;

		//	cout << "Iterating through neighbour list..." << endl;

			for (list<pair<vertex*, int>>::iterator neighbourIterator = neighbourList.begin(); neighbourIterator != neighbourList.end(); ++neighbourIterator)
			{
				if (closedSet.find(((pair<vertex*, int>)*neighbourIterator).first) != closedSet.end()) //should make sense
				{
				//	cout << "Found in closed set" << endl;
					continue; // :thinking:
				}// else cout << "Not found in closed set" << endl;
				int newMovCostToVert = currentVert->getgCost() + ((pair<vertex*, int>)*neighbourIterator).second; //weight
				//cout << "New movement cost to vertex: " << newMovCostToVert << endl;
				if (newMovCostToVert < (((pair<vertex*, int>)*neighbourIterator).first)->getgCost() || (find(openSet.begin(), openSet.end(), ((pair<vertex*, int>)*neighbourIterator).first) == openSet.end()))
				{
					//cout << "Found to be smaller..." << endl;
					((pair<vertex*, int>)*neighbourIterator).first->setgCost(newMovCostToVert);
					((pair<vertex*, int>)*neighbourIterator).first->sethCost(heuristic(currentVert->getCoords(), ((pair<vertex*, int>)*neighbourIterator).first->getCoords()));
					((pair<vertex*, int>)*neighbourIterator).first->setParent(currentVert);

					//
					if (find(openSet.begin(), openSet.end(), ((pair<vertex*, int>)*neighbourIterator).first) == openSet.end())
						openSet.push_back(((pair<vertex*,int>)*neighbourIterator).first);
				//	if(!openSet.)
					//continue;
				}
			}

			 			
			// HEURISTIC
			// int newMovCostToVert = currentVert gCost + distance between node and neighbor (= weight)
			// if newMovCostToVert < neighbor.GCost || !openSet.contains(neighbour)
				// neighbor.gCost = newMovCostToVert;
				// hCost = HEUR
				// neighbor.parent = currentVert;

				// if (!openSet.contains(neighbor)
					//add neighbor

		}
	}

	
	list<vertex*> retracePath(vertex* _start, vertex* _end)
	{
		list<vertex*> path;
		vertex* currentVert = _end;
		while (currentVert != _start)
		{
			path.push_front(currentVert);
			currentVert = currentVert->getParent();
		}
		//cout << "THinking";
	return path;
	//	path.reverse (no need, pushed front)
	}
	double heuristic(pair<int, int> coord_A, pair<int, int> coord_B) {
		return abs(coord_A.first - coord_B.first) + abs(coord_A.second - coord_B.second); // simple ? not good?
	}


	
	//void breadthFirst(vertex* start) {
	//	frontier.push(start);
	//	visited.insert(start);

	//	while (!frontier.empty()) {
	//		auto current = frontier.front();
	//		frontier.pop();

	//		cout << "Visiting " << current->getIndex() << endl;
	//		for (std::list<edge *>::iterator listIterator = current->getEdgeList()->begin();
	//		listIterator != current->getEdgeList()->end();
	//			++listIterator)
	//		{
	//		//	frontier.push(;
	//			((edge*)*listIterator)->displayEdgeInfo();
	//		}
	//	}
	//}


	

};
#endif A_STAR