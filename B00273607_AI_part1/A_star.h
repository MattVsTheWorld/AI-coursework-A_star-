#pragma once
#ifndef A_STAR
#define A_STAR
#include <iostream>
#include <queue>
#include <functional>
#include "AdjacencyList.h"
#include <unordered_set>
using namespace std;

class A_star {																// A* search class: attempts to find best path between two points of a given graph
private:
	vector<vertex*> openSet;												// vertices still being considered
	unordered_set<vertex*> closedSet;										// vertices determined to be unoptimal for the route
	AdjacencyList* adjList;													// graph structure to traverse
	// Methods
	list<vertex*> retracePath(vertex* _start, vertex* _end);				// retrace the path through the use of parent references
	double heuristic(pair<int, int> coord_A, pair<int, int> coord_B);		// calculate heuristic (in this case, euclidean distance)
	int iterations;															// number of while iterations before the goal is found
protected:
public:
	A_star(AdjacencyList *_adjList);										// Create base object by copying the graph
	void algorithm_standard(vertex* start, vertex* end);					// "standard" version of the algorithm (every iteration explores the entire open set)
	void algorithm_heap(vertex* start, vertex* end);						// Heap implementation of the open set (same result)
	int getIterationCount();												// return iteration count
	void resetIterationCount();												// set iteration count to 0
};
#endif