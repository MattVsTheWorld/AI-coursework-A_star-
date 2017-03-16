#pragma once
#ifndef GRID
#define GRID
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "AdjacencyList.h"
#define DEFAULTWEIGHT 2.0f
#define DEFAULTRADIUS 2

//Node size = 2x2 seems fair

// Adj list; all nodes from -35 to +35, all 9 around neighbours
// for / for /
	//	add vertex
// add neighbours after
// right = i + size*2j
class Grid {
public:
	Grid() {  /* PARAMS */
		grid = new AdjacencyList();

		int index = 1;
		pair<int, int> coordinates;
		for (int i = -gridSize / 2; i < gridSize / 2; i += 2)
			for (int j = -gridSize / 2; j < gridSize / 2; j += 2)
			{

				coordinates.first = i;
				coordinates.second = j;
				vertex *newVertex = new vertex(index, coordinates, true);
				index++;
				try {
					grid->addVertex(newVertex);
				}
				catch (int e) {
					cout << "Exception occured. Exception Nr:" << e << '.\n';
				}
			}

		for (int i = 0; i < index; ++i)
		{
			try {
				vector <edge*> newEdges;
				//if (grid->getVertex(i)->getCoords().first + grid->getVertex(i+1)->getCoords.first) {
				// top row	
				//if (i % gridSize == 0)
				//	newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(i + 1), DEFAULTWEIGHT));
				//// bottom row
				//if ( i == 1 || (i-1) % gridSize == 0)
				//	newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(i - 1), DEFAULTWEIGHT));
				//// right edge
				//if (i < (gridSize*gridSize) && i >(gridSize*gridSize) - gridSize)
				//	newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(i + gridSize), DEFAULTWEIGHT));
				//// left edge
				//if (i > gridSize / 2)
				//	newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(i - gridSize), DEFAULTWEIGHT));


				//newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(i + 1 + gridSize), DEFAULTWEIGHT));
				//newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(i - 1 + gridSize), DEFAULTWEIGHT));
				//newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(i + 1 - gridSize), DEFAULTWEIGHT));
				//newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(i - 1 - gridSize), DEFAULTWEIGHT));
				//}
				newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(make_pair((grid->getVertex(i)->getCoords().first + DEFAULTRADIUS), (grid->getVertex(i)->getCoords().second))), DEFAULTWEIGHT));
				newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(make_pair((grid->getVertex(i)->getCoords().first + DEFAULTRADIUS), (grid->getVertex(i)->getCoords().second + DEFAULTRADIUS))), DEFAULTWEIGHT));
				newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(make_pair((grid->getVertex(i)->getCoords().first + DEFAULTRADIUS), (grid->getVertex(i)->getCoords().second - DEFAULTRADIUS))), DEFAULTWEIGHT));
				newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(make_pair((grid->getVertex(i)->getCoords().first - DEFAULTRADIUS), (grid->getVertex(i)->getCoords().second))), DEFAULTWEIGHT));
				newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(make_pair((grid->getVertex(i)->getCoords().first - DEFAULTRADIUS), (grid->getVertex(i)->getCoords().second + DEFAULTRADIUS))), DEFAULTWEIGHT));
				newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(make_pair((grid->getVertex(i)->getCoords().first - DEFAULTRADIUS), (grid->getVertex(i)->getCoords().second - DEFAULTRADIUS))), DEFAULTWEIGHT));
				newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(make_pair((grid->getVertex(i)->getCoords().first), (grid->getVertex(i)->getCoords().second + DEFAULTRADIUS))), DEFAULTWEIGHT));
				newEdges.push_back(new edge(grid->getVertex(i), grid->getVertex(make_pair((grid->getVertex(i)->getCoords().first), (grid->getVertex(i)->getCoords().second - DEFAULTRADIUS))), DEFAULTWEIGHT));



				for (const auto &it : newEdges)
					grid->getVertex(i)->addEdge(it);
			}
			catch (int e) {
				cout << "Exception occured. Exception Nr:" << e << '.\n';
			}
		}
		//for (const auto &it : grid)
		//	it
				//grid[i][j] = new Node(true, glm::vec3(i, 0, j));
	}
protected:
private:
	//	glm::vec2 gridWorldSize;
	//	float nodeMargin = 2;
	static const int gridSize = 70; //TODO change grid size
	AdjacencyList *grid;
};

#endif