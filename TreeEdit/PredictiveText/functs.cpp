/*********
* functs.cpp
* Noah Ansel
* 2015-10-01
*************
* Miscellaneous functions used
* in multiple areas of the code.
*************/

#pragma once

#include "functs.h"

////////////////
// fileToTree: reads a file into a tree, using the provided node as the root
int fileToTree(FILE* fp, Node* &root) {
	int depth = 0;
	char c, currChar;
	unsigned int maxUses = 0;
	Node* parent = nullptr;
	Node* curr = nullptr;

	do {
		currChar = fgetc(fp);

		switch (currChar) {
		case '{': { // beginning of node
			curr = new Node();
			if (depth == 0) { // this is the beginning node
				root = curr;
			} else {
				curr->setParent(parent);
				parent->addKid(curr);
			}
			depth++;
			continue;
		}
		case '\'': { // character marker
			c = fgetc(fp);
			if (trackedChar(c)) { // not a tracked character
				curr->setChar(c);
			} else if (c == ' ') {
				continue; // do nothing; when writing file, '\0' translates to ' '
			} else { // bad character
				delete root;
				root = nullptr;
				return BAD_FILE;
			}
			continue;
		}
		case 'x': { // usgCnt marker
			fscanf(fp, "%X", &maxUses);
			curr->setMaxUses(maxUses);
			continue;
		}
		case '[': { // into child list
			parent = curr; // down a level
			continue;
		}
		case ']': { // out of child list
			parent = parent->getParent(); // back up a level
			continue;
		}
		case '}': { // end of node
			depth--;
			curr = nullptr; // done with this node
			continue;
		}
		}
	} while (currChar != EOF && depth != 0);

	return NO_ERROR;
}

////////////////
// trackedChar: tests if char is part of the alphabet
bool trackedChar(char c) {
	int i;
	for (i = 0; i < NUM_CHARS; i++) {
		if (c == CHARS[i]) {
			return true;
		}
	}
	return false;
}

////////////////
// wipeFile: wipes a saved tree file to a blank tree
void wipeFile(char filename[]) {
	FILE* fp = fopen(filename, "w");
	fprintf(fp, NODE_HEADER_FORMAT, '\0', MAX_UNSIGNED_INT);
	fprintf(fp, NODE_FOOTER_FORMAT, "");
	closeFile(fp);
}

////////////////
// closeFile: fclose wrapper with null check
int closeFile(FILE* fp) {
	if (fp == nullptr) {
		return 0;
	} else {
		return fclose(fp);
	}
}