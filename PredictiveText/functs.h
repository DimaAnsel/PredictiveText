/*********
* functs.h
* Noah Ansel
* 2015-10-01
*************
* Function prototypes for the
* miscellaneous functions found in
* functs.cpp.
*************/

#pragma once

#include "main.h"
#include "CharTree.h"

int fileToTree(FILE* fp, Node* &root);
bool trackedChar(char c);

void wipeFile(char filename[]);

int closeFile(FILE* fp);