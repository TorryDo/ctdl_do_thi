#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include <fstream>					
#include <iostream>
#include <conio.h>
#include <limits.h>
#include <stddef.h>
#include <sstream>
#include <Windows.h>
#include <windows.h>
#include <windowsx.h> 
//#ifndef WINBGI_H
#define WINBGI_H
//#include "list_vertices.hpp"

using namespace std;

const char DIALOG_WARN_OPEN_FILE[] = " workspace dang mo \n ban co muon mo file moi khong"; 

void openFile(ListVertices *listv)
{
		
	if (MessageBox(GetActiveWindow(), DIALOG_WARN_OPEN_FILE,"Thong bao", MB_APPLMODAL | MB_ICONWARNING | MB_YESNO) == IDNO) return;
	OPENFILENAME file;
	char fileName[MAX_PATH] = "\0";
//	_getcwd(fileName, MAX_PATH);
	ZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.lpstrFile = fileName;
	file.nMaxFile = sizeof(fileName);
	file.lpstrFilter = (FILE_FILTER);
	file.nFilterIndex = 1;
	file.hwndOwner = GetActiveWindow();
	file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_READONLY;
	bool error = 0;
	
	if (GetOpenFileName(&file))
	{
		while (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);	
		}
		ifstream openFile(fileName);
		int num;
		if ((openFile >> num) && openFile.good())
		{
			
			listv->clear();
			setMatrixTo(adjaGraph, NO_EDGE_VALUE); //Clear maxtix
			char tmpName[MAX_NAME_LENGTH];
			int x, y;
			float weight;
			for (int i = 0; i < num && !error; ++i){
				if (!(openFile >> tmpName >> x >> y)) {
					error = 1;	
				}else{
					listv->addVertex(tmpName, x, y);
				}
			}
				
			if (!error){
				while (!openFile.eof())
				{
					if (!(openFile >> x >> y >> weight)) break;
					else adjaGraph[x][y] = weight;
				}
			}
				
			isSaved = 1;
			
		}
		else error = 1;
		openFile.close();
	}
	if (error) 
	{
		listv->clear();
		setMatrixTo(adjaGraph, NO_EDGE_VALUE); //Clear maxtix
		MessageBox(GetActiveWindow() , "LOI DOC FILE!!!", "Loi",  MB_APPLMODAL | MB_ICONERROR);
	}
}