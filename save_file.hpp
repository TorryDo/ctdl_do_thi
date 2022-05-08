#pragma once

using namespace std;

void saveFile()
{
	OPENFILENAME file;
	char fileName[MAX_PATH] = "\0";
	ZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.lpstrFile = fileName;
	file.nMaxFile = sizeof(fileName);
	file.lpstrFilter = (FILE_FILTER);
	file.nFilterIndex = 1;
	file.hwndOwner = GetActiveWindow();
	file.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT;
	if (GetSaveFileName(&file) == 1)
	{
//		if (!strstr(fileName, ".graph")) {
//			strcat(fileName, ".graph"); // Add file name extension if it isn't exist, but be aware !!! 
//		}
//		std::ofstream saveFile(fileName);
//		const int num = listv.num;
//		saveFile << num << '\n';
//		for (int i = 0; i < num; ++i)
//			saveFile << listv.v[i]->name << ' ' << listv.v[i]->x << ' ' << listv.v[i]->y << '\n';
//		saveFile << '\n'; // Endl between Vertexs and ListEdge
//		for (int i = 0; i < num; ++i)
//			for (int j = 0; j < num; ++j)
//				if (adjaGraph[i][j] != NO_EDGE_VALUE)
//					saveFile << i << ' ' << j << ' ' << adjaGraph[i][j] << '\n';
//		saveFile.close();
//		isSaved = 1;
	}
}