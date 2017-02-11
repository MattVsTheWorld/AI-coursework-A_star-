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
	ifstream dotfile;
	//dotfile.open("graph.dot");
	string line;
	AdjacencyMatrix test(5);
	test.add_edge(1, 2, 2);
	test.add_edge(1, 4, 9);
	test.add_edge(1, 5, 2);
	test.add_edge(2, 3, 6);
	test.add_edge(2, 5, 4);
	test.add_edge(3, 1, 2);
	test.add_edge(5, 2, 3);
	test.add_edge(4, 3, 2);
	//test.add_edge(-1, -1);
	test.display();

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


	return 0;
}