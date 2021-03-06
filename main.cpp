
#include "button.hpp"			// Button structures
#include "vertex.hpp"			// Vertex structures
#include "list_vertices.hpp"	// Manage all vertices
#include "helpers.hpp"			// Basic functions & draw edges
#include "constants.hpp"		// All constants go here
#include "global_variables.hpp" // All Global variables
#include "drawAll.hpp"
#include "func.hpp"

#include "top_bar.hpp"
#include "open_file.hpp"
#include "save_file.hpp"
#include "algos.hpp"

using namespace std;

int newPos(-1), oldPos(-1);

void listenMouseEvent();
void onMouseClick(int *newPos, int *oldPos);
void onTopBarClickListener(int id);

int main()
{

	initwindow(WINDOW_WIDTH + 5, WINDOW_HIGHT + 10);

	initScreen();

	listenMouseEvent();
}

void onTopBarClickListener(int id)
{

	refreshScreen();

	switch (id)
	{

	case TOPBAR_FILE:
		createDialogFile();
		showFileButtons();
		break;

	case TOPBAR_ALGO:
		createDialogAlgo();
		showAlgoButtons();
		break;

	case TOPBAR_HELP:
		help();
		break;

	case TOPBAR_OUTSIDER:
		drawTopBar();
		break;

	case TOPBAR_OPEN_FILE:
		openFile(&listv);
		refreshScreen();
		break;
	case TOPBAR_SAVE_FILE:
		saveFile(&listv);
		break;
	case TOPBAR_CLOSE_FILE:
		closeFile(&listv);
		break;

	case TOPBAR_ALGO_DFS:
		dfs();
		break;

	case TOPBAR_ALGO_BFS:
		bfs();
		break;

	case TOPBAR_ALGO_XtoY:
		shortestWayXY();
		break;

	case TOPBAR_ALGO_DinhTru:
		cutVertex();
		break;

	case TOPBAR_ALGO_DinhThat:
		knotVertex();
		break;

	case TOPBAR_ALGO_CanhCau:
		bridgeEdge();
		break;

	case TOPBAR_ALGO_Hamilton:
		hamilton();
		break;

	case TOPBAR_ALGO_Euler:
		euler();
		break;

	case TOPBAR_ALGO_TopoSort:
		topoSort();
		break;

	case TOPBAR_ALGO_TPLT:
		SCC();
		break;

	default:

		break;
	}
}

void listenMouseEvent()
{
	int x, y;

	while (1)
	{
		if (ismouseclick(WM_MOUSEMOVE)) // bat sk khi di chuyen chuot
		{
			checkIfMouseHoverInTopBar(x, y);

			getmouseclick(WM_MOUSEMOVE, x, y);
			update(oldPos, newPos, x, y);
		}
		if (ismouseclick(WM_LBUTTONDOWN)) // bat sk khi nhan chuot trai
		{
			clearmouseclick(WM_LBUTTONDOWN);

			if (onMouseClickInTopBar(x, y, onTopBarClickListener))
				continue;

			onMouseClick(&newPos, &oldPos);
		}
		delay(DELAY_VALUE);
	}
}

void onMouseClick(int *newPos, int *oldPos)
{
	clearmouseclick(WM_LBUTTONDOWN);
	if (*newPos != -1)
	{
		showChoseButton(*newPos);
		switchMenuItem(*newPos);
	}
	*oldPos = -1;
	refreshScreen();
	update(*oldPos, *newPos, mousex(), mousey());
}