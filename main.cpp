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
#include "open_file.hpp"
#include "save_file.hpp"

using namespace std;

void listenMouseEvent();

void blahblah(int *newPos, int *oldPos);

int newPos(-1), oldPos(-1);

void onTopBarClickListener(int id){
	
	cout << "tri - id is: " << id << endl;
	
	refreshScreen();
	
	switch(id){
		
		case TOPBAR_FILE:
			createDialogFile();
			addInsideFileButtons();
		break;
		
		case TOPBAR_ALGO:
			createDialogAlgo();
			addInsideAlgoButtons();
		break;
		
		case TOPBAR_HELP:	
			createDialogHelp();
		break;
		
		case TOPBAR_OUTSIDER:
			blahblah(&newPos, &oldPos);
			drawTopBar();
			break;
			
		case TOPBAR_OPEN_FILE:
			openFile(&listv);
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
	
}

thread mainThread;

int main(){
	initwindow(WINDOW_WIDTH + 5, WINDOW_HIGHT + 10);
	
    initScreen();
		
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
			
			bool c = onMouseClickInTopBar(x, y, onTopBarClickListener);
			
			if(c) continue;

			blahblah(&newPos, &oldPos);
			
			cout << "hoang" << x<< "-" << y << endl;
			
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