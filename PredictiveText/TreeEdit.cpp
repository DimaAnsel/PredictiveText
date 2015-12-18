/*********
* TreeEdit.cpp
* Noah Ansel
* 2015-10-01
*************
* A simple console program for
* basic tree manipulation/training.
*************/

#include "TreeEdit.h"
#include "functs.h"


////////////////
// getAndDoCommand: recieves and acts on a single command
//	main loops this until EXIT_CODE is returned
int getAndDoCommand(CharTree* tree) {
	char cmd_in[MAX_CMD_LEN] = "";
	char cmd_head[MAX_CMDHEAD_LEN] = "";
	char cmd_tail[MAX_CMDTAIL_LEN] = "";
	int ret_code = NO_CODE;

	// ask for and recieve input
	printf("[%s] >> ", CONSOLE_PROGRAM_NAME);
	gets_s(cmd_in); // read until a '\n'
	splitOnChar(cmd_in, cmd_head, cmd_tail, ' ');

	// take action based on cmd_head (command type)
	if (!strncmp(cmd_in, "help", 4) || 
		 !strcmp(cmd_in, "h")) {
		ret_code = help();
	} else if (!strncmp(cmd_in, "wipe", 4) ||
				!strcmp(cmd_in, "w")) {
		ret_code = wipe(tree);
	} else if (!strncmp(cmd_in, "load", 4) ||
				!strcmp(cmd_in, "l")) {
		ret_code = load(tree);
	} else if (!strncmp(cmd_in, "save", 4) ||
				!strcmp(cmd_in, "s")) {
		ret_code = save(tree);
	} else if (!strncmp(cmd_in, "read ", 5) || // must have something
			   !strncmp(cmd_in, "r ", 2)) {    // follow this command
		ret_code = read(tree, cmd_tail);
	} else if (!strncmp(cmd_in, "clear", 5) ||
		!strcmp(cmd_in, "c")) {
		ret_code = clear(tree);
	} else if (!strncmp(cmd_in, "exit", 4) ||
				!strcmp(cmd_in, "x")) {
		ret_code = EXIT_CODE; // exits the program

	} else {
		printf("Invalid command. Use help to see valid commands.\n");
	}
	return ret_code;
}

///////////////////
// splitOnChar: splits a string at the first char c it finds
int splitOnChar(char in[], char word[], char rem[], char c) {
	int i, j;

	for (i = 0; i < MAX_CMD_LEN && in[i] != c &&
		 in[i] != '\0'; i++) { // copy until char or end of str
		word[i] = in[i];
	}
	if (in[i] == '\0') { // no split
		word[i] = '\0';
		rem[0] = '\0'; // no space, so remainder is empty
	} else if (in[i] == c) { // split
		word[i] = '\0'; // terminate
		i++; // pass the space
		for (j = 0; j < MAX_CMDTAIL_LEN && in[i] != '\0' && in[i] != '\n'; i++, j++) {
			rem[j] = in[i]; // copy remainder
		}
		if (j < MAX_CMDTAIL_LEN) {
			rem[j] = '\0'; // terminate
		} else { // invalid string
			rem[j - 1] = '\0';
			return INVALID_STRING;
		}
	} else { // invalid string
		word[i - 1] = '\0';
		rem[0] = '\0';
		return INVALID_STRING;
	}

	return NO_CODE;
}

///////////////////
// help: prints help page
int help() {
	char c;
	FILE* fp = fopen("TreeEdit_help.txt", "r");
	if (fp == nullptr) {
		printf("Help file not found.\n");
	} else {
		for (c = fgetc(fp); c != EOF; c = fgetc(fp)) {
			printf("%c",c);
		}
		printf("\n");
	}
	closeFile(fp);
	return NO_CODE;
}

///////////////////
// wipe: wipes the tree file
int wipe(CharTree* tree) {
	wipeFile(TREE_FILENAME);
	printf("Wiped tree file: %s\n", TREE_FILENAME);
	return NO_CODE;
}

///////////////////
// load: loads from the tree file
int load(CharTree* tree) {
	FILE* fp = fopen(TREE_FILENAME, "r");
	if (fp == nullptr) { // no file exists, so make a clean one
		closeFile(fp);
		printf("No file found. Creating clean tree file...\n");
		wipeFile(TREE_FILENAME);
		fopen(TREE_FILENAME, "r");
	}
	tree->parseIn(fp);
	closeFile(fp);
	printf("Loaded tree from: %s\n", TREE_FILENAME);
	return NO_CODE;
}

///////////////////
// save: saves to the tree file
int save(CharTree* tree) {
	FILE* fp = fopen(TREE_FILENAME, "w");
	tree->writeOut(fp);
	closeFile(fp);
	printf("Saved tree to: %s\n", TREE_FILENAME);
	return NO_CODE;
}

///////////////////
// read: reads as many files as are provided in cmd_tail
int read(CharTree* tree, char cmd_tail[]) {
	char currfile[MAX_CMDTAIL_LEN];
	splitOnChar(cmd_tail, currfile, cmd_tail, ' '); // take off first file

	if (currfile[0] != '\0') { // there is a file to try to parse
		tree->learnFromFile(currfile);
	} else { // no filename
		return INVALID_STRING;
	}
	if (cmd_tail[0] != '\0' || cmd_tail[0] != '\n') { // more files to read
		read(tree, cmd_tail);
	}
	return NO_CODE;
}

///////////////////
// clear: clears the program's tree
int clear(CharTree* tree) {
	delete tree;
	tree = new CharTree();
	printf("Cleared tree\n");
	return NO_CODE;
}