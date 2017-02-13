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

#define VERTICES_BEGIN 2
#define VERTICES_END 67
#define EDGES_END 194

int main(int argc, char **argv) {

	//AdjacencyMatrix edgeMatrix(5);
	//edgeMatrix.add_edge(1, 2, 
	//	2);
	//edgeMatrix.add_edge(1, 4, 
	//	9);
	//edgeMatrix.add_edge(1, 5, 
	//	2);
	//edgeMatrix.add_edge(2, 3, 
	//	6);
	//edgeMatrix.add_edge(2, 5, 
	//	4);
	//edgeMatrix.add_edge(3, 1, 
	//	2);
	//edgeMatrix.add_edge(5, 2,
	//	3);
	//edgeMatrix.add_edge(4, 3, 
	//	2);
	////edgeMatrix.add_edge(-1, -1);
	//edgeMatrix.display();
	//cout << "\n\n";
	//edgeMatrix.displayOnlyEdges();

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

	//typedef std::pair<int, int> intPair;
	//typedef std::pair<int, intPair> originDestinationPair;
	//std::vector<std::vector<originDestinationPair>> vectorGraph;
	// Have I gone too far

	AdjacencyList *adjList = new AdjacencyList();

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
		//		cout << index << " - " << position_x << "," << position_y << endl;

				pair<int, int> coordinates;
				coordinates.first = stoi(position_x);
				coordinates.second = stoi(position_y);
				vertex *newVertex = new vertex(stoi(index), coordinates);
				adjList->addVertex(newVertex);// ? cout << "Added vertex\n" : cout << "Unable to add vertex\n";
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
				//cout << stoi(path_beginning) << "<>" << stoi(path_end) << " || " << stoi(weight) << endl;
				//edge *testEdge1 = new edge(testVert1, testVert2, 10);
				//adjList->addEdge()

				try {
					edge *newEdge = new edge(((vertex*)adjList->getVertex(stoi(path_beginning))), 
						(vertex*)adjList->getVertex(stoi(path_end)), 
						stoi(weight));
					adjList->addEdge(newEdge);
				/*	((vertex*)adjList->getVertex(stoi(path_beginning)));
					((vertex*)adjList->getVertex(stoi(path_end)));*/
				}
				catch (int e)
				{
					cout << "Exception occured. Exception Nr: " << e << '\n';
				}
			}
			//cout << line << "\n";
			
		}
	
		dotfile.close();
		cout << "File closed.\n";
	}
	else if (!dotfile.is_open())
		cout << "File not open.\n";

	adjList->displayVertices();

	// +++ VIP
	//std::pair<int, int> pairTest;
	//pairTest.first = 2;
	//pairTest.second = 4;
	//vertex *testVert1 = new vertex(0, pairTest);
	//testVert1->displayVertexInfo();
	//pairTest.first = 3;
	//pairTest.second = 5;
	//vertex *testVert2 = new vertex(1, pairTest);
	//pairTest.first = 6;
	//pairTest.second = 9;
	//vertex *testVert3 = new vertex(2, pairTest);
	//edge *testEdge1 = new edge(testVert1, testVert2, 10);
	//edge *testEdge2 = new edge(testVert1, testVert3, 15);
	//edge *testEdge3 = new edge(testVert2, testVert3, 12);
	//cout << "\n//// NOW FOR THE LIST ///\n";
	//AdjacencyList *adjTest = new AdjacencyList();
	//adjTest->addVertex(testVert1);
	//adjTest->addVertex(testVert2);
	//try {
	//	adjTest->addEdge(testEdge1);
	//}
	//catch (int e) {
	//	cout << "Out of bounds exception occured. Exception n: " << e << '\n';
	//}	
	//try {
	//adjTest->addEdge(testEdge3);
	//}
	//catch (int e) {
	//	cout << "Out of bounds exception occured. Exception n: " << e << '\n';
	//}
	//adjTest->addVertex(testVert3);
	//try {
	//adjTest->addEdge(testEdge2);
	//}
	//catch (int e) {
	//	cout << "Out of bounds exception occured. Exception n: " << e << '\n';
	//}
	//try {
	//adjTest->addEdge(testEdge3);
	//}
	//catch (int e) {
	//	cout << "Out of bounds exception occured. Exception n: " << e << '\n';
	//}
	//adjTest->displayVertices();
	//cout << "\n//// CATCHING SOME ERRORS ///\n";
	//try {
	//	((vertex*)adjTest->getVertex(0))->displayVertexInfo();
	//}
	//catch (int e)
	//{
	//	cout << "Out of bounds exception occured. Exception n: " << e << '\n';
	//}
	//try {
	//	((vertex*)adjTest->getVertex(4))->displayVertexInfo();
	//}
	//catch (int e)
	//{
	//	cout << "Out of bounds exception occured. Exception Nr: " << e << '\n';
	//}


//	adjTest->addEdge(testEdge);
	
	// +++
	return 0;
}