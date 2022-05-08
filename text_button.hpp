#pragma once
#include "graphics.h"


class TextButton {

	private:
		int id = 0;
		int top, right, bottom, left;
		char* title;
		int color;
		int borderWidth = 0;

		int backgroundColor;
		int highLightColor;
		int borderColor;
		int textColor;
		bool isSelected = false;
		bool isHover = false;


		void buildTitle() {
			moveto((left + right) / 2, (top + bottom) / 2 + 6);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			setusercharsize(1, 3, 1, 2);
			settextstyle(GOTHIC_FONT, HORIZ_DIR, USER_CHAR_SIZE);
			setcolor(this->textColor);
			setbkcolor(this->color);
			outtext(this->title);
		}

		void buildFrame() {
			setcolor(this->borderColor);
			setfillstyle(SOLID_FILL, this->color);
			bar(left, top, right, bottom);

			if(borderWidth > 0) {
				setlinestyle(SOLID_LINE, 1, this->borderWidth); 	// ?, ?, borderWidth
				rectangle(left, top, right, bottom);
			}

		}

	public:
		TextButton(int left, int top, int right, int bottom, char* title, int id) {
			this->top = top;
			this->right = right;
			this->bottom = bottom;
			this->left = left;
			this->title = title;
			this->id = id;
		}

		int getID() {
			return id;
		}
		void setSelection(bool state) {
			isSelected = state;

			if(isSelected) {
				this->color = this->highLightColor;
			} else {
				this->color = this->backgroundColor;
			}

			buildFrame();
			buildTitle();
		}

		void setBackgroundColor(int color) {
			this->backgroundColor = color;
		}

		void setBorderColor(int color) {
			this->borderColor = color;
		}

		void setHighLightColor(int color) {
			this->highLightColor = color;
		}

		void setBorderWidth(int width) {
			this->borderWidth = width;
		}

		void setTextColor(int color) {
			this->textColor = color;
		}

		bool isButtonClicked(int x, int y) {
			return (y > top && y < bottom && x > left && x < right);
		}

		void show() {
			this->color = this->backgroundColor;

			buildFrame();
			buildTitle();
		}

};
