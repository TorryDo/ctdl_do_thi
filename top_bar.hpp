#pragma once

#include <thread>
#include <vector>
#include "drawAll.hpp"
#include "text_button.hpp"
#define COLOR(r,g,b) (0x04000000 | RGB(r,g,b))


const int TOP_BAR_COLOR = COLOR(134, 198, 244);
const int HIGHLIGHT_TEXT_COLOR = YELLOW;

using namespace std;

// top bar

const int TOPBAR_LEFT = 0;
const int TOPBAR_TOP = 0;
const int TOPBAR_RIGHT = WINDOW_WIDTH;
const int TOPBAR_BOTTOM = 40;

const int BUTTON_WIDTH = 120;
const int BUTTON_HEIGHT = 40;

const int BUTTON_FILE_LEFT = 0;
const int BUTTON_FILE_RIGHT = BUTTON_WIDTH;

const int BUTTON_ALGO_LEFT = BUTTON_FILE_RIGHT;
const int BUTTON_ALGO_RIGHT = BUTTON_FILE_RIGHT + BUTTON_WIDTH;

const int BUTTON_HELP_LEFT = BUTTON_ALGO_RIGHT;
const int BUTTON_HELP_RIGHT = BUTTON_ALGO_RIGHT + BUTTON_WIDTH;

const int DIALOG_FILE_RIGHT = 200;
const int DIALOG_FILE_BOTTOM = TOPBAR_BOTTOM + 120;

const int DIALOG_ALGO_RIGHT = BUTTON_FILE_RIGHT + (BUTTON_WIDTH * 3);
const int DIALOG_ALGO_BOTTOM = 300;

const int DIALOG_HELP_RIGHT = BUTTON_ALGO_RIGHT + 200;
const int DIALOG_HELP_BOTTOM = 300;

// button open file
const int BUTTON_OPEN_FILE_LEFT = BUTTON_FILE_LEFT + 5;
const int BUTTON_OPEN_FILE_RIGHT = DIALOG_FILE_RIGHT - 5;
const int BUTTON_OPEN_FILE_TOP = TOPBAR_BOTTOM;
const int BUTTON_OPEN_FILE_BOTTOM = BUTTON_OPEN_FILE_TOP + BUTTON_HEIGHT;

const int BUTTON_SAVE_FILE_LEFT = BUTTON_FILE_LEFT + 5;
const int BUTTON_SAVE_FILE_RIGHT = DIALOG_FILE_RIGHT - 5;
const int BUTTON_SAVE_FILE_TOP = BUTTON_OPEN_FILE_BOTTOM;
const int BUTTON_SAVE_FILE_BOTTOM = BUTTON_SAVE_FILE_TOP + BUTTON_HEIGHT;

const int BUTTON_CLOSE_FILE_LEFT = BUTTON_FILE_LEFT + 5;
const int BUTTON_CLOSE_FILE_RIGHT = DIALOG_FILE_RIGHT - 5;
const int BUTTON_CLOSE_FILE_TOP = BUTTON_SAVE_FILE_BOTTOM;
const int BUTTON_CLOSE_FILE_BOTTOM = BUTTON_CLOSE_FILE_TOP + BUTTON_HEIGHT;

// button algo file
const int BUTTON_DFS_LEFT = BUTTON_ALGO_LEFT;
const int BUTTON_DFS_RIGHT = BUTTON_DFS_LEFT + BUTTON_WIDTH;
const int BUTTON_DFS_TOP = TOPBAR_BOTTOM;
const int BUTTON_DFS_BOTTOM = BUTTON_DFS_TOP + BUTTON_HEIGHT;

const int BUTTON_BFS_LEFT = BUTTON_DFS_RIGHT;
const int BUTTON_BFS_RIGHT = BUTTON_BFS_LEFT + BUTTON_WIDTH;
const int BUTTON_BFS_TOP = TOPBAR_BOTTOM;
const int BUTTON_BFS_BOTTOM = BUTTON_BFS_TOP + BUTTON_HEIGHT;

const int BUTTON_XtoY_LEFT = BUTTON_BFS_RIGHT;
const int BUTTON_XtoY_RIGHT = BUTTON_XtoY_LEFT + BUTTON_WIDTH;
const int BUTTON_XtoY_TOP = TOPBAR_BOTTOM;
const int BUTTON_XtoY_BOTTOM = BUTTON_XtoY_TOP + BUTTON_HEIGHT;

