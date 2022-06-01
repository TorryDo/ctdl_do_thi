#pragma once

#include "list_vertices.hpp"
#include <cstring>
#include <vector>

#include "colors.hpp"			// Define all colors need
#include "button.hpp"			// Button structures
#include "vertex.hpp"			// Vertex structures
#include "helpers.hpp"			// Basic functions & draw edges
#include "constants.hpp"		// All constants go here
#include "global_variables.hpp" // All Global variables

#include "queue.hpp" // int queue using linked list
#include "stack.hpp" // int stack also using linked list

using namespace std;

void SCC();
void tarjanResult(stack &s, int stop, int components);
void tarjanVisit(int u, int *disc, int *low, stack &s, int &count, int &components, bool callTarjanResult);
int tarjanAlgo(bool showResult, int remove);
void dfsTraveler(int u);
void bfsTraveler(int u);
void dijkstra(int start, int stop);
bool fordbellman(int start, int stop);
void showResultPathXY(double dist[], int start, int stop);

void dfs()
{
	if (isEmptyGraph())
		return;

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
				if (getKey() == KEY_ESC)
					return;
				delay(delayRunTime);
			}
		listv.v[u]->showActive(0);
		listv.v[u]->show(VERTEX_VISTED_COLOR);
	}
	deleteText("->");
}

void bfs()
{
	if (isEmptyGraph())
		return;
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
				if (getKey() == KEY_ESC)
					return;
				delay(delayRunTime);
			}
		listv.v[u]->showActive(0);
		listv.v[u]->show(VERTEX_VISTED_COLOR);
	}
	deleteText("->");
}

void shortestWayXY()
{
	if (isEmptyGraph())
		return;
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
	float d;
	int u;
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
		if (u == -1 || u == stop)
			break;
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
			if (adjaGraph[j][i] != NO_EDGE_VALUE && dist[j] != MAX_EDGE_VALUE && dist[i] > dist[j] + adjaGraph[j][i])
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
			if (i == start)
				continue;
			for (int j = 0; j < NUM; ++j)
			{
				if (i == j)
					continue;
				double weight = adjaGraph[j][i];
				if (weight != 0 && dist[i] > dist[j] + weight && dist[j] != NO_EDGE_VALUE)
				{
					dist[i] = dist[j] + weight;
					trace[i] = j;
					stop = 0;
				}
			}
		}
		if (stop)
			break; // if not update any dist ==> stop
	}
	if (isNegativeCycle(dist))
		return false;
	showResultPathXY(dist, start, stop);
	return true;
}

int tarjanAlgo(bool showResult, int remove)
{
	const int &NUM = listv.num;
	int disc[NUM];
	int low[NUM];
	setArrayTo(disc, NUM, 0);
	setArrayTo(trace, NUM, 1);
	int count(0), components(0);
	stack s;
	if (remove != -1)
	{
		disc[remove] = 1;  // ignore remove
		trace[remove] = 0; // ignore remove
	}
	for (int i = 0; i < NUM; ++i)
		if (disc[i] == 0)
			tarjanVisit(i, disc, low, s, count, components, showResult);
	return components;
}
void tarjanVisit(int u, int *disc, int *low, stack &s, int &count, int &components, bool callTarjanResult)
{
	low[u] = disc[u] = ++count;
	s.push(u);
	int v;
	for (v = 0; v < listv.num; ++v)
		if (trace[v] != 0 && adjaGraph[u][v] != NO_EDGE_VALUE)
			if (disc[v] != 0)
				low[u] = minn(low[u], disc[v]);
			else
			{
				tarjanVisit(v, disc, low, s, count, components, callTarjanResult);
				low[u] = minn(low[u], low[v]);
			}
	if (disc[u] == low[u])
	{
		++components;
		if (callTarjanResult)
			tarjanResult(s, u, components);
		else
			do
			{
				v = s.pop();
				trace[v] = 0;
			} while (v != u);
	}
}
void tarjanResult(stack &s, int stop, int components)
{
	setTextPrintStyle(TEXT_COLOR);
	printText(components);
	printText(":(");
	int v;
	do
	{
		v = s.pop();
		trace[v] = 0;
		listv.v[v]->show(VERTEX_MORE_COLOR[components]);
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText(listv.v[v]->name);
		printText(",");

	} while (v != stop);
	deleteText(",");
	printText(") ");
}
void SCC()
{
	if (isEmptyGraph())
		return;
	// listv.showAll(VERTEX_COLOR_0);
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac thanh phan lien thong manh:");
	int count = tarjanAlgo(1, 1); // Use tarjan algorithm to calculate SCC & show result
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tong cong: ");
	printText(count);
	return backToMenu();
}

