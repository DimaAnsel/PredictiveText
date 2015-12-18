#pragma once

#include "main.h"
#include "CharTree.h"

int charUntilCorrect(CharTree* tree, char* word) {
	int i = 0;
	int len = (int)(strlen(word) + 1);
	char temp[MAX_WORD_LEN];
	char test[MAX_WORD_LEN];
	for (i = 0; i < MAX_WORD_LEN; i++) {
		temp[i] = '\0';
	}

	for (i = 0; i < len; i++) {
		temp[i] = word[i];
		tree->predictWord(temp, test, MAX_WORD_LEN);
		if (!(strcmp(test, word))) { // if same
			return i + 1; // strlen(temp)
		}
	}
	// never found word
	return _CRT_INT_MAX; // should never get here
}

void testFile(CharTree* tree, char* filename) {
	char word[MAX_WORD_LEN];
	char testword[MAX_WORD_LEN];
	char prevword[MAX_WORD_LEN];
	int chars;

	FILE* fp = fopen(filename, "r");
	if (fp == nullptr) {
		printf("Invalid file.");
		return;
	} else {
		// output file
		FILE* fout = fopen(TEST_FILENAME, "a");
		if (fp == nullptr) {
			printf("Failed to open output file.");
			return;
		}
		fprintf(fout, "%s,,\n", filename);

		// ignore first two lines
		fgets(word, MAX_WORD_LEN, fp);
		strcpy(prevword, word);
		fgets(word, MAX_WORD_LEN, fp);

		while (strcmp(word, prevword)) {
			strcpy(prevword, word);
			fgets(word, MAX_WORD_LEN, fp);
			sscanf(word, "%s\n", testword);
			chars = charUntilCorrect(tree, testword);
			fprintf(fout, ",%s,%d\n", testword, chars); // print word, char in csv format
		}
		fclose(fp);
		fclose(fout);
	}
}