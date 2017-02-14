#ifndef A_STAR
#define A_STAR
#include <iostream>
#include <queue>
#include "AdjacencyList.h"

using namespace std;
/// *** 1 ***
/// That one sebastian on youtubez
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
/// -----------
class A_star {
private:
	//unordered_set<vertex*> visited;
	//queue <vertex*> frontier;
	//queue <vertex*> closed;
	AdjacencyList* adjList;
protected:
public:
	A_star(AdjacencyList *_adjList) {
		// do stuff
		adjList = _adjList; // assigning pointers... right? right? :thinking:
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

	double heuristic(pair<int, int> coord_A, pair<int, int> coord_B) {
		return abs(coord_A.first - coord_B.first) + abs(coord_A.second - coord_B.second); // simple ? not good?
	}
	

};
#endif A_STAR