const int BUTTON_DinhTru_LEFT = BUTTON_ALGO_LEFT;
const int BUTTON_DinhTru_RIGHT = BUTTON_DinhTru_LEFT + BUTTON_WIDTH;
const int BUTTON_DinhTru_TOP = BUTTON_DFS_BOTTOM;
const int BUTTON_DinhTru_BOTTOM = BUTTON_DinhTru_TOP + BUTTON_HEIGHT;

const int BUTTON_DinhThat_LEFT = BUTTON_DinhTru_RIGHT;
const int BUTTON_DinhThat_RIGHT = BUTTON_DinhThat_LEFT + BUTTON_WIDTH;
const int BUTTON_DinhThat_TOP = BUTTON_DFS_BOTTOM;
const int BUTTON_DinhThat_BOTTOM = BUTTON_DinhThat_TOP + BUTTON_HEIGHT;

const int BUTTON_CanhCau_LEFT = BUTTON_DinhThat_RIGHT;
const int BUTTON_CanhCau_RIGHT = BUTTON_CanhCau_LEFT + BUTTON_WIDTH;
const int BUTTON_CanhCau_TOP = BUTTON_XtoY_BOTTOM;
const int BUTTON_CanhCau_BOTTOM = BUTTON_CanhCau_TOP + BUTTON_HEIGHT;

const int BUTTON_Hamilton_LEFT = BUTTON_ALGO_LEFT;
const int BUTTON_Hamilton_RIGHT = BUTTON_Hamilton_LEFT + BUTTON_WIDTH;
const int BUTTON_Hamilton_TOP = BUTTON_DinhTru_BOTTOM;
const int BUTTON_Hamilton_BOTTOM = BUTTON_Hamilton_TOP + BUTTON_HEIGHT;

const int BUTTON_Euler_LEFT = BUTTON_Hamilton_RIGHT;
const int BUTTON_Euler_RIGHT = BUTTON_Euler_LEFT + BUTTON_WIDTH;
const int BUTTON_Euler_TOP = BUTTON_DinhThat_BOTTOM;
const int BUTTON_Euler_BOTTOM = BUTTON_Euler_TOP + BUTTON_HEIGHT;

const int BUTTON_TopoSort_LEFT = BUTTON_Euler_RIGHT;
const int BUTTON_TopoSort_RIGHT = BUTTON_TopoSort_LEFT + BUTTON_WIDTH;
const int BUTTON_TopoSort_TOP = BUTTON_CanhCau_BOTTOM;
const int BUTTON_TopoSort_BOTTOM = BUTTON_TopoSort_TOP + BUTTON_HEIGHT;

const int BUTTON_ToMau_LEFT = BUTTON_ALGO_LEFT;
const int BUTTON_ToMau_RIGHT = BUTTON_ToMau_LEFT + BUTTON_WIDTH;
const int BUTTON_ToMau_TOP = BUTTON_Hamilton_BOTTOM;
const int BUTTON_ToMau_BOTTOM = BUTTON_ToMau_TOP + BUTTON_HEIGHT;

const int BUTTON_TPLT_LEFT = BUTTON_ALGO_LEFT;
const int BUTTON_TPLT_RIGHT = BUTTON_TPLT_LEFT + BUTTON_WIDTH;
const int BUTTON_TPLT_TOP = BUTTON_Euler_BOTTOM;
const int BUTTON_TPLT_BOTTOM = BUTTON_TPLT_TOP + BUTTON_HEIGHT;

// func

void initTopBar(void (*listener)(int));
void drawTopBar();

void listenTopBarInput(void (*listener)(int));

int findSelectedButton(int x, int y);
int onMouseClickInTopBar(int x, int y);
void closePreviousThread();
void createDialogFile();
void createDialogAlgo();
void createDialogHelp();


void addInsideFileButtons();
void removeInsideFileButtons();

void addInsideAlgoButtons();
void removeInsideAlgoButtons();


// button id --------------------------------------------

const int TOPBAR_UNSELECT = -1;
const int TOPBAR_OUTSIDER = -2;
// 0..2 : topBar buttons
const int TOPBAR_FILE = 1;
const int TOPBAR_ALGO = 2;
const int TOPBAR_HELP = 3;

// 3..5 : item in file option
const int TOPBAR_OPEN_FILE = 4;
const int TOPBAR_SAVE_FILE = 5;
const int TOPBAR_CLOSE_FILE = 6;

// 3..5 : item in file option
const int TOPBAR_ALGO_DFS = 7;
const int TOPBAR_ALGO_BFS = 8;
const int TOPBAR_ALGO_XtoY = 9;
const int TOPBAR_ALGO_DinhTru = 10;
const int TOPBAR_ALGO_DinhThat = 11;
const int TOPBAR_ALGO_CanhCau = 12;
const int TOPBAR_ALGO_Hamilton = 13;
const int TOPBAR_ALGO_Euler = 14;
const int TOPBAR_ALGO_TopoSort = 15;
const int TOPBAR_ALGO_ToMau = 16;
const int TOPBAR_ALGO_TPLT = 17;

