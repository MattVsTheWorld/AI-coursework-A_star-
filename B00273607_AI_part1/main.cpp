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
//#include <queue>
//#include <functional>

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
	pathfinder->algorithm(adjList->getVertex(startId), adjList->getVertex(endId));
	auto t2 = chrono::steady_clock::now();
	cout << chrono::duration<double>(t2 - t1).count() << " seconds elapsed to find and print path.\n";
	cout << "While iterations: " << pathfinder->getIterationCount() << "\n";
	adjList->resetCosts();
	delete pathfinder;
} // findPath function

struct comp
{
	bool operator()(const pair<int, char>& pair1, const pair<int, char>& pair2)
	{
		return pair1.first < pair2.first;
	}
};


int main(int argc, char **argv) {

	/*
	* SPARSE GRAPH
	* https://en.wikipedia.org/wiki/Adjacency_list
	* Goodrich and tamassia adjacency list
	*/

	AdjacencyList *adjList = new AdjacencyList();
	readGraph(adjList);

	//cout << "Priority queue testing..." << endl;
	//priority_queue<int, vector<int>, greater<int>> q;
	//for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
	//	q.push(n);

	//while (!q.empty()) {
	//	cout << q.top() << " ";
	//	q.pop();
	//}
	//cout << '\n';
	//cout << "Done testing..." << endl;
	//cout << "\\\\\\\\\\\\\\\\ \n";
	vector < pair<int, char> > v;
	v.push_back(make_pair(0, 'a'));
	v.push_back(make_pair(2, 'b'));
	v.push_back(make_pair(6, 'c'));
	v.push_back(make_pair(4, 'd'));
	v.push_back(make_pair(3, 'e'));
	v.push_back(make_pair(1, 'f'));


	make_heap(v.begin(), v.end(), comp());

	//cout << "Max:" << v.front().first << endl;
	sort_heap(v.begin(), v.end(), comp());

	for (const auto it : v)
		cout << it.first << "-" << it.second << " ";

	cout << endl;
	//pop_heap(v.begin(), v.end(), comp()); v.pop_back();
	v.push_back(make_pair(5, 'g')); //push_heap(v.begin(), v.end(), comp());
	make_heap(v.begin(), v.end(), comp());
	sort_heap(v.begin(), v.end(), comp());
	
	for (const auto it : v)
		cout << it.first << "-" << it.second << " ";
	cout << endl;

	//findPath(adjList, 0, 60);
	//findPath(adjList, 1, 61);
	//findPath(adjList, 0, 60);
	//findPath(adjList, 3, 57);
	//findPath(adjList, 1, 61);
	//findPath(adjList, 3, 57);

	delete adjList;
	return 0;
} // main