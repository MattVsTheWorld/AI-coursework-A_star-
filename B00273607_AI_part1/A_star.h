#ifndef A_STAR
#define A_STAR
#include <iostream>
#include <queue>
#include "AdjacencyList.h"
#include <unordered_set>
using namespace std;
/// *** 1 ***
/// That one sebastian on youtubez
// https://github.com/SebLague/Pathfinding/blob/master/Episode%2003%20-%20astar/Assets/Scripts/Pathfinding.cs
/// -----------

//A* search class; takes an adjacency list and process any start - end point
class A_star {
private:
	vector<vertex*> openSet;
	unordered_set<vertex*> closedSet;
	AdjacencyList* adjList;

	list<vertex*> retracePath(vertex* _start, vertex* _end);
	double heuristic(pair<int, int> coord_A, pair<int, int> coord_B);
	//int iterations;
protected:
public:
	A_star(AdjacencyList *_adjList);
	void algorithm(vertex* start, vertex* end);
	//int getIterationCount();
	//void resetIterationCount();
};
#endif