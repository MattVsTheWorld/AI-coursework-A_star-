#pragma once
#ifndef A_STAR
#define A_STAR
#include <iostream>
#include <queue>
#include <functional>
#include "AdjacencyList.h"
#include <unordered_set>
using namespace std;
/// *** 1 ***
/// That one sebastian on youtubez
// https://github.com/SebLague/Pathfinding/blob/master/Episode%2003%20-%20astar/Assets/Scripts/Pathfinding.cs
/// -----------

// http://www.redblobgames.com/pathfinding/a-star/implementation.html
struct PriorityQueue {
	typedef pair<double, vertex*> queue_Element;
	priority_queue < queue_Element, vector<queue_Element>, greater<queue_Element>> elements;

	inline bool empty() const { return elements.empty(); }

	inline void put(vertex* item, double priority) {
		elements.emplace(priority, item);
	}

	inline vertex* get() {
		vertex* best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

//A* search class; takes an adjacency list and process any start - end point
class A_star {
private:
	vector<vertex*> openSet;
	PriorityQueue open_Set;
	//	priority_queue<vertex*, vector<int>, greater<int>> openSet;
	unordered_set<vertex*> closedSet;
	AdjacencyList* adjList;

	list<vertex*> retracePath(vertex* _start, vertex* _end);
	double heuristic(pair<int, int> coord_A, pair<int, int> coord_B);
	int iterations;
protected:
public:
	A_star(AdjacencyList *_adjList);
	void algorithm(vertex* start, vertex* end);
	int getIterationCount();
	void resetIterationCount();
};
#endif