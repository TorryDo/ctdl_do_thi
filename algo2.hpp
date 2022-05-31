#pragma once

#include "list_vertices.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

#include "colors.hpp"			// Define all colors need
#include "constants.hpp"		// All constants go here
#include "global_variables.hpp" // All Global variables
#include "vertex.hpp"
#include "graph.hpp"

bool contains(std::vector<Vertex> seen, int id)
{
	for (auto v : seen)
	{
		if (v.id == id)
		{
			std::cout << "contains id" << endl;
			return true;
		}
	}
	return false;
}

bool contains(std::stack<Vertex> seeing, int id)
{
	while (!seeing.empty())
	{
		if (seeing.top().id == id)
		{
			return true;
		}
	}

	seeing.pop();

	return false;
}

SCCs tarjanDFS(Graph *graph, std::vector<Vertex> *seen, std::stack<Vertex> *seeing)
{
	SCCs sccs;

	for (int i = 0; i < graph->listVertices.num; i++)
	{
		int from = graph->listVertices.v[i]->id;

		if (
			graph->edges[seeing->top().id][i] > 0 &&
			!contains(*seen, from))
		{
			// if next node is available in stack, pop node in stack and push to vector
			// should complete one scc
			if (contains(*seeing, from))
			{
				while (seeing->top().id != i)
				{
					seen->push_back(seeing->top());
					seeing->pop();
				}
				seen->push_back(seeing->top());
				seeing->pop();
			}

			// after that, if stack is not empty, finding it's neighbor, if null, add it to seen
			// scc will be added to sccs variable

			// if edge not null, push into stack, now stack is [1, 2]
		}
	}

	return sccs;
}

SCCs tarjan(Graph graph)
{
	SCCs sccs;

	std::vector<Vertex> seen;
	std::stack<Vertex> seeing;

	while (!graph.listVertices.isEmpty())
	{
		seeing.push(*graph.listVertices.v[0]); // 2

		SCCs tempSCCs = tarjanDFS(&graph, &seen, &seeing);

		// tempSCCs has one scc, remove all scc vertex from listVertices of graph

		sccs.merge(tempSCCs);
	}

	return sccs;
}

void TPLT(Graph graph)
{
	if (graph.listVertices.isEmpty())
		return;

	// set id
	for (int i = 0; i < graph.listVertices.num; i++)
	{
		graph.listVertices.v[i]->id = i;
	}

	SCCs sccs = tarjan(graph);
}