#pragma once
#include <cstring>
#include "colors.hpp"			// Define all colors need
#include "button.hpp"			// Button structures
#include "vertex.hpp"			// Vertex structures
#include "list_vertices.hpp"	// Manage all vertices
#include "helpers.hpp" 			// Basic functions & draw edges
#include "constants.hpp" 		// All constants go here
#include "global_variables.hpp"// All Global variables

//----------------------------BUTTON ALGOGRIMTH------------------------------
void dfs();
void bfs();
void shortestWayXY();

//----------------------------BUTTON TOPBAR-----------------------
void open();
void aglo();

//----------------------------BUTTON EDIT-------------------------
void addVertex();
void addEdges();
void renameVertex();
void deleteVertex();
void moveVertex();
void cleanGraph();
//----------------------------Ho tro------------------------------
void removeVertex(int);
void removeRow(int);
void removeCol(int);
void removeLast();

void dfsTraveler(int u);
void bfsTraveler(int u);

void setTextPrintStyle(int color);
void load();
void aglo();
bool isNegativeWeight();
void dijkstra(int start, int stop);
bool fordbellman(int start, int stop);
void showResultPathXY(double dist[], int start, int stop);
void backToMenu();
//
int findButton(int x, int y);
int findButton2(int x, int y);
int findButton3(int x, int y);
void refreshScreen();
void refreshGraph(int mPos);

//---------------
int chooseVertex(int, int skipReset = -1);
//---
void setTextPrintStyle(int);
void printText(float);
void printText(const char*);
void deleteText(const char*);
template <typename Type>
void printTextWl(Type); // print text -> endl
template <typename Type>
void printTextWlb(Type); // endl -> print text

bool isEmptyGraph()
{
	if (listv.num == 0)
	{
		MessageBox(hwnd, "Do thi rong", "Loi", MB_APPLMODAL | MB_ICONERROR);
		return 1;
	}
	return 0;
}

void adjustSpeed(char key)
{
	if (key == KEY_LEFT)
		delayRunTime = (delayRunTime < MAX_SPEED) ? delayRunTime + 100 : MAX_SPEED;
	else if (key == KEY_RIGHT)
		delayRunTime = (delayRunTime > 100) ? delayRunTime - 100 : 0;
	showSpeed();
}

char getKey()
{
	if (kbhit())
	{
		char c = getch();
		switch (c)
		{
			case KEY_ESC:
				return KEY_ESC;
			case ARROW_KEY:
				c = getch();
				adjustSpeed(c);
				return c;
			case KEY_Q:
				return KEY_Q;
			case KEY_LQ:
				return KEY_Q;
			default:
				return KEY_NULL;
		}
	}
	return KEY_NULL;
}

void printText(const char *str)
{
	int const tw = textwidth(str);
	if (xCursor + tw >= 390) // 10 + tw >= tRIGHT
	{
		xCursor = xCURSOR;
		yCursor += TEXTHIGHT;
	}
	if (yCursor > tBOTTOM - TEXTHIGHT) //510 < 620
	{
		drawTextZone();
		xCursor = xCURSOR;
		yCursor = yCURSOR;
		setTextPrintStyle(TEXT_COLOR);
	}
	outtextxy(xCursor, yCursor, str);
	xCursor += tw;
}

void printText(float value)
{
	char str[MAX_INPUT];
	convertToChar(value, str);
	printText(str);
}

void setTextPrintStyle(int color)
{
//	setusercharsize(9, 10, 9, 10);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
	setbkcolor(BACKGROUND_COLOR);
	setcolor(color);
	settextjustify(LEFT_TEXT, TOP_TEXT);
}

void drawEdge(int begin, int end, int color)
{
	const int &x1 = listv.v[begin]->x;
	const int &y1 = listv.v[begin]->y;
	const int &x2 = listv.v[end]->x;
	const int &y2 = listv.v[end]->y;
	if (adjaGraph[end][begin] == NO_EDGE_VALUE || begin < end)
		drawArrow(x1, y1, x2, y2, color, adjaGraph[begin][end]);
	else
		drawCurvedLine(x1, y1, x2, y2, color, adjaGraph[begin][end]);
}

