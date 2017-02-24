//
//==============================================================================================================================================
// B00273607
// AI coursework - part 1
// A* pathfinding
//==============================================================================================================================================
//

/*
* ==============================================================================================================================================
//// References - All website last accessed February 2017
// Guides on how to represent a graph
* http://softwareengineering.stackexchange.com/questions/148313/what-is-the-most-space-efficient-way-to-implement-a-graph-data-structure
* http://www.cplusplus.com/forum/beginner/118340/
* https://en.wikipedia.org/wiki/Adjacency_list
// Further information on graph representation, and statistics on performance to decide which data structure to use
* https://en.wikipedia.org/wiki/Graph_(abstract_data_type) 
// Goodrich and Tamassia's adjacency list and more (in a power point representation)
* www.utdallas.edu/~daescu/Graph.ppt 
// Justification of why the graph might be considered sparse
* http://stackoverflow.com/questions/12599143/what-is-the-distinction-between-sparse-and-dense-graphs 
// General idea of A* (although different version was implemented)
* http://www.redblobgames.com/pathfinding/a-star/implementation.html
// Tutorial and pseudocode for A* inspired by Sebastian Lague's implementation for pathfinding in Unity
* https://github.com/SebLague/Pathfinding	  - Repository
* https://www.youtube.com/watch?v=-L-WgKMFuhE - First video tutorial
* ==============================================================================================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include "AdjacencyList.h"
#include "A_star.h"
#include <chrono>

using namespace std;

#define VERTICES_BEGIN 2
#define VERTICES_END 67
#define EDGES_END 194

// A rather rudimentary and case specific parser
// With more time could be improved to instead recognise the two patterns of vertices and edges
void readGraph(AdjacencyList *adjList) {
	ifstream dotfile;
	dotfile.open("graph.dot");
	string line;
	int lineNo = 0;
	if (dotfile.is_open()) {
		if (dotfile.is_open())
			cout << "File opened.\n";
		while (getline(dotfile, line)) {
			lineNo++;
			if (lineNo > VERTICES_BEGIN && lineNo < VERTICES_END) {
				string index;
				string temp;
				string position_x;
				string position_y;
				getline(dotfile, index, '[');
				getline(dotfile, temp, '"');
				getline(dotfile, temp, '"');
				getline(dotfile, temp, '"');
				getline(dotfile, position_x, ',');
				getline(dotfile, position_y, '"');

				pair<int, int> coordinates;
				coordinates.first = stoi(position_x);
				coordinates.second = stoi(position_y);
				vertex *newVertex = new vertex(stoi(index), coordinates);
				try {
					adjList->addVertex(newVertex);
				}
				catch (int e) {
					cout << "Exception occured. Exception Nr:" << e << '.\n';
				}
			}
			else if (lineNo >= VERTICES_END && lineNo < EDGES_END) {
				string path_beginning;
				string path_end;
				string temp;
				string weight;
				getline(dotfile, path_beginning, '-');
				getline(dotfile, temp, '-');
				getline(dotfile, path_end, '[');
				getline(dotfile, temp, '"');
				getline(dotfile, temp, '"');
				getline(dotfile, temp, '"');
				getline(dotfile, weight, '"');
				try {
					edge *newEdge = new edge((static_cast<vertex*>(adjList->getVertex(stoi(path_beginning)))),
						static_cast<vertex*>(adjList->getVertex(stoi(path_end))),
						stoi(weight));
					adjList->addEdge(newEdge);
				}
				catch (int e) {
					cout << "Exception occured. Exception Nr:" << e << '.\n';
				}
			}
		}
		dotfile.close();
		cout << "File closed.\n";
	}
	else if (!dotfile.is_open())
		cout << "File not open.\n";
} // readGraph function

void findPath(AdjacencyList *adjList, int startId, int endId) {
	auto t1 = chrono::steady_clock::now();
	A_star *pathfinder = new A_star(adjList);
	cout << "////////\n" << startId << " to " << endId << endl;
	pathfinder->algorithm_standard(adjList->getVertex(startId), adjList->getVertex(endId));
	auto t2 = chrono::steady_clock::now();
	cout << chrono::duration<double>(t2 - t1).count() << " seconds elapsed to find and print path.\n";
	cout << "While iterations: " << pathfinder->getIterationCount() << "\n";
	adjList->resetCosts();
	delete pathfinder;
} // findPath function

int main(int argc, char **argv) {
	AdjacencyList *adjList = new AdjacencyList();
	readGraph(adjList);
	findPath(adjList, 0, 60);
	findPath(adjList, 1, 61);
	delete adjList;
	return 0;
} // main