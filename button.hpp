#pragma once
#include "graphics.h"
#include "colors.hpp"
#include "constants.hpp"
#include "helpers.hpp"

struct Button
{
	const int left, top, right, bottom;
	int color;
	const char name[15];
	
	void showInit(int );
	void showNormalButton();
	void showHightLightButton();
	void showChoseButton();
	void showButtonHint();
	void showName() const;
	bool isButtonClick(int x, int y);
};

inline bool Button::isButtonClick(int x, int y)
{
	return (y > top && y < bottom && x > left && x < right);
}
void Button::showInit(int borderColor)
{
	setcolor(borderColor);
	setlinestyle(SOLID_LINE, 1, 2);
	setfillstyle(SOLID_FILL, color);
	bar(left, top, right, bottom);
	rectangle(left, top, right, bottom);
}
inline void Button::showNormalButton()
{
	color = BUTTON_COLOR;
	showInit(BUTTON_BORDER);
}
inline void Button::showHightLightButton()
{
	color = BUTTON_COLOR_HIGHTLIGHT;
	showInit(BUTTON_BORDER_HIGHTLIGHT);
}
inline void Button::showChoseButton()
{
	color = BUTTON_COLOR_CHOSE;
	showInit(BUTTON_BORDER_CHOSE);
}
void Button::showButtonHint()
{
	setusercharsize(1, 2, 1, 2);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	setcolor(BLACK);
	setbkcolor(BUTTON_HINT);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	outtextxy(right, bottom, name);
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	rectangle(right - 1, bottom, right + textwidth(name), bottom + textheight(name));
}
void Button::showName() const
{
	moveto((left + right) / 2, (top + bottom) / 2 + 6);
	settextjustify(CENTER_TEXT, CENTER_TEXT);	
	setusercharsize(1, 3, 1, 2); //gothic
	settextstyle(GOTHIC_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	setcolor(BLACK);
	setbkcolor(color);
	outtext(name);
}
void showButtonIcon(Button const *menu, int i)
{
	setcolor(BLACK);
	switch (i)
	{
	case ADD_VERTEX_MENU://357, 22, 417, 92,
		setlinestyle(SOLID_LINE, 1, NORM_WIDTH);//bar(aLEFT, 430, mRIGHT + 50, aBOTTOM); 640
		circle(449, 604, 25); // 500 ; 572
		setfillstyle(SOLID_FILL, BLACK);
		bar(437, 602, 461, 607);// 535
		bar(447, 592, 452, 618);
		break;
	case ADD_EDGE_MENU://357, 92, 417, 162
		setlinestyle(SOLID_LINE, 1, 2);
		line(489, 623, 529, 583);// 500; 572
		drawTrianle(523, 589, 530, 582, BLACK);
		break;
	case RENAME_VERTEX_MENU://357, 162, 417, 232
		setlinestyle(SOLID_LINE, 1, 2);
		line(579, 586, 591, 598); // 12
		line(556, 609, 568, 621); // 12
		line(556, 609, 579, 586); // 23
		line(568, 621, 591, 598); // 23
		line(556, 609, 550, 626); // 17
		line(568, 621, 550, 626); // 5
		break;
	case DELETEVE_MENU://357, 232, 417, 302
		setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
		circle(629, 604, 25);
		setlinestyle(SOLID_LINE, 1, THICK_WIDTH);
		line(621, 595, 636, 610);//15
		line(621, 610, 636, 595);//15
		break;
	case MOVEVE_MENU://357, 302, 417, 372
		setfillstyle(SOLID_FILL, BLACK);
		bar(674, 602, 703, 604);
		bar(689, 589, 691, 618);
		drawTrianle(676, 602, 670, 602, BLACK);
		drawTrianle(689, 589, 689, 583, BLACK);
		drawTrianle(703, 602, 709, 602, BLACK);
		drawTrianle(689, 618, 689, 624, BLACK);
		break;
	case CLEAN_GRAPH_MENU://357, 372, 417, 442
		setlinestyle(SOLID_LINE, 1, 2);
		rectangle(731, 588, 767, 628); // 
		rectangle(735, 578, 763, 588); // 510; 520
		setlinestyle(SOLID_LINE, 1, 3);
		line(739, 599, 739, 623); // 24
		line(749, 599, 749, 623); // 24
		line(759, 599, 759, 623); // 24
		line(727, 588, 771, 588); // 0
		break;
	case HELP_MENU://357, 442, 417, 498
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setusercharsize(1, 1, 1, 1);
		settextstyle(GOTHIC_FONT, HORIZ_DIR, USER_CHAR_SIZE);
		setbkcolor(menu[HELP_MENU].color);
		outtextxy(809, 618, "?");
		break;
	default:
		menu[i].showName();
		break;
	}
}