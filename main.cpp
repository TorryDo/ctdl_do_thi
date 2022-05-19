
#include <iostream>				// Debug std::cin std::cout
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
#include "algos.hpp"

using namespace std;

int newPos(-1), oldPos(-1);


void listenMouseEvent();
void onMouseClick(int *newPos, int *oldPos);
void onTopBarClickListener(int id);


int main(){
	
	initwindow(WINDOW_WIDTH + 5, WINDOW_HIGHT + 10);
	
    initScreen();
		
    listenMouseEvent();
    
}


void onTopBarClickListener(int id){
		
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
//			onMouseClick(&newPos, &oldPos);
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
			break;
		case TOPBAR_ALGO_DinhThat:	
			break;
		case TOPBAR_ALGO_CanhCau:
//			canhCau(&listv);
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

void listenMouseEvent()
{
	int x, y;
	
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

			onMouseClick(&newPos, &oldPos);
						
		}
		delay(DELAY_VALUE);
	}
	
}

void onMouseClick(int *newPos, int *oldPos){
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