void cutVertex()
{
	if (isEmptyGraph())
		return;
	int SCC = tarjanAlgo(0, 1);
	int count(0);
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac dinh tru tim duoc:");
	for (int i = 0; i < listv.num; ++i)
	{
		int SCCAfterRemove = tarjanAlgo(0, i); // tarjan algorithm without show result & delete vertex i
		if (SCCAfterRemove > SCC)			   // is a cut vertex
		{
			listv.v[i]->show(VERTEX_DELETE_COLOR);
			setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
			printText(listv.v[i]->name);
			printText(", ");
			++count;
		}
	}
	deleteText(", ");
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tong cong: ");
	printText(count);
	return backToMenu();
}
bool dfsToCheckConnected(bool (*checkEdge)(int, int), int start, int stop)
{
	setArrayTo(trace, listv.num, 0);
	stack s;
	s.push(start);
	trace[start] = 1;
	int numOfCheckedVertex(0);
	while (!s.isEmpty())
	{
		start = s.pop();
		if (start == stop)
			return 1;
		++numOfCheckedVertex;
		for (int i = 0; i < listv.num; ++i)
			if (trace[i] == 0 && checkEdge(start, i))
			{
				trace[i] = 1;
				s.push(i);
			}
	}
	return (numOfCheckedVertex == listv.num);
}
inline bool isExistDirectedEdge(int v1, int v2)
{
	return (adjaGraph[v1][v2] != NO_EDGE_VALUE);
}
void dfsToCheckKnot(int start, int stop, bool *mark)
{
	trace[start] = 1;
	if (start == stop)						// found path start->stop
		for (int i = 0; i < listv.num; ++i) // update mark
			mark[i] = trace[i] && mark[i];
	else
	{
		for (int i = 0; i < listv.num; ++i)
			if (trace[i] == 0 && adjaGraph[start][i] != NO_EDGE_VALUE)
				dfsToCheckKnot(i, stop, mark);
	}
	trace[start] = 0;
}
void knotVertex()
{
	if (isEmptyGraph())
		return;
	int start, stop, count(0);
	if (chooseTwoVertices(start, stop))
	{
		setTextPrintStyle(TEXT_COLOR);
		if (adjaGraph[start][stop] != NO_EDGE_VALUE ||
			!dfsToCheckConnected(isExistDirectedEdge, start, stop))
			printText("Khong co dinh that (co duong di truc tiep hoac khong ton tai duong di).");
		else
		{
			bool mark[listv.num];
			setArrayTo(mark, listv.num, true); // marked all as knot vertex
			setArrayTo(trace, listv.num, 0);   // reset visited
			dfsToCheckKnot(start, stop, mark); // calculate mark as result
			mark[start] = mark[stop] = false;  // start & stop are not knot themself
			printTextWl("Cac dinh that tim duoc: ");
			for (int i = 0; i < listv.num; ++i)
				if (mark[i]) // is knot vertex between start & stop
				{
					++count;
					listv.v[i]->show(VERTEX_DELETE_COLOR);
					setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
					printText(listv.v[i]->name);
					printText(", ");
				}
			deleteText(", ");
			setTextPrintStyle(TEXT_COLOR);
			printTextWlb("Tong cong: ");
			printText(count);
		}
	}
	return backToMenu();
}

void bridgeEdge()
{
	if (isEmptyGraph())
		return;
	int SCC = tarjanAlgo(0, 1); // first find current SCC
	int count(0);
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac canh cau tim duoc:");
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			if (adjaGraph[i][j] != NO_EDGE_VALUE)
			{
				float backup = adjaGraph[i][j];			   // backup edge
				adjaGraph[i][j] = NO_EDGE_VALUE;		   // Delete edge
				int SCCAfterRemoveEdge = tarjanAlgo(0, 1); // recalculate SCC
				adjaGraph[i][j] = backup;				   // restore
				if (SCCAfterRemoveEdge > SCC)			   // is strong bridge
				{
					++count;
					drawEdge(i, j, EDGE_HIGHTLIGHT_COLOR);
					setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
					printText("(");
					printText(listv.v[i]->name);
					printText(",");
					printText(listv.v[j]->name);
					printText(");");
				}
			}
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tong cong: ");
	printText(count);
	return backToMenu();
}

bool numbering(int *degIn, int *order) // Kahns algorith
{
	int const &NUM = listv.num;
	queue q;
	for (int i = 0; i < NUM; ++i)
		if (degIn[i] == 0)
			q.push(i);
	int u, count(0);
	while (!q.isEmpty())
	{
		u = q.pop();
		order[count++] = u;
		for (int i = 0; i < NUM; ++i)
			if (adjaGraph[u][i] != NO_EDGE_VALUE)
				if (--degIn[i] == 0)
					q.push(i);
	}
	return (count == NUM);
}

void topoSort()
{
	if (isEmptyGraph())
		return;
	int const &NUM = listv.num;
	int degIn[NUM];
	int order[NUM];
	for (int i = 0; i < NUM; ++i)
	{
		degIn[i] = 0;
		for (int j = 0; j < NUM; ++j)
			if (adjaGraph[j][i] != NO_EDGE_VALUE)
				++degIn[i];
	}
	setTextPrintStyle(TEXT_COLOR);
	if (numbering(degIn, order))
	{
		printTextWl("Thu tu sap xep topo: ");
		for (int i = 0; i < NUM; ++i)
		{
			if (getKey() == KEY_ESC)
				break;
			listv.v[order[i]]->show(VERTEX_VISTED_COLOR);
			setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
			printText(listv.v[order[i]]->name);
			printText("->");
			delay(delayRunTime);
		}
		deleteText("->");
	}
	else
		printText("Do thi khong ton tai chu trinh.");
	return backToMenu();
}
