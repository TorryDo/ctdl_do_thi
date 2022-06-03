#pragma once

#include "graphics.h"
#include <fstream>
#include <iostream>

using namespace std;

const char DIALOG_WARN_OPEN_FILE[] = " workspace dang mo \n ban co muon mo file moi khong";

bool isConfirmed()
{
    return MessageBox(GetActiveWindow(), DIALOG_WARN_OPEN_FILE, "Thong bao", MB_APPLMODAL | MB_ICONWARNING | MB_YESNO) == IDNO;
}

void openFile(ListVertices *listv)
{

    if (!listv->isEmpty() && isConfirmed())
        return;

    OPENFILENAME file;
    char fileName[MAX_PATH] = "\0";

    SecureZeroMemory(&file, sizeof(file));
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
        ifstream inputFileStream(fileName);
        int num;
        if ((inputFileStream >> num) && inputFileStream.good())
        {
            listv->clear();
            setMatrixTo(weightMatrix, NO_EDGE_VALUE); // Clear maxtix
            char tmpName[MAX_NAME_LENGTH];
            int x, y;
            float weight;
            for (int i = 0; i < num && !error; ++i)
            {
                if (!(inputFileStream >> tmpName >> x >> y))
                {
                    error = 1;
                }
                else
                {
                    listv->addVertex(tmpName, x, y);
                }
            }

            if (!error)
            {
                while (!inputFileStream.eof())
                {
                    if (!(inputFileStream >> x >> y >> weight))
                    {
                        break;
                    }

                    else
                    {
                        weightMatrix[x][y] = weight;
                    }
                }
            }

            isSaved = 1;
        }
        else
            error = 1;
        inputFileStream.close();
    }
    if (error)
    {
        listv->clear();
        setMatrixTo(weightMatrix, NO_EDGE_VALUE); // Clear maxtix
        MessageBox(GetActiveWindow(), "LOI DOC FILE!", "Loi", MB_APPLMODAL | MB_ICONERROR);
    }
}