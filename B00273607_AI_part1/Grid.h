#pragma once
#ifndef GRID
#define GRID
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "AdjacencyList.h"
#define DEFAULTWEIGHT 2.0f

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
			edge *newEdges[9];
			newEdges[0] = new edge(grid->getVertex(i), grid->getVertex(i + 1), DEFAULTWEIGHT);
			newEdges[1] = new edge(grid->getVertex(i), grid->getVertex(i - 1), DEFAULTWEIGHT);
			newEdges[2] = new edge(grid->getVertex(i), grid->getVertex(i + gridSize), DEFAULTWEIGHT);
			newEdges[3] = new edge(grid->getVertex(i), grid->getVertex(i - gridSize), DEFAULTWEIGHT);
			newEdges[4] = new edge(grid->getVertex(i), grid->getVertex(i + 1 + gridSize), DEFAULTWEIGHT);
			newEdges[5] = new edge(grid->getVertex(i), grid->getVertex(i - 1 + gridSize), DEFAULTWEIGHT);
			newEdges[6] = new edge(grid->getVertex(i), grid->getVertex(i + 1 - gridSize), DEFAULTWEIGHT);
			newEdges[7] = new edge(grid->getVertex(i), grid->getVertex(i - 1 - gridSize), DEFAULTWEIGHT);
			for (int i = 0; i <8; i++)
				grid->addEdge(newEdges[i]);
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