int topBarSelection = TOPBAR_UNSELECT;

// button top bar
TextButton buttonFile = TextButton(BUTTON_FILE_LEFT, TOPBAR_TOP, BUTTON_FILE_RIGHT, TOPBAR_BOTTOM, "FILE", TOPBAR_FILE);
TextButton buttonAlgo = TextButton(BUTTON_ALGO_LEFT, TOPBAR_TOP, BUTTON_ALGO_RIGHT, TOPBAR_BOTTOM, "ALGORIHM", TOPBAR_ALGO);
TextButton buttonHelp = TextButton(BUTTON_HELP_LEFT, TOPBAR_TOP, BUTTON_HELP_RIGHT, TOPBAR_BOTTOM, "HELP", TOPBAR_HELP);
// inside file menu
TextButton buttonOpenFile = TextButton(BUTTON_OPEN_FILE_LEFT, BUTTON_OPEN_FILE_TOP, BUTTON_OPEN_FILE_RIGHT, BUTTON_OPEN_FILE_BOTTOM, "OPEN FILE", TOPBAR_OPEN_FILE);
TextButton buttonSaveFile = TextButton(BUTTON_SAVE_FILE_LEFT, BUTTON_SAVE_FILE_TOP, BUTTON_SAVE_FILE_RIGHT, BUTTON_SAVE_FILE_BOTTOM, "SAVE FILE", TOPBAR_SAVE_FILE);
TextButton buttonCloseFile = TextButton(BUTTON_CLOSE_FILE_LEFT, BUTTON_CLOSE_FILE_TOP, BUTTON_CLOSE_FILE_RIGHT, BUTTON_CLOSE_FILE_BOTTOM, "CLOSE FILE", TOPBAR_CLOSE_FILE);
// inside algo menu
TextButton buttonDFS = TextButton(BUTTON_DFS_LEFT, BUTTON_DFS_TOP, BUTTON_DFS_RIGHT, BUTTON_DFS_BOTTOM, "DFS", TOPBAR_ALGO_DFS);
TextButton buttonBFS = TextButton(BUTTON_BFS_LEFT, BUTTON_BFS_TOP, BUTTON_BFS_RIGHT, BUTTON_BFS_BOTTOM, "BFS", TOPBAR_ALGO_BFS);
TextButton buttonXtoY = TextButton(BUTTON_XtoY_LEFT, BUTTON_XtoY_TOP, BUTTON_XtoY_RIGHT, BUTTON_XtoY_BOTTOM, "X to Y", TOPBAR_ALGO_XtoY);
TextButton buttonDinhTru = TextButton(BUTTON_DinhTru_LEFT, BUTTON_DinhTru_TOP, BUTTON_DinhTru_RIGHT, BUTTON_DinhTru_BOTTOM, "Dinh Tru", TOPBAR_ALGO_DinhTru);
TextButton buttonDinhThat = TextButton(BUTTON_DinhThat_LEFT, BUTTON_DinhThat_TOP, BUTTON_DinhThat_RIGHT, BUTTON_DinhThat_BOTTOM, "Dinh That", TOPBAR_ALGO_DinhThat);
TextButton buttonCanhCau = TextButton(BUTTON_CanhCau_LEFT, BUTTON_CanhCau_TOP, BUTTON_CanhCau_RIGHT, BUTTON_CanhCau_BOTTOM, "Canh Cau", TOPBAR_ALGO_CanhCau);
TextButton buttonHamilton = TextButton(BUTTON_Hamilton_LEFT, BUTTON_Hamilton_TOP, BUTTON_Hamilton_RIGHT, BUTTON_Hamilton_BOTTOM, "Hamilton", TOPBAR_ALGO_Hamilton);
TextButton buttonEuler = TextButton(BUTTON_Euler_LEFT, BUTTON_Euler_TOP, BUTTON_Euler_RIGHT, BUTTON_Euler_BOTTOM, "Euler", TOPBAR_ALGO_Euler);
TextButton buttonTopoSort = TextButton(BUTTON_TopoSort_LEFT, BUTTON_TopoSort_TOP, BUTTON_TopoSort_RIGHT, BUTTON_TopoSort_BOTTOM, "TopoSort", TOPBAR_ALGO_TopoSort);
TextButton buttonTPLT = TextButton(BUTTON_TPLT_LEFT, BUTTON_TPLT_TOP, BUTTON_TPLT_RIGHT, BUTTON_TPLT_BOTTOM, "TPLT", TOPBAR_ALGO_TPLT);