void drawAllEdges()
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			if (adjaGraph[i][j] != NO_EDGE_VALUE)
				drawEdge(i, j, EDGE_COLOR);
}

int chooseVertex(int highLightColor, int skipReset)
{
	drawLimitZone();
	int x, y;
	int newPos(-1), oldPos(-1);
	while (1)
	{
		if (getKey() == KEY_ESC) break;
		newPos = listv.find(mousex(), mousey());
		if (newPos != oldPos)
		{
			if (newPos != -1 && newPos != skipReset) 
				listv.v[newPos]->show(highLightColor);
			if (oldPos != -1 && oldPos != skipReset)
				listv.v[oldPos]->show(VERTEX_COLOR2);
			oldPos = newPos;
		}
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (!isInWorkingZone(x, y)) break;
			if (newPos != -1)
			{
				listv.v[newPos]->show(highLightColor);
				return newPos;
			}
		}
		delay(DELAY_VALUE);
	}
	return -1;
}

bool chooseStartVertex(int &start, const char *text1, const char *text2)
{
	setTextPrintStyle(TEXT_COLOR);
	printText(text1);
	start = chooseVertex(VERTEX_CHOOSING_COLOR);
	if (start == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printText(listv.v[start]->name);
	printTextWlb(text2);
	return 1;
	
}

bool chooseTwoVertices(int &start, int &stop)
{
	setTextPrintStyle(TEXT_COLOR);
	printText("Chon dinh xuat phat: ");
	start = chooseVertex(VERTEX_CHOOSING_COLOR);
	if (start == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printTextWl(listv.v[start]->name);
	listv.v[start]->show(VERTEX_CHOSE_COLOR);
	setTextPrintStyle(TEXT_COLOR);
	printText("Chon dinh ket thuc: ");
	stop = chooseVertex(VERTEX_CHOOSING_COLOR, start);
	if (stop == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printTextWl(listv.v[stop]->name);
	listv.v[stop]->show(VERTEX_CHOSE_COLOR);
	if (start == stop)
	{
		listv.v[stop]->show(VERTEX_COLOR);
		return 0;
	}
	return 1;
}
 
void deleteText(const char* str){
	if (xCursor <= xCURSOR) return;
	const int currentColor = getcolor();
	setTextPrintStyle(BACKGROUND_COLOR);
	const int tw = textwidth(str);
	xCursor -= tw;
	printText(str);
	xCursor -= tw;
	setTextPrintStyle(currentColor);
}

bool getInputChar(char *str, int max, bool (*checkKey)(char key))
{
	setTextPrintStyle(BLUE);
	int i = 0; str[0] = '\0';
	char key[2] = {'\0', '\0'};
	while (i < max)
	{
		if (kbhit())
		{
			key[0] = getch();
			if (key[0] == KEY_ESC || key[0] == KEY_ENTER) break;
			if (key[0] == KEY_BACKSPACE && i > 0) {--i; key[0] = str[i]; deleteText(key); str[i] = '\0';}
			else if (checkKey(key[0])) {strcat(str, key); ++i; printText(key);}
		}
		if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
		delay(DELAY_VALUE);
	}
	return (i > 0);
}

bool getInputWeight(float &res)
{
	char str[10];
	getInputChar(str, 10, inputFloat);
	if (!isFloat(str)) return 0;
	res = roundf(toFloat(str) * 100) / 100;
	if (res > MAX_WEIGHT || res < MIN_WEIGHT)
	{
		char msg[70]; char w[10];
		strcpy(msg, "Trong so khong cho phep.\nTrong so >= ");
		convertToChar(MIN_WEIGHT, w);
		strcat(msg, w);
		strcat(msg, " & Trong so <= ");
		convertToChar(MAX_WEIGHT, w);
		strcat(msg, w);
		MessageBox(hwnd, msg, "Loi", MB_APPLMODAL | MB_ICONERROR);
		return 0;
	}
	return 1;
}

void refreshGraph(int mPos)
{
	setactivepage(1 - getactivepage());
	drawWorkingZone();
	drawMatrixZone();
	drawTextZone();
	showAllButtons();
	drawAllEdges();
	listv.showAll();
	menuButton[mPos].showChoseButton();
	showButtonIcon(menuButton, mPos);
	setvisualpage(getactivepage());
}
template <typename Type>
void printTextWl(Type s)
{
	printText(s);
	xCursor = xCURSOR;
	yCursor += TEXTHIGHT;
}
template <typename Type>
void printTextWlb(Type s)
{
	xCursor = xCURSOR;
	yCursor += TEXTHIGHT;
	printText(s);
}
//Xu ly them, xoa, sua, di chu
void addVertex()
{
	drawLimitZone();
	if (listv.num == MAX_VERTEX)
	{
		char msg[45], num[3];
		strcpy(msg, "Qua so luong dinh cho phep MAX_VERTEX = ");
		convertToChar(MAX_VERTEX, num);
		strcat(msg, num);
		MessageBox(hwnd, msg, "Loi", MB_APPLMODAL | MB_ICONERROR);
	}
	int x, y;
	setTextPrintStyle(TEXT_COLOR);
	printText("Click chuot de them dinh.");
	while (listv.num < MAX_VERTEX)
	{
		if (getKey() == KEY_ESC) break;
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (listv.find(x, y) != -1)
			{
				MessageBox(hwnd, "Trung dinh da co\nVui long chon lai.", "Loi",
							MB_APPLMODAL | MB_ICONERROR);
				continue;
			}
			if (isInLimitZone(x, y))
			{
				listv.addVertex(x, y);
				setMatrixTo2(adjaGraph, listv.num, NO_EDGE_VALUE);
				drawMatrixZone();
				isSaved = 0;
			}
			else break;
		}
		delay(DELAY_VALUE);
	}
}

void addEdges()
{
	if (isEmptyGraph()) return;
	int begin, end, oldEnd = -1;
	float weight;
	setTextPrintStyle(TEXT_COLOR);
	printText("Noi hai dinh de them/xoa cung.");
	while (1)
	{
		begin = chooseVertex(VERTEX_CHOOSING_COLOR);
		if (begin == -1) break;
		int x = listv.v[begin]->x;
		int y = listv.v[begin]->y;
		if (ismouseclick(WM_LBUTTONUP)) clearmouseclick(WM_LBUTTONUP);
		while (!ismouseclick(WM_LBUTTONUP))
		{
			setactivepage(1 - getactivepage());
			initScreen();
			drawLimitZone();
			drawAllEdges();
			listv.showAll();
			listv.v[begin]->show(VERTEX_CHOSE_COLOR);
			menuButton[ADD_EDGE_MENU].showChoseButton();
			showButtonIcon(menuButton, ADD_EDGE_MENU);
			end = listv.find(mousex(), mousey());
			drawArrow(x, y, mousex(), mousey(), EDGE_HIGHTLIGHT_COLOR, 0);
			setvisualpage(getactivepage());
			if (oldEnd != -1 && oldEnd != end && oldEnd != begin)
				listv.v[oldEnd]->show(VERTEX_COLOR);
			if (end != begin && end != -1 && end != oldEnd)
				listv.v[end]->show(VERTEX_CHOOSING_COLOR);
			oldEnd = end;
			if (!isInWorkingZone(mousex(), mousey())) break;
			delay(DELAY_VALUE);
		}
		if (end == -1 || end == begin)
		{
			refreshGraph(ADD_EDGE_MENU);
			listv.v[begin]->show(VERTEX_COLOR);
			continue;
		}
		listv.v[end]->show(VERTEX_CHOSE_COLOR);
		setvisualpage(getactivepage());
		adjaGraph[begin][end] = DEFAULT_WEIGHT;
		refreshGraph(ADD_EDGE_MENU);
		drawEdge(begin, end, EDGE_HIGHTLIGHT_COLOR);
		setTextPrintStyle(TEXT_COLOR);
		
		printText("Nhap trong so (xoa cung nhap '-')");
		printText("cung ");
		
		printText(listv.v[begin]->name);
		printText("->");
		printText(listv.v[end]->name);
		printText(": ");
		if (getInputWeight(weight)) adjaGraph[begin][end] = weight;
		else adjaGraph[begin][end] = NO_EDGE_VALUE;
		isSaved = 0;
		refreshGraph(ADD_EDGE_MENU);
		listv.v[begin]->show(VERTEX_COLOR);
		listv.v[end]->show(VERTEX_COLOR);
	}
}

void renameVertex()
{
	if (isEmptyGraph()) return;
	int choose;
	while (1)
	{
		if (chooseStartVertex(choose, "Chon dinh can doi ten: ", "Nhap ten moi cho dinh "))
		{
			printText(listv.v[choose]->name);
			printText(": ");
			listv.v[choose]->show(VERTEX_CHOSE_COLOR);
			char name[MAX_NAME_LENGTH];
			if (getInputChar(name, MAX_NAME_LENGTH - 1, inputAscii) && !listv.isExist(name))
			{
				listv.updateCurrentName(name);
				listv.v[choose]->clearName();
				strcpy(listv.v[choose]->name, name);
				drawMatrixZone();
				isSaved = 0;
			}
			else MessageBox(hwnd, "Trung ten hoac nhap sai", "Loi", MB_APPLMODAL | MB_ICONERROR);
			listv.v[choose]->show(VERTEX_COLOR2);
			printTextWl("");
		} else break;
	}
}

inline void removeRow(int row)
{
	for (int i = row; i < listv.num - 1; ++i)
		for (int j = 0; j < listv.num; ++j)
			adjaGraph[i][j] = adjaGraph[i + 1][j];
}
inline void removeCol(int col)
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = col; j < listv.num - 1; ++j)
			adjaGraph[i][j] = adjaGraph[i][j + 1];
}
inline void removeLast()
{
	const int &LAST = listv.num - 1;
	for (int i = 0; i < listv.num; ++i) //Remove last row & last column
	{
		adjaGraph[LAST][i] = NO_EDGE_VALUE;
		adjaGraph[i][LAST] = NO_EDGE_VALUE;
	}
}
void removeVertex(int v)
{
	removeCol(v);
	removeRow(v);
	removeLast();
}

