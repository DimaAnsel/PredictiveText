/*********
* TreeEdit.h
* Noah Ansel
* 2015-10-01
*************
* Function prototypes for the console
* tree editing program.
*************/

#pragma once

#include "main.h"
#include "CharTree.h"


enum CMD_STATUS {
	NO_CODE,
	EXIT_CODE,
	INVALID_STRING
};

int getAndDoCommand(CharTree* tree); // main function that gets and acts on a command
int splitOnChar(char in[], char word[], char rem[], char c); // splits a string at the first matching char it finds

int help(); // displays help info;

int wipe(CharTree* tree); // clears the tree file
int load(CharTree* tree); // loads tree from file
int save(CharTree* tree); // saves tree to file
int read(CharTree* tree, char filename[]); // teaches the tree from a file
int clear(CharTree* tree); // clears the program's tree