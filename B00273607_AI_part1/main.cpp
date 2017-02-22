//
//=======================================================================
// B00273607
// AI coursework - part 1
// A* pathfinding
//=======================================================================
//

#include <iostream>
#include <fstream>
#include <string>
#include "AdjacencyList.h"
//#include "AdjacencyMatrix.h"
#include "A_star.h"
#include <chrono>

using namespace std;

// http://www.redblobgames.com/pathfinding/a-star/implementation.html
// didn't really use this

// rudimental parser, but works
#define VERTICES_BEGIN 2
#define VERTICES_END 67
#define EDGES_END 194
//TODO: improve to something more decent
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
				catch (int e){
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
	cout << "////////\n"<< startId <<" to "<< endId << endl;
	pathfinder->algorithm(adjList->getVertex(startId), adjList->getVertex(endId));
	auto t2 = chrono::steady_clock::now();
	cout << chrono::duration<double>(t2 - t1).count() << " seconds elapsed to find and print path.\n";
	cout << "While iterations: " << pathfinder->getIterationCount() << "\n";
	adjList->resetCosts();
	delete pathfinder;
} // findPath function

int main(int argc, char **argv) {

	/*
	* SPARSE GRAPH
	* https://en.wikipedia.org/wiki/Adjacency_list
	* Goodrich and tamassia adjacency list
	*/

	AdjacencyList *adjList = new AdjacencyList();
	readGraph(adjList);
	findPath(adjList, 0, 60);
	findPath(adjList, 1, 61);
	findPath(adjList, 0, 60);
	//findPath(adjList, 3, 57);
	//findPath(adjList, 1, 61);
	//findPath(adjList, 3, 57);

	delete adjList;
	return 0;
} // main