#pragma once
#include "list_vertices.hpp"
#include "button.hpp"

ListVertices listv;						 // List vertices
int xCursor = xCURSOR;					 // For printText()
int yCursor = yCURSOR;					 // For printText()
int delayRunTime = 500;					 // 500ms delay default
bool isSaved = 1;						 // Check if Graph is saved or not
int trace[MAX_VERTEX];					 // visited & save path...
float adjaGraph[MAX_VERTEX][MAX_VERTEX]; // Adjacency Matrix

HWND hwnd; // Manage win32 api functions

// List button for select menu item
Button menuButton[] = {
	{419, 568, 479, 640, BUTTON_COLOR, ""},
	{479, 568, 539, 640, BUTTON_COLOR, ""},
	{539, 568, 599, 640, BUTTON_COLOR, ""},
	{599, 568, 659, 640, BUTTON_COLOR, ""},
	{659, 568, 719, 640, BUTTON_COLOR, ""},
	{719, 568, 779, 640, BUTTON_COLOR, ""},
};