// inside help menu

vector<TextButton> buttonList;

bool canListenTopBarInput = true;

thread thr;

// code ------------------------------------------------------------------------------


void drawTopBar()
{
	setfillstyle(SOLID_FILL, TOP_BAR_COLOR);
	bar(TOPBAR_LEFT, TOPBAR_TOP, TOPBAR_RIGHT, TOPBAR_BOTTOM);

	buttonList.clear();
	buttonList.push_back(buttonFile);
	buttonList.push_back(buttonAlgo);
	buttonList.push_back(buttonHelp);

	for (int i = 0; i < 3; i++)
	{
		buttonList[i].setBackgroundColor(TOP_BAR_COLOR);
		buttonList[i].setHighLightColor(HIGHLIGHT_TEXT_COLOR);
		buttonList[i].setTextColor(TEXT_COLOR);
		buttonList[i].show();
	}
}

// listen mouse click
void closePreviousThread()
{
	canListenTopBarInput = false;
	canListenTopBarInput = true;
}

bool onMouseClickInTopBar(int x, int y, void (*listener)(int)){
	int id = onMouseClickInTopBar(x, y);
			
	(*listener)(id);
	
	return id < 0 ? false : true;
}

int findSelectedButton(int x, int y)
{
	for (int i = 0; i < buttonList.size(); i++)
	{
		if (buttonList[i].isButtonClicked(x, y))
		{
//			cout << "selected button = " << i << endl;
			return i;
		}
	}
	return -1;
}

int onMouseClickInTopBar(int x, int y)
{

	int buttonPosition = findSelectedButton(x, y);

	drawTopBar();

	if (buttonPosition < 0)
	{
		removeInsideFileButtons();
		removeInsideAlgoButtons();
		
		return TOPBAR_OUTSIDER;
	}

	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i].setSelection(false);
	}

	if (buttonPosition < 3)
	{
		if (buttonList[buttonPosition].isButtonClicked(x, y))
		{
			buttonList[buttonPosition].setSelection(true);
		}
	}

	
	return buttonList[buttonPosition].getID();
}

void addInsideFileButtons()
{

	buttonList.push_back(buttonOpenFile);
	buttonList.push_back(buttonSaveFile);
	buttonList.push_back(buttonCloseFile);

	for (int i = 3; i < buttonList.size(); i++)
	{
		buttonList[i].setBackgroundColor(GREEN);
		buttonList[i].setHighLightColor(RED);
		buttonList[i].setTextColor(WHITE);
		buttonList[i].show();
	}
}

void removeInsideFileButtons()
{
	for (int i = 3; i < buttonList.size(); i++)
	{
		buttonList.pop_back();
	}
}

void addInsideAlgoButtons()
{
	buttonList.push_back(buttonDFS);
	buttonList.push_back(buttonBFS);
	buttonList.push_back(buttonXtoY);
	buttonList.push_back(buttonDinhTru);
	buttonList.push_back(buttonDinhThat);
	buttonList.push_back(buttonCanhCau);
	buttonList.push_back(buttonHamilton);
	buttonList.push_back(buttonEuler);
	buttonList.push_back(buttonTopoSort);
	buttonList.push_back(buttonTPLT);

	for (int i = 3; i < buttonList.size(); i++)
	{
		buttonList[i].setBackgroundColor(GREEN);
		buttonList[i].setHighLightColor(RED);
		buttonList[i].setTextColor(WHITE);
		buttonList[i].show();
	}
}

void removeInsideAlgoButtons()
{
	for (int i = 3; i < buttonList.size(); i++)
	{
		buttonList.pop_back();
	}
}

// child
void createDialogFile()
{
	setfillstyle(SOLID_FILL, HIGHLIGHT_TEXT_COLOR);
	bar(BUTTON_FILE_LEFT, TOPBAR_BOTTOM, DIALOG_FILE_RIGHT, DIALOG_FILE_BOTTOM);
}
void createDialogAlgo()
{
	setfillstyle(SOLID_FILL, HIGHLIGHT_TEXT_COLOR);
	bar(BUTTON_ALGO_LEFT, TOPBAR_BOTTOM, DIALOG_ALGO_RIGHT, DIALOG_ALGO_BOTTOM);
}
void createDialogHelp()
{
	setfillstyle(SOLID_FILL, HIGHLIGHT_TEXT_COLOR);
	bar(BUTTON_HELP_LEFT, TOPBAR_BOTTOM, DIALOG_HELP_RIGHT, DIALOG_HELP_BOTTOM);
}



