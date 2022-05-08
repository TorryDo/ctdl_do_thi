#pragma once
#include"graphics.h"
#include"constants.hpp"
#include"global_variables.hpp"
#include "top_bar.hpp"

void drawWindow();
void initScreen();
void drawbarsettings();
void drawMatrixZone();
void drawTextZone();
void drawWorkingZone();
void drawLimitZone();
void showAllButtons();
void initScreen();

void drawWindow()
{
	setcolor(15);
	setbkcolor(15);
	setfillstyle(1, BACKGROUND2_COLOR);
	bar(0, 0, WINDOW_WIDTH, WINDOW_HIGHT);                                  
}

void drawbarsettings(){
//	setcolor(0);
//	setbkcolor(0);
//	setfillstyle(1, BUTTON_TOPBAR);
//	bar(mLEFT, mTOP - 10, wRIGHT, 50);
//	rectangle(mLEFT, mTOP - 10, wRIGHT, 50);
}

void drawMatrixZone(){
	setcolor(7);
	setbkcolor(7);
	setfillstyle(1, 7);
	setusercharsize(1, 2, 1, 2);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(BLACK);
	outtextxy(6, mTOP + 35, "Matrix");
	bar(aLEFT, mTOP + 55, mRIGHT , mRIGHT + 60);
	rectangle(aLEFT, mTOP + 55, mRIGHT , mRIGHT + 60);
	const int &n = listv.num + 1;
	if (n == 1) return;
	const float width = float(aRIGHT - aLEFT) / n;
	const float hight = float(aBOTTOM - aTOP) / n;
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	setcolor(BLACK);
	setbkcolor(BACKGROUND_COLOR);
	settextjustify(LEFT_TEXT, CENTER_TEXT);
	if (n > aVERTEX_MAX_2)
	{
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
		outtextxy((aLEFT + mRIGHT) / 2, ((mTOP + 55) + (mRIGHT + 60)) / 2, "KHONG THE HIEN THI.");
		return;
	}
	if (n > aVERTEX_MAX_1) settextstyle(SMALL_FONT, HORIZ_DIR, 4);
	else
	{
		setusercharsize(1, 2, 1, 2);
		settextstyle(BOLD_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	}
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	char str[10];
	for (int i = 1; i < n; ++i)
	{
		line(aLEFT, mTOP + 55 + i * hight, mRIGHT, mTOP + 55 + i * hight);
		line(aLEFT + i * width, mTOP + 55, aLEFT + i * width, mBOTTOM + 185);
		outtextxy(ADJUST_TEXT_X, i * hight + ADJUST_TEXT_Y, listv.v[i - 1]->name);
		outtextxy(ADJUST_TEXT_X + i * width, ADJUST_TEXT_Y, listv.v[i - 1]->name);
		for (int j = 1; j < n; ++j)
			if (adjaGraph[i - 1][j - 1] != NO_EDGE_VALUE)
			{
				convertToChar(adjaGraph[i - 1][j - 1], str);
				outtextxy(ADJUST_TEXT_X + j * width, i * hight + ADJUST_TEXT_Y, str);
			}
	}
}

void drawTextZone(){
	setcolor(7);
	setbkcolor(7);
	setfillstyle(1, 7);
	setusercharsize(1, 2, 1, 2);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(BLACK);
	outtextxy(6, 410 , "Console");
	bar(aLEFT, 430, mRIGHT + 50, aBOTTOM);
	rectangle(aLEFT, 430, mRIGHT + 50, aBOTTOM);
	xCursor = xCURSOR; // Move cursor x to beginning
	yCursor = yCURSOR;
}

void drawWorkingZone(){
	setcolor(7);
	setbkcolor(7);
	setfillstyle(1, 7);
	setusercharsize(1, 2, 1, 2);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(BLACK);
	outtextxy(wbLEFT + 1, mTOP + 35 , "WorkSpace");
	bar(wbLEFT, mTOP + 55, wRIGHT, wBOTTOM - 2);
}

void drawLimitZone(){
	setcolor(0);
	//setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	rectangle(wbLEFT, mTOP + 55, wRIGHT, wBOTTOM - 2);
}
//================ShowButton======================

void showAllButtons()
{
	for (int i = 0; i < 7 ;++i)
	{
		menuButton[i].showNormalButton();
		showButtonIcon(menuButton, i);
	}
}

//------------------------------------------------
void showSpeed()
{
	char status[15];
	char speed[3];
	convertToChar((MAX_SPEED - delayRunTime) / 100, speed);
	strcpy(status, "Speed: ");
	strcat(status, speed);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	bar(sLEFT, sTOP, sRIGHT, sBOTTOM);
	setbkcolor(BACKGROUND_COLOR);
	setusercharsize(1, 2, 1, 2);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	outtextxy(sLEFT, sTOP, status);
}


void initScreen()
{
	drawWindow();
	drawTopBar();
	drawMatrixZone();
	drawTextZone();
	drawWorkingZone();
	drawLimitZone();
	showAllButtons();
}