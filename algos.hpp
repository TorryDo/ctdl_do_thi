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

const int IGNORE_REMOVE = -1;

void SCC();
void tarjanResult(stack &s, int stop, int components);
void tarjanVisit(int u, int *pioneer, int *queen, stack &s, int &count, int &components, bool callTarjanResult);
int tarjanAlgo(bool showResult, int remove = IGNORE_REMOVE);

void dfsVisited(int u);
void bfsVisited(int u);
void dijkstra(int start, int stop);
bool fordbellman(int start, int stop);
void showResultPathXY(double dist[], int start, int stop);
inline bool isEdgeAvailable(int start, int destination);

void dfs()
{
	if (isEmptyGraph())
		return;

	int start;

	if (chooseStartVertex(start, "Chon dinh bat dau: ", "DFS: "))
	{
		setArrayTo(visited, listv.num, 0);
		visited[start] = 1;
		dfsVisited(start);
		backToMenu();
	}
}

void dfsVisited(int u)
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
		// Them lan luot cac canh tu u den i vao stack
		for (int i = 0; i < listv.num; ++i)
			if (visited[i] == 0 && weightMatrix[u][i] != NO_EDGE_VALUE)
			{
				visited[i] = 1;
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
		setArrayTo(visited, listv.num, 0);
		visited[start] = 1;
		bfsVisited(start);
		backToMenu();
	}
}

void bfsVisited(int u)
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
		// Duyet lan luot theo queue
		for (int i = 0; i < listv.num; ++i)
			if (visited[i] == 0 && weightMatrix[u][i] != NO_EDGE_VALUE)
			{
				visited[i] = 1;
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
	backToMenu();
}

bool isNegativeWeight()
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			if (weightMatrix[i][j] != NO_EDGE_VALUE && weightMatrix[i][j] < 0)
				return 1;
	return 0;
}

void dijkstra(int start, int stop)
{
	const int &NUM = listv.num;
	// Su dung check de kiem tra dinh i da duoc duyet hay chua
	bool check[NUM];
	double total[NUM];
	setArrayTo(check, NUM, true);
	// Su dung visited luu dinh co duong di ngan nhat den no
	setArrayTo(visited, NUM, start);
	// Su dung total luu tong trong so tu start den stop
	setArrayTo(total, NUM, MAX_EDGE_VALUE);
	total[start] = 0;
	float d;
	int u;
	while (1)
	{
		d = MAX_EDGE_VALUE;
		u = -1;
		// Duyet dinh start
		for (int i = 0; i < NUM; ++i)
			if (check[i] && total[i] < d)
			{
				d = total[i];
				u = i;
			}
		if (u == -1 || u == stop)
			break;
		check[u] = 0;
		// Thay doi trong so nho nhat cua ban bac ra tu u den i
		for (int i = 0; i < NUM; ++i)
		{
			float weight = weightMatrix[u][i];
			if (check[i] && weight != NO_EDGE_VALUE && total[i] > d + weight)
			{
				total[i] = d + weight;
				visited[i] = u;
			}
		}
	}
	showResultPathXY(total, start, stop);
}
// Ham kiem tra do thi co trong so am hay khong
bool isNegativeCycle(double *dist)
{
	const int &NUM = listv.num;
	for (int i = 0; i < NUM; ++i)
		for (int j = 0; j < NUM; ++j)
			if (weightMatrix[j][i] != NO_EDGE_VALUE && dist[j] != MAX_EDGE_VALUE && dist[i] > dist[j] + weightMatrix[j][i])
				return true;
	return false;
}

bool fordbellman(int start, int stop)
{
	const int &NUM = listv.num;
	double total[NUM];
	setArrayTo(visited, NUM, start);
	// Gan MAX_EDGE_VALUE cho cac canh khong co duong di tu start, gan gia tri cho total[i] tu start di den
	for (int i = 0; i < NUM; ++i)
		total[i] = (weightMatrix[start][i] == 0) ? MAX_EDGE_VALUE : weightMatrix[start][i];
	total[start] = 0;
	// Duyet NUM - 1 lan de dam bao kiem tra tat ca cac dinh co duong di tu start den stop
	for (int k = 1; k < NUM - 1; ++k)
	{
		bool stop = 1;
		for (int i = 0; i < NUM; ++i)
		{
			// Neu i == start, tiep tuc den vong for ke tiep
			if (i == start)
				continue;
			for (int j = 0; j < NUM; ++j)
			{
				// neu i = j, tiep tuc den vong for ke tiep
				if (i == j)
					continue;
				double weight = weightMatrix[j][i];
				// Neu total[i] > total[j] + weight => cap nhat total[i] = total[j] + weight
				if (weight != 0 && total[i] > total[j] + weight && total[j] != NO_EDGE_VALUE)
				{
					total[i] = total[j] + weight;
					visited[i] = j;
					stop = 0;
				}
			}
		}
		// Neu khong thay doi thi break
		if (stop)
			break;
	}
	if (isNegativeCycle(total))
		return false;
	showResultPathXY(total, start, stop);
	return true;
}

