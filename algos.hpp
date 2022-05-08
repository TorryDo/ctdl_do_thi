#pragma once

#include "list_vertices.hpp"

using namespace std;


void canhCau(ListVertices *listVertices)
{
	if (isEmptyGraph()) return;
	int SCC = tarjanAlgo(0); // first find current SCC
	int count(0);
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac canh cau tim duoc:");
	for (int i = 0; i < *listVertices.num; ++i)
		for (int j = 0; j < *listVertices.num; ++j)
			if (adjaGraph[i][j] != NO_EDGE_VALUE)
			{
				float backup = adjaGraph[i][j]; // backup edge
				adjaGraph[i][j] = NO_EDGE_VALUE; // Delete edge
				int SCCAfterRemoveEdge = tarjanAlgo(0); // recalculate SCC
				adjaGraph[i][j] = backup; // restore
				if (SCCAfterRemoveEdge > SCC) // is strong bridge
				{
					++count;
					drawEdge(i, j, EDGE_HIGHTLIGHT_COLOR);
					setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
					printText("(");
					printText(*listVertices.v[i]->name);
					printText(",");
					printText(*listVertices.v[j]->name);
					printText(");");
				}
			}
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tong cong: ");
	printText(count);
	return backToMenu();
}