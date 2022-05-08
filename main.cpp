#include <fstream>				// For open & save file
#include <iostream>				// Debug std::cin std::cout
#include "queue.hpp"			// int queue using linked list
#include "stack.hpp"			// int stack also using linked list
#include "button.hpp"			// Button structures
#include "vertex.hpp"			// Vertex structures
#include "list_vertices.hpp"	// Manage all vertices
#include "helpers.hpp" 			// Basic functions & draw edges
#include "constants.hpp" 		// All constants go here
#include "global_variables.hpp" // All Global variables
#include "drawAll.hpp"			
#include "func.hpp"		
#include "top_bar.hpp"	
#include <thread>

using namespace std;

void listenMouseEvent();

void blahblah(int *newPos, int *oldPos);

int newPos(-1), oldPos(-1);

void onTopBarClickListener(int id){
	cout << "id is: " << id << endl;
	switch(id){
		
		case TOPBAR_FILE:
			refreshScreen();
			createDialogFile();
			addInsideFileButtons();
		break;
		
		case TOPBAR_ALGO:
			refreshScreen();
			createDialogAlgo();
			addInsideAlgoButtons();
		break;
		
		case TOPBAR_HELP:	
			refreshScreen();
			createDialogHelp();
		break;
		
		case TOPBAR_OUTSIDER:
			blahblah(&newPos, &oldPos);
			drawTopBar();
			break;
			
		case TOPBAR_OPEN_FILE:
			break;
		case TOPBAR_SAVE_FILE:
			break;
		case TOPBAR_CLOSE_FILE:
			break;
			
		case TOPBAR_ALGO_DFS:
			
			dfs();
			
			break;
			
		case TOPBAR_ALGO_BFS:
			break;
		case TOPBAR_ALGO_XtoY:	
			break;
		case TOPBAR_ALGO_DinhTru:	
			break;
		case TOPBAR_ALGO_DinhThat:	
			break;
		case TOPBAR_ALGO_CanhCau:	
			break;
		case TOPBAR_ALGO_Hamilton:	
			break;
		case TOPBAR_ALGO_Euler:	
			break;
		case TOPBAR_ALGO_TopoSort:	
			break;
		case TOPBAR_ALGO_TPLT:	
			break;
			
		default:
			break;
	}
	
//	refreshScreen();
	
}

thread mainThread;

int main(){
	initwindow(WINDOW_WIDTH + 5, WINDOW_HIGHT + 10);
	
    initScreen();
    initTopBar(onTopBarClickListener);

    listenMouseEvent();
    
	getch();
}


void listenMouseEvent()
{
	int x, y;//lua toa do
	
	while (1)
	{
		//if (getKey() == KEY_Q) quit();
		if (ismouseclick(WM_MOUSEMOVE)) // bat sk khi di chuyen chuot
		{
			getmouseclick(WM_MOUSEMOVE, x, y);
			update(oldPos, newPos, x, y);
		}
		if (ismouseclick(WM_LBUTTONDOWN))// bat sk khi nhan chuot trai
		{
			clearmouseclick(WM_LBUTTONDOWN);

			blahblah(&newPos, &oldPos);

		}
		delay(DELAY_VALUE);
	}
}

void blahblah(int *newPos, int *oldPos){
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