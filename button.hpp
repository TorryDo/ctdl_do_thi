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
		setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
		circle(449, 535, 25);
		setfillstyle(SOLID_FILL, BLACK);
		bar(437, 533, 461, 538);
		bar(447, 523, 452, 549);
		break;
	case ADD_EDGE_MENU://357, 92, 417, 162
		setlinestyle(SOLID_LINE, 1, 2);
		line(489, 555, 529, 515);
		drawTrianle(523, 521, 530, 514, BLACK);
		break;
	case RENAME_VERTEX_MENU://357, 162, 417, 232
		setlinestyle(SOLID_LINE, 1, 2);
		line(579, 518, 591, 530);
		line(556, 541, 568, 553);
		line(556, 541, 579, 518);
		line(568, 553, 591, 530);
		line(556, 541, 550, 558);
		line(568, 553, 550, 558);
		break;
	case DELETEVE_MENU://357, 232, 417, 302
		setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
		circle(629, 535, 25);
		setlinestyle(SOLID_LINE, 1, THICK_WIDTH);
		line(621, 527, 636, 542);
		line(621, 542, 636, 527);
		break;
	case MOVEVE_MENU://357, 302, 417, 372
		setfillstyle(SOLID_FILL, BLACK);
		bar(674, 534, 703, 536);
		bar(689, 521, 691, 550);
		drawTrianle(676, 534, 670, 534, BLACK);
		drawTrianle(689, 521, 689, 515, BLACK);
		drawTrianle(703, 534, 709, 534, BLACK);
		drawTrianle(689, 550, 689, 556, BLACK);
		break;
	case CLEAN_GRAPH_MENU://357, 372, 417, 442
		setlinestyle(SOLID_LINE, 1, 2);
		rectangle(731, 520, 767, 560);
		rectangle(735, 510, 763, 520);
		setlinestyle(SOLID_LINE, 1, 3);
		line(739, 531, 739, 555);
		line(749, 531, 749, 555);
		line(759, 531, 759, 555);
		line(727, 520, 771, 520);
		break;
	case HELP_MENU://357, 442, 417, 498
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setusercharsize(1, 1, 1, 1);
		settextstyle(GOTHIC_FONT, HORIZ_DIR, USER_CHAR_SIZE);
		setbkcolor(menu[HELP_MENU].color);
		outtextxy(809, 550, "?");
		break;
	default:
		menu[i].showName();
		break;
	}
}
