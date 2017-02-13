#ifndef A_STAR
#define A_STAR
#include <iostream>
#include <queue>
#include "AdjacencyList.h"
using namespace std;
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
//--

class A_star {
private:
	queue <vertex*> open;
	queue <vertex*> closed;
	AdjacencyList* adjList;
protected:
public:
	A_star(AdjacencyList *_adjList) {
		// do stuff
		adjList = _adjList; // assigning pointers... right? right? :thinking:
	}

	double heuristic(pair<int, int> coord_A, pair<int, int> coord_B) {
		return abs(coord_A.first - coord_B.first) + abs(coord_A.second - coord_B.second);
	}

};
#endif A_STAR