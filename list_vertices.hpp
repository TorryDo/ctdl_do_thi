#pragma once

#include "graphics.h"
#include "colors.hpp"
#include "vertex.hpp"
#include "helpers.hpp"

class ListVertices
{
public:
	int num; //so luong dinh
	Vertex *v[MAX_VERTEX]; // mang luu cac dinh
	char currentName[MAX_NAME_LENGTH];
	
	
	ListVertices()
	{
		num = 0;
		strcpy(currentName, VERTEX_NAME_BEGIN);
	};
	void addVertex(int x, int y)
	{
		v[num] = new Vertex;
		v[num]->create(x, y, currentName);
		v[num]->show();
		increaseStr(currentName);
		++num;
	}
	void addVertex(char const *name, int x, int y)
	{
		v[num] = new Vertex;
		v[num]->create(x, y, name);
		strcpy(currentName, max(currentName, name));
		increaseStr(currentName);
		++num;
	}
	void deleteVertex(int pos)
	{
		delete v[pos];
		--num;
		for (int i = pos; i < num; ++i)
			v[i] = v[i + 1];
	}
	int find(int x, int y) const
	{
		for (int i = 0; i < num; ++i)
			if (v[i]->isVertexClick(x, y)) return i;
		return -1;
	}
	void showAll() const
	{
		for (int i = 0; i < num; ++i)
			v[i]->show();
	}
	void showAll(int color)
	{
		for (int i = 0; i < num; ++i)
			v[i]->show(color);
	}
	void resetColor()
	{
		for (int i = 0; i < num; ++i)
			v[i]->setColor(VERTEX_COLOR2);
	}
	bool isExist(char const *name) const
	{
		for (int i = 0; i < num; ++i)
			if (strcmp(v[i]->name, name) == 0) return 1;
		return 0;
	}
	void clear()
	{
		while (--num >= 0)
			delete v[num];
		num = 0;
		strcpy(currentName, VERTEX_NAME_BEGIN);
	}
	void updateCurrentName(const char *str)
	{
		if (strcmp(currentName, max(currentName, str)) != 0)
		{
			strcpy(currentName, str);
			increaseStr(currentName);
		}
	}
	
	bool isEmpty(){
		return num <= 0;
	}
	
	~ListVertices()
	{
		while (--num >= 0)
			delete v[num];
	}
	
};

