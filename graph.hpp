#pragma once

#include <vector>
#include <iostream>

#include "constants.hpp"
#include "list_vertices.hpp"
//#include ""

using namespace std;

class Graph
{
public:
	int num = 0;
	float edges[MAX_VERTEX][MAX_VERTEX];
	ListVertices listVertices;

	void print()
	{
		cout << "edges are: " << endl;

		for (int i = 0; i < MAX_VERTEX; i++)
		{
			for (int j = 0; j < MAX_VERTEX; j++)
			{
				cout << edges[i][j];
			}
			cout << endl;
		}

		cout << "list vertices are: " << endl;

		for (auto v : listVertices.v)
		{
			cout << v << " ";
		}
	}
};

class SCCs
{
public:
	int count;
	vector<vector<Vertex>> vertex;

	SCCs() {}

	void push(vector<Vertex> v)
	{
		vertex.push_back(v);
	}

	void merge(SCCs sccs)
	{
		this->count = sccs.count;
		for (auto v : sccs.vertex)
		{
			vertex.push_back(v);
		}
	}

	void print()
	{
		cout << "count is: " << count << endl;

		for (auto vt : vertex)
		{
			cout << "vertex ";
			for (auto v : vt)
			{
				cout << v.id << " - ";
			}
			cout << endl;
		}
	}
};