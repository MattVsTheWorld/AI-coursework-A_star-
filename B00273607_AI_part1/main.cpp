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
#include <vector>
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

void readGraph(AdjacencyList *adjList) {
	ifstream dotfile;
	dotfile.open("graph.dot");
	string line;
	int lineNo = 0;
	if (dotfile.is_open()) {
		if (dotfile.is_open())
			cout << "File opened.\n";
		while (getline(dotfile, line))
		{
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
				catch (int e)
				{
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
					edge *newEdge = new edge(((vertex*)adjList->getVertex(stoi(path_beginning))),
						(vertex*)adjList->getVertex(stoi(path_end)),
						stoi(weight));
					adjList->addEdge(newEdge);
				}
				catch (int e)
				{
					cout << "Exception occured. Exception Nr:" << e << '.\n';
				}
			}

		}

		dotfile.close();
		cout << "File closed.\n";
	}
	else if (!dotfile.is_open())
		cout << "File not open.\n";
}

int main(int argc, char **argv) {

	/*
	* SPARSE GRAPH
	* https://en.wikipedia.org/wiki/Adjacency_list
	* Goodrich and tamassia adjacency list
	*/

	AdjacencyList *adjList = new AdjacencyList();

	readGraph(adjList);

	// !!
	auto t1 = std::chrono::steady_clock::now();
	// !!
	
	A_star *pathfinder = new A_star(adjList);
	cout << "////////\n0 to 60\n";
	pathfinder->algorithm(adjList->getVertex(0), adjList->getVertex(60));
	/*cout << "Iterations: " << pathfinder->getIterationCount() << "\n";*/
	delete pathfinder;
	
	// !!
	auto t2 = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration<double>(t2-t1).count() << " seconds.\n";
	// !!

	//A_star *_pathfinder = new A_star(adjList);
	//cout << "////////\n12 to 58\n";
	//_pathfinder->algorithm(adjList->getVertex(12), adjList->getVertex(58));
	///*cout << "Iterations: " << pathfinder->getIterationCount() << "\n";*/
	//delete _pathfinder;

	//A_star *_pathfinder = new A_star(adjList);
	//cout << "////////\n1 to 61\n";
	//_pathfinder->algorithm(adjList->getVertex(1), adjList->getVertex(61));
	///*cout << "Iterations: " << _pathfinder->getIterationCount() << "\n";*/
	//delete _pathfinder;

	//A_star *__pathfinder = new A_star(adjList);
	//cout << "////////\n2 to 57\n";
	//__pathfinder->algorithm(adjList->getVertex(2), adjList->getVertex(57));
	///*cout << "Iterations: " << __pathfinder->getIterationCount() << "\n";*/
	//delete __pathfinder;

	delete adjList;
	return 0;
}