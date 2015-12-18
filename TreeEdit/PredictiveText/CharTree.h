/*********
* CharacterTree.h
* Noah Ansel
* 2015-09-25
*************
* Data and method prototypes for the
* tree that stores learned words.
*************/

#include <stdio.h>
#include <stdlib.h>
#include "main.h"


enum NODE_STUFF {
	NO_ERROR,
	BAD_FILE,
	TOO_MANY_KIDS,
	INVALID_COUNT,
	USG_CNT_OVERFLOW
};

/////////////////
// Node:
//	Members:
//		character	the character this node represents
//		maxUses		number of uses of most common word
//		children	list of this node's children
//		parent		this node's parent
//
class Node {
private:
	char character;
	unsigned int maxUses;
	Node* children[NUM_CHARS];
	Node* parent;
public:
	Node();
	Node(char c);
	~Node();

	// getter/setters
	void setParent(Node* parent);
	Node* getParent();
	unsigned int getMaxUses();
	char getChar();
	void setChar(char c);
	void setMaxUses(unsigned int uses);

	int inc(); // increments maxUses (overflow check)
	void dec(); // decrements maxUses (deletes if empty)

	Node* biggestKid();		// find most used child
	int addKid(Node* kid);	// add child
	Node* find(char c);		// find child with given char

	void print(char end[]);	// print to console; for debug
	void printInd(int indents);
	int writeOut(FILE* fp);	//
	void writeOutInd(FILE* fp, int indents);
};


/////////////////
// CharTree:
//	Members:
//		head	pointer to head of tree
//		curr	current character pointer
//		depth	curr's depth
//
class CharTree {
private:
	Node* root; // base of tree
	Node* curr; // pointer to current node of tree
	int depth; // curr's depth (0 if curr == root)
public:
	CharTree();
	~CharTree();

	Node* getCurr();
	Node* getRoot();

	void charAction(char c);

	void writeOut(FILE* fp);
	int parseIn(FILE* fp);
	void print();

	void learnFromFile(char filename[]); // reads a file and teaches the tree off the words it finds
	void learnWord(char word[]); // teaches the tree a single word
	void predictWord(char inp[], char buff[], int size); // predicts a word from inp and returns the word in buff
};

#pragma once