void deleteVertex()
{
	if (isEmptyGraph()) return;
	while (listv.num > 0)
	{
		setTextPrintStyle(TEXT_COLOR);
		printText("Chon dinh can xoa: ");
		int choose = chooseVertex(VERTEX_DELETE_COLOR);
		if (choose == -1) break;
		setTextPrintStyle(VERTEX_DELETE_COLOR);
		printText(listv.v[choose]->name);
		removeVertex(choose);
		listv.deleteVertex(choose); // --num is in here
		refreshGraph(DELETEVE_MENU);
		isSaved = 0;
		if (listv.num == 0)
			listv.clear();
	}
}

void moveVertex()
{
	if (isEmptyGraph()) return;
	int x, y;
	setTextPrintStyle(TEXT_COLOR);
	
	printTextWl("Dung thao tac keo/tha dinh de di");
	printTextWl("chuyen tung dinh ! ");
	printText("hoac Ctr + keo/tha de di chuyen");
	printText("toan bo do thi ! ");
	
	while (1)
	{
		int choose = chooseVertex(VERTEX_CHOOSING_COLOR);
		if  (choose == -1) break;
		if (ismouseclick(WM_LBUTTONUP)) clearmouseclick(WM_LBUTTONUP);
		isSaved = 0;
		listv.v[choose]->show(VERTEX_CHOSE_COLOR);
		while (!ismouseclick(WM_LBUTTONUP))
		{
			if (ismouseclick(WM_MOUSEMOVE))
			{
				getmouseclick(WM_MOUSEMOVE, x, y);
				if (!isInLimitZone(x, y)) continue;
				if (GetKeyState(VK_CONTROL) < 0) // Crt + move all vertices
				{
					int dx = x - listv.v[choose]->x;
					int dy = y - listv.v[choose]->y;
					for (int i = 0; i < listv.num; ++i)
					{
						listv.v[i]->x += dx;
						listv.v[i]->y += dy;
						if (!isInLimitZone(listv.v[i]->x, listv.v[i]->y))
						{
							for (int j = i; j >= 0; --j)
							{
								listv.v[j]->x -= dx;
								listv.v[j]->y -= dy;
							}
							break;
						}
					}
				} else listv.v[choose]->setCoordinate(x, y); // Move single vertex
				setactivepage(1 - getactivepage());
				initScreen();
				drawLimitZone();
				drawAllEdges();
				listv.showAll();
				menuButton[MOVEVE_MENU].showChoseButton();
				showButtonIcon(menuButton, MOVEVE_MENU);
				setvisualpage(getactivepage());
			}
			delay(DELAY_VALUE);
		}
		listv.v[choose]->show(VERTEX_COLOR2);
		setvisualpage(getactivepage());
	}
}

