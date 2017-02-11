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
#include "graph.h"
#include "AdjacencyMatrix.h"

using namespace std;
//
//#include <unordered_map>
//using namespace std;
//
//// http://www.redblobgames.com/pathfinding/a-star/implementation.html
//template<typename L>
//struct SimpleGraph {
//	typedef L Location;
//	typedef typename vector<Location>::iterator iterator;
//	unordered_map<Location, vector<Location>> edges;
//
//	inline const vector<Location> neighbors(Location id) {
//		return edges[id];
//	}
//};

// E.G.
// { 0 , { 3 , 7 } };
//


int main(int argc, char **argv) {

	AdjacencyMatrix edgeMatrix(5);
	edgeMatrix.add_edge(1, 2, 
		2);
	edgeMatrix.add_edge(1, 4, 
		9);
	edgeMatrix.add_edge(1, 5, 
		2);
	edgeMatrix.add_edge(2, 3, 
		6);
	edgeMatrix.add_edge(2, 5, 
		4);
	edgeMatrix.add_edge(3, 1, 
		2);
	edgeMatrix.add_edge(5, 2,
		3);
	edgeMatrix.add_edge(4, 3, 
		2);
	//edgeMatrix.add_edge(-1, -1);
	edgeMatrix.display();
	cout << "\n\n";
	edgeMatrix.displayOnlyEdges();

	// idea 1
	/*
	* Instead of making empty matrix
	* make edge ""matrix""
	* 2d vector?
	* pair ? <int edgeNo, std::vector<std::pair<destination,weight>>
	* SPARSE GRAPH
	* https://en.wikipedia.org/wiki/Adjacency_list
	* Goodrich and tamassia adjacency list
	*/
	//std::vector<std::pair<int, std::vector<std::pair<int, int>>> edges;

	typedef std::pair<int, int> intPair;
	typedef std::pair<int, intPair> originDestinationPair;
	std::vector<std::vector<originDestinationPair>> vectorGraph;
	// Have I gone too far

	ifstream dotfile;
	//dotfile.open("graph.dot");
	string line;

	if (dotfile.is_open())
	{
	if (dotfile.is_open())
		cout << "File opened.\n";
		while (getline(dotfile, line))
		{
			cout << line << "\n";
		}
		dotfile.close();
	}
	if (!dotfile.is_open())
		cout << "File not open.\n";

	// +++
	/*std::pair<int, int> pairTest;
	pairTest.first = 1;
	vertex *TEST = new vertex(0, pairTest);*/
	//std::list<int> intList;
	//intList.push_back(1);
	//intList.push_back(2);
	//intList.push_back(3);

	//for (int n : intList)
	//	cout << n << " ";
	std::pair<int, int> pairTest;
	pairTest.first = 2;
	pairTest.second = 4;
	vertex *testVert1 = new vertex(0, pairTest);
	testVert1->displayVertexInfo();
	pairTest.first = 3;
	pairTest.second = 5;
	vertex *testVert2 = new vertex(1, pairTest);
	testVert2->displayVertexInfo();
	//testVert->addEdge(edge(verte))
	edge *testEdge = new edge(testVert1, testVert2, 10);
	//cout << testVert2 << endl;
	//testEdge->displayEdgeInfo();
	// +++
	return 0;
}