bool kahn(int *in, int *listed)
{
	int const &NUM = listv.num;
	queue q;
	for (int i = 0; i < NUM; ++i)
		if (in[i] == 0)
			q.push(i);
	int u, count(0);
	while (!q.isEmpty())
	{
		u = q.pop();
		listed[count++] = u;
		for (int i = 0; i < NUM; ++i)
			if (weightMatrix[u][i] != NO_EDGE_VALUE)
				if (--in[i] == 0)
					q.push(i);
	}
	return (count == NUM);
}

void topoSort()
{
	if (isEmptyGraph())
		return;
	int const &NUM = listv.num;
	int in[NUM];
	int listed[NUM];
	// Tinh tong ban bac vao cua cac dinh
	for (int i = 0; i < NUM; ++i)
	{
		in[i] = 0;
		for (int j = 0; j < NUM; ++j)
			if (weightMatrix[j][i] != NO_EDGE_VALUE)
				++in[i];
	}
	setTextPrintStyle(TEXT_COLOR);
	if (kahn(in, listed))
	{
		printTextWl("Thu tu sap xep topo: ");
		for (int i = 0; i < NUM; ++i)
		{
			if (getKey() == KEY_ESC)
				break;
			listv.v[listed[i]]->show(VERTEX_VISTED_COLOR);
			setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
			printText(listv.v[listed[i]]->name);
			printText("->");
			delay(delayRunTime);
		}
		deleteText("->");
	}
	else
	{
		printText("Do thi khong ton tai chu trinh.");
	}

	backToMenu();
}

int tarjanAlgo(bool showResult, int remove)
{
	const int &VERTEX_NUM = listv.num;

	int pioneer[VERTEX_NUM] = {0};
	int king[VERTEX_NUM];

	setArrayTo(visited, VERTEX_NUM, 1);

	int id = 0, components = 0;
	stack seeing;

	if (remove != -1)
	{
		pioneer[remove] = 1;
		visited[remove] = 0;
	}

	for (int i = 0; i < VERTEX_NUM; ++i)
	{
		if (pioneer[i] == 0)
		{
			tarjanVisit(i, pioneer, king, seeing, id, components, showResult);
		}
	}

	return components;
}
void tarjanVisit(int u, int *pioneer, int *king, stack &seeing, int &id, int &components, bool canShowResult)
{

	king[u] = pioneer[u] = ++id;
	seeing.push(u);

	int v;

	for (v = 0; v < listv.num; ++v)
	{
		if (visited[v] != 0 && isEdgeAvailable(u, v)) // if ( node v not visited && edge u-v available ) 2-0
		{
			// if node v is not visited, return true
			if (pioneer[v] == 0)
			{
				tarjanVisit(v, pioneer, king, seeing, id, components, canShowResult);
			}

			king[u] = min(king[u], king[v]); // king[0] = 0
		}
	}

	// when find a new scc
	if (pioneer[u] == king[u])
	{
		++components;

		if (canShowResult)
		{
			tarjanResult(seeing, u, components);
		}
		else
		{
			do
			{
				v = seeing.pop();
				visited[v] = 0;
			} while (v != u);
		}
	}
}
void tarjanResult(stack &seeing, int root, int components)
{
	setTextPrintStyle(TEXT_COLOR);
	printText(components);
	printText(":(");

	int v;
	do
	{
		v = seeing.pop();
		visited[v] = 0;

		listv.v[v]->show(VERTEX_MORE_COLOR[components]);
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText(listv.v[v]->name);
		printText(",");

	} while (v != root);

	deleteText(",");
	printText(") ");
}
void SCC()
{
	if (isEmptyGraph())
		return;

	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac thanh phan lien thong manh:");

	int count = tarjanAlgo(1, -1); // return scc components amount

	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tong cong: ");
	printText(count);

	backToMenu();
}

void cutVertex()
{
	if (isEmptyGraph())
		return;

	int SCC = tarjanAlgo(0);

	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac dinh tru tim duoc:");

	int count = 0;
	for (int i = 0; i < listv.num; ++i)
	{
		int SCCAfterBeingRemoved = tarjanAlgo(0, i); // tarjan algorithm without show result & delete vertex i
		if (SCCAfterBeingRemoved > SCC)				 // is a cut vertex
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

	backToMenu();
}

inline bool isEdgeAvailable(int start, int destination)
{
	return (weightMatrix[start][destination] != NO_EDGE_VALUE);
}

bool dfsReachable(int start, int stop)
{
	setArrayTo(visited, listv.num, 0);

	stack seeing;
	seeing.push(start);

	visited[start] = 1;
	int numOfCheckedVertex(0);

	while (!seeing.isEmpty())
	{
		int current = seeing.pop();

		if (current == stop)
			return 1;

		++numOfCheckedVertex;

		for (int i = 0; i < listv.num; ++i)
			if (visited[i] == 0 && isEdgeAvailable(current, i))
			{
				visited[i] = 1;
				seeing.push(i);
			}
	}

	return numOfCheckedVertex == listv.num;
}

void dfsToCheckKnot(int start, int stop, bool *isKnotVertex)
{
	visited[start] = 1;

	if (start == stop) // found path start->stop
	{
		for (int i = 0; i < listv.num; ++i) // update isKnotVertex
			isKnotVertex[i] = visited[i] && isKnotVertex[i];
	}
	else
	{
		for (int i = 0; i < listv.num; ++i)
			if (visited[i] == 0 && isEdgeAvailable(start, i))
				dfsToCheckKnot(i, stop, isKnotVertex);
	}

	visited[start] = 0;
}
void knotVertex()
{
	if (isEmptyGraph())
		return;

	int start, stop, count(0);

	if (chooseTwoVertices(start, stop))
	{
		setTextPrintStyle(TEXT_COLOR);
		if (isEdgeAvailable(start, stop) || !dfsReachable(start, stop)) // if not contains knotVertex
		{
			printTextWl("");
			printText("Khong co dinh that (co duong di");
			printText("truc tiep hoac khong ton tai");
			printText("duong di)");
			printTextWlb("");
		}
		else
		{
			bool isKnotVertex[listv.num];
			setArrayTo(isKnotVertex, listv.num, true);		  // marked all as knot vertex
			setArrayTo(visited, listv.num, 0);				  // reset visited
			dfsToCheckKnot(start, stop, isKnotVertex);		  // set isKnotVertex
			isKnotVertex[start] = isKnotVertex[stop] = false; // start & stop are not knot of themself

			printTextWl("Cac dinh that tim duoc: ");

			for (int i = 0; i < listv.num; ++i)
				if (isKnotVertex[i]) // is knot vertex between start & stop
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

	backToMenu();
}

void bridgeEdge()
{
	if (isEmptyGraph())
		return;

	int SCC = tarjanAlgo(0);
	int count = 0;

	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac canh cau tim duoc:");

	for (int u = 0; u < listv.num; ++u)
		for (int v = 0; v < listv.num; ++v)
			if (isEdgeAvailable(u, v))
			{
				float backupWeight = weightMatrix[u][v];
				weightMatrix[u][v] = NO_EDGE_VALUE;

				int SCCAfterBeingRemovedEdge = tarjanAlgo(0);
				weightMatrix[u][v] = backupWeight;

				if (SCCAfterBeingRemovedEdge > SCC)
				{
					++count;

					drawEdge(u, v, EDGE_HIGHTLIGHT_COLOR);
					setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
					printText("(");
					printText(listv.v[u]->name);
					printText(",");
					printText(listv.v[v]->name);
					printText(");");
				}
			}

	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tong cong: ");
	printText(count);

	backToMenu();
}

void hamilton()
{
	MessageBox(hwnd, "Chua cap nhat", "Info", MB_APPLMODAL | MB_ICONINFORMATION);
}

void euler()
{
	MessageBox(hwnd, "Chua cap nhat", "Info", MB_APPLMODAL | MB_ICONINFORMATION);
}