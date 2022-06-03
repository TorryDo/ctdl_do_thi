#pragma once

#include "graphics.h"
#include <fstream>
#include <iostream>
#define WINBGI_H

using namespace std;

void saveFile(ListVertices *listv)
{
	OPENFILENAME file;
	char fileName[MAX_PATH] = "\0";
	SecureZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.lpstrFile = fileName;
	file.nMaxFile = sizeof(fileName);
	file.lpstrFilter = (FILE_FILTER);
	file.nFilterIndex = 1;
	file.hwndOwner = GetActiveWindow();
	file.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT;

	if (GetSaveFileName(&file) == 1)
	{
		if (!strstr(fileName, ".graph"))
		{
			strcat(fileName, ".graph"); // Add file name suffix if it isn't exist.
		}

		ofstream outputFileStream(fileName);

		const int num = listv->num;

		outputFileStream << num << '\n';
		for (int i = 0; i < num; ++i)
		{
			outputFileStream << listv->v[i]->name << ' ' << listv->v[i]->x << ' ' << listv->v[i]->y << '\n';
		}

		outputFileStream << '\n'; // Endl between Vertexs and ListEdge

		for (int i = 0; i < num; ++i)
		{
			for (int j = 0; j < num; ++j)
			{
				if (weightMatrix[i][j] != NO_EDGE_VALUE)
				{
					outputFileStream << i << ' ' << j << ' ' << weightMatrix[i][j] << '\n';
				}
			}
		}

		outputFileStream.close();
		isSaved = 1;
	}
}

void closeFile(ListVertices *listVertex)
{
	if (!isSaved && !listVertex->isEmpty())
	{
		int id = MessageBox(hwnd, "Ban co muon luu do thi khong?", "Save file", MB_APPLMODAL | MB_ICONEXCLAMATION | MB_YESNOCANCEL);
		if (id == IDCANCEL)
			return;
		if (id == IDYES)
			return saveFile(listVertex);
	}

	closegraph();
	exit(EXIT_SUCCESS);
}