void cleanGraph()
{
	if (isEmptyGraph()) return;
	if (MessageBox(hwnd, "Ban co chac khong?", "Xoa do thi",
		MB_APPLMODAL| MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		listv.clear();
		setMatrixTo(adjaGraph, NO_EDGE_VALUE);
		refreshGraph(CLEAN_GRAPH_MENU);
		isSaved = 1;
	}
}

void help()
{
	MessageBox(hwnd, "Do an do thi nhom 35.\n"
					"Su dung:\n"
					"Phim <ESC> : Huy chuc nang.\n"
					"Phim <Q>/<q> : Thoat chuong trinh.\n"
					"Phim <LEFT>/<RIGHT> : Chinh toc do giam/tang.\n"
					"Su dung cac nut de thuc hien thao tac tren man hinh.\n"
					"\nTac gia:\n"
					"Tran Minh Hoang\n"
					"Nguyen Do Tri\n"
					"Dang Mai Hong An",
				 	"Help", MB_APPLMODAL | MB_ICONINFORMATION);
}

//-------------------------------------------xu ly button menu (file, aglo, quit)

void open(){
	int x, y;
//	menu2();
	while(1){
		for (int i = 10; i < 12 ;++i)
		{
			menuButton[i].showNormalButton();
			showButtonIcon(menuButton, i);
			
			delay(DELAY_VALUE);
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			int choose = findButton2(x, y);
			if(choose == -1) return;
			if(choose != -1){
				if(choose == 10) return load();
				if(choose == 11) return;
			}
		}
	}
}

void load(){
	int x, y;
	while(1){
		outtextxy(100,200,"hoang");
		delay(DELAY_VALUE);
		if(ismouseclick(WM_LBUTTONDOWN)){
		getmouseclick(WM_LBUTTONDOWN, x, y);
		int choose = findButton2(x, y);
		if(choose != 10) return;
		}
	}
}

void aglo(){
	int x, y;
//	int newChoose(-1), oldChoose(-1);
	while(1){
		for (int i = 12; i < 23 ;++i)
		{
			menuButton[i].showNormalButton();
			showButtonIcon(menuButton, i);
			
			delay(DELAY_VALUE);
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			int choose = findButton3(x, y);
			//newChoose = choose;
			if(choose == -1) return;
			if(choose == 12) return dfs();
			if(choose == 13) return bfs();
			if(choose == 14) return shortestWayXY();
		}
	}
}

// demo thuat toan -------------------------------------------------------------------------
//void dfs(){
//	int x, y;
//	while(1){
//		outtextxy(100, 300, "My");
//		delay(DELAY_VALUE);
//		if(ismouseclick(WM_LBUTTONDOWN)){
//		getmouseclick(WM_LBUTTONDOWN, x, y);
//		int choose = findButton3(x, y);
//		if(choose != 12) return;
//		}
//	}
//}

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
		//for (int i = listv.num - 1; i >= 0 ; --i) //like recursive order
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

void showResultStack(stack &s)
{
	int v, u = s.pop();
	setTextPrintStyle(TEXT_COLOR);
	printText(listv.v[u]->name);
	listv.v[u]->show(VERTEX_CHOSE_COLOR);
	while (!s.isEmpty())
	{
		v = s.pop();
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText("->");
		printText(listv.v[v]->name);
		drawEdge(u, v, EDGE_VISTED_COLOR);
		listv.v[v]->show(VERTEX_VISTED_COLOR);
		u = v;
		if (getKey() == KEY_ESC) return;
		delay(delayRunTime);
	}
}

void showResultPathXY(double dist[], int start, int stop)
{
	setTextPrintStyle(TEXT_COLOR);
	if (dist[stop] == MAX_EDGE_VALUE)
		printText("Khong ton tai duong di.");
	else
	{
		printText("Tong trong so: ");
		printTextWl(dist[stop]);
		printText("Duong di ngan nhat: ");
		stack s;
		while (stop != start)
		{
			s.push(stop);
			stop = trace[stop];
		}
		s.push(start);
		return showResultStack(s);
	}
}

// Xu li cac button
void switchMenuItem(int chose)
{
	switch (chose)
	{
		case ADD_VERTEX_MENU:	 	return addVertex();
		case ADD_EDGE_MENU: 		return addEdges();
		case RENAME_VERTEX_MENU: 	return renameVertex();
		case DELETEVE_MENU: 		return deleteVertex();
		case MOVEVE_MENU: 			return moveVertex();
		case CLEAN_GRAPH_MENU: 		return cleanGraph();
		case HELP_MENU: 			return help();
		default: 					return;
	}
}

void backToMenu()
{
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Nhan phim bat ky hoac click chuot");
	printTextWlb("de tiep tuc.");
	if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
	fflush(stdin);
	while (1)
	{
		if (kbhit()) break;
		if (ismouseclick(WM_LBUTTONDOWN)) break;
		delay(DELAY_VALUE);
	}
	if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
	fflush(stdin);
}

// lam moi man hinh
void refreshScreen()
{
	setactivepage(1 - getactivepage());
	initScreen();
	drawAllEdges();
	listv.showAll(VERTEX_COLOR2);
	setvisualpage(getactivepage());
}
// show button da chon
inline void showChoseButton(int pos)
{
	if (pos >= ADD_VERTEX_MENU) refreshScreen();
	menuButton[pos].showChoseButton();
	showButtonIcon(menuButton, pos);
}
// tim kiem button, tra ve i neu tim thay va tra ve -1 neu khong tim thay
int findButton(int x, int y)
{
	for (int i = 0; i < 10 ;++i)
		if (menuButton[i].isButtonClick(x, y))
			return i;
	return -1;
}
int findButton2(int x, int y)
{
	for (int i = 10; i < 12 ;++i)
		if (menuButton[i].isButtonClick(x, y))
			return i;
	return -1;
}

int findButton3(int x, int y)
{
	for (int i = 12; i < 23 ;++i)
		if (menuButton[i].isButtonClick(x, y))
			return i;
	return -1;
}

// show hightlight button
inline void showHightLightButton(int pos)
{
	menuButton[pos].showHightLightButton();
	if (pos >= ADD_VERTEX_MENU) menuButton[pos].showButtonHint();
	showButtonIcon(menuButton, pos);
}

inline void showNormalButton(int pos)
{
	if (pos >= ADD_VERTEX_MENU) refreshScreen();
	menuButton[pos].showNormalButton();
	showButtonIcon(menuButton, pos);
}
// update button theo showNormalButton va showHightLightButton
inline void update(int &oldPos, int &newPos, int x, int y)
{
	newPos = findButton(x, y);
	if (newPos != oldPos)
	{	
		if (oldPos != -1) showNormalButton(oldPos);
		if (newPos != -1) showHightLightButton(newPos);
		oldPos = newPos;  
	}
}