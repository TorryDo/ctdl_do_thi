#pragma once
#include "list_vertices.hpp"
#include "button.hpp"

ListVertices listv;							// List vertices
int xCursor = xCURSOR;						// For printText()
int yCursor = yCURSOR;						// For printText()
int delayRunTime = 500;						// 500ms delay default
bool isSaved = 1;							// Check if Graph is saved or not
int trace[MAX_VERTEX]; 						// visited & save path...
float adjaGraph[MAX_VERTEX][MAX_VERTEX];	// Adjacency Matrix

HWND hwnd;									// Manage win32 api functions

// List button for select menu item 
Button menuButton[] =	{/*{120, 245, 220, 285, BUTTON_COLOR,"Luu File"},
						  {225, 245, 325, 285, BUTTON_COLOR,"Thoat"},*/
						  {419, 500, 479, 572, BUTTON_COLOR,"Them Dinh"},
						  {479, 500, 539, 572, BUTTON_COLOR,"Them/Xoa Cung"},
						  {539, 500, 599, 572, BUTTON_COLOR,"Doi Ten Dinh"},
						  {599, 500, 659, 572, BUTTON_COLOR,"Xoa Dinh"},
						  {659, 500, 719, 572, BUTTON_COLOR,"Di Chuyen"},
						  {719, 500, 779, 572, BUTTON_COLOR,"Xoa Do Thi"},
						  {779, 500, 839, 572, BUTTON_COLOR,"Giup Do"}
//						  {6, 11, 106, 49, BUTTON_COLOR,	"FILE"},
//						  {107, 11, 207, 49, BUTTON_COLOR,	"AGLO"},
//						  {207, 11, 307, 49, BUTTON_COLOR,	"Thoat"},
//						  {6, 50, 115, 90, BUTTON_COLOR,  	"Mo File"},
//						  {116, 50, 220, 90, BUTTON_COLOR,	"Luu File"},
//						  {6, 50, 115, 90, BUTTON_COLOR,  	"DFS"},
//						  {116, 50, 220, 90, BUTTON_COLOR,	"BFS"},
//						  {221, 50, 325, 90, BUTTON_COLOR,	"X->Y"},
//						  {6, 91, 115, 131, BUTTON_COLOR,	"DINH TRU"},
//						  {116, 91, 220, 131, BUTTON_COLOR,	"DINH THAT"},
//						  {221, 91, 325, 131, BUTTON_COLOR,	"CANH CAU"},
//						  {6, 132, 115, 172, BUTTON_COLOR,	"HAMILTON"},
//						  {116, 132, 220, 172, BUTTON_COLOR,"EULER"},
//						  {221, 132, 325, 172, BUTTON_COLOR,"TOPO SORT"},
//						  {6, 173, 115, 213, BUTTON_COLOR,	"TO MAU"},
//						  {116, 173, 220, 213, BUTTON_COLOR,"TPLT"}
						  };
