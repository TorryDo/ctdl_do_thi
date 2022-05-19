#pragma once

#include "list_vertices.hpp"
#include <cstring>
#include "colors.hpp"			// Define all colors need
#include "button.hpp"			// Button structures
#include "vertex.hpp"			// Vertex structures
#include "helpers.hpp" 			// Basic functions & draw edges
#include "constants.hpp" 		// All constants go here
#include "global_variables.hpp"// All Global variables

#include "queue.hpp"			// int queue using linked list
#include "stack.hpp"			// int stack also using linked list

using namespace std;

void dfs()
{
	if (isEmptyGraph()) return;
	int start;
	if (chooseStartVertex(start, "Chon dinh bat dau: ", "DFS: "))
	{
		setArrayTo(trace, listv.num, 0);
		trace[start] = 1;
		dfsTraveler(start);
		return backToMenu();
	}
}

void dfsTraveler(int u)
{
	stack s;
	s.push(u);
	while (!s.isEmpty())
	{
		u = s.pop();
		listv.v[u]->show(VERTEX_VISTED_COLOR);
		listv.v[u]->showActive(1);
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText(listv.v[u]->name);
		printText("->");
		delay(delayRunTime);
		for (int i = 0; i < listv.num; ++i)
			if (trace[i] == 0 && adjaGraph[u][i] != NO_EDGE_VALUE)
			{
				trace[i] = 1;
				s.push(i);
				drawEdge(u, i, EDGE_VISTED_COLOR);
				listv.v[i]->show(VERTEX_QUEUE_COLOR);
				if (getKey() == KEY_ESC) return;
				delay(delayRunTime);
			}
		listv.v[u]->showActive(0);
		listv.v[u]->show(VERTEX_VISTED_COLOR);
	}
	deleteText("->");
}

void bfs()
{
	if (isEmptyGraph()) return;
	int start;
	if (chooseStartVertex(start, "Chon dinh bat dau: ", "BFS: "))
	{
		setArrayTo(trace, listv.num, 0);
		trace[start] = 1;
		bfsTraveler(start);
		return backToMenu();
	}
}

void bfsTraveler(int u)
{
	queue q;
	q.push(u);
	while (!q.isEmpty())
	{
		u = q.pop();
		listv.v[u]->show(VERTEX_VISTED_COLOR);
		listv.v[u]->showActive(1);
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText(listv.v[u]->name);
		printText("->");
		delay(delayRunTime);
		for (int i = 0; i < listv.num; ++i)
			if (trace[i] == 0 && adjaGraph[u][i] != NO_EDGE_VALUE)
			{
				trace[i] = 1;
				q.push(i);
				drawEdge(u, i, EDGE_VISTED_COLOR);
				listv.v[i]->show(VERTEX_QUEUE_COLOR);
				if (getKey() == KEY_ESC) return;
				delay(delayRunTime);
			}
		listv.v[u]->showActive(0);
		listv.v[u]->show(VERTEX_VISTED_COLOR);
	}
	deleteText("->");
}

void shortestWayXY(){
	if (isEmptyGraph()) return;
	int start, stop;
	if (chooseTwoVertices(start, stop))
	{
		setTextPrintStyle(TEXT_COLOR);
		if (!isNegativeWeight())
		{
			printTextWl("Khoi chay thuat toan Dijkstra:");
			dijkstra(start, stop);
		}
		else
		{
			// if graph doesn't contain negative cycle
			// run algorimth shortestPathFasterAlgo(start, stop)
			// instead of fordbellman
			printTextWl("Khoi chay thuat toan FordBellman: ");
			if (!fordbellman(start, stop))
				printTextWlb("Do thi ton tai chu trinh am.");
		} 
	}
	return backToMenu();
}

bool isNegativeWeight()
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			if (adjaGraph[i][j] != NO_EDGE_VALUE && adjaGraph[i][j] < 0)
				return 1;
	return 0;
}
void dijkstra(int start, int stop)
{
	const int &NUM = listv.num;
	bool free[NUM];
	double dist[NUM];
	setArrayTo(free, NUM, true);
	setArrayTo(trace, NUM, start);
	setArrayTo(dist, NUM, MAX_EDGE_VALUE);
	dist[start] = 0;
	float d; int u;
	while (1)
	{
		d = MAX_EDGE_VALUE;
		u = -1;
		for (int i = 0; i < NUM; ++i)
			if (free[i] && dist[i] < d)
			{
				d = dist[i];
				u = i;
			}
		if (u == -1 || u == stop) break;
		free[u] = 0;
		for (int i = 0; i < NUM; ++i)
		{
			float weight = adjaGraph[u][i];
			if (free[i] && weight != NO_EDGE_VALUE && dist[i] > d + weight)
			{
				dist[i] = d + weight;
				trace[i] = u;
			}
		}
	}
	showResultPathXY(dist, start, stop);
}

bool isNegativeCycle(double *dist)
{
	const int &NUM = listv.num;
	for (int i = 0; i < NUM; ++i)
		for (int j = 0; j < NUM; ++j)
			if (adjaGraph[j][i] != NO_EDGE_VALUE && dist[j] != MAX_EDGE_VALUE 
				&& dist[i] > dist[j] + adjaGraph[j][i])
				return true;
	return false;
}

bool fordbellman(int start, int stop)
{
	const int &NUM = listv.num;
	double dist[NUM];
	setArrayTo(trace, NUM, start);
	for (int i = 0; i < NUM; ++i)
		dist[i] = (adjaGraph[start][i] == 0) ? MAX_EDGE_VALUE : adjaGraph[start][i];
	dist[start] = 0;
	for (int k = 1; k < NUM - 1; ++k)
	{
		bool stop = 1;
		for (int i = 0; i < NUM; ++i)
		{
			if (i == start) continue;
			for (int j = 0; j < NUM; ++j)
			{
				if (i == j) continue;
				double weight = adjaGraph[j][i];
				if (weight != 0 && dist[i] > dist[j] + weight && dist[j] != NO_EDGE_VALUE)
				{
					dist[i] = dist[j] + weight;
					trace[i] = j;
					stop = 0;
				}
			}
		}
		if (stop) break; // if not update any dist ==> stop
	}
	if (isNegativeCycle(dist)) return false;
	showResultPathXY(dist, start, stop);
	return true;
}
