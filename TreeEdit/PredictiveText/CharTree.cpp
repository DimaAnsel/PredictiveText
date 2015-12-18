/*********
* CharTree.cpp
* Noah Ansel
* 2015-09-25
*************
* Method definitions for the main character
* tree and node classes.
*************/

#include "main.h"
#include "CharTree.h"
#include "functs.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////	Node	////////////////////////////////////////////////////////

////////////////
// Node(): default character to \0; used for root of tree
Node::Node() {
	int i;
	this->character = '\0';
	this->maxUses = 0;
	this->parent = nullptr;
	for (i = 0; i < NUM_CHARS; i++) {
		this->children[i] = nullptr;
	}
}

////////////////
// Node(char): for non-empty Nodes
Node::Node(char c) {
	int i;

	this->character = c;
	this->maxUses = 0;
	for (i = 0; i < NUM_CHARS; i++) {
		this->children[i] = nullptr;
	}
}

////////////////
// ~Node(): delete node (and children)
Node::~Node() {
	int i;
	for (i = 0; i < NUM_CHARS; i++) {
		if (this->children[i] != nullptr) {
			delete this->children[i];
		}
	}
}

////////////////
// getter/setters
Node* Node::getParent() {
	return this->parent;
}
void Node::setParent(Node* parent) {
	this->parent = parent;
}
unsigned int Node::getMaxUses() {
	return this->maxUses;
}
char Node::getChar() {
	return this->character;
}
void Node::setChar(char c) {
	this->character = c;
}
void Node::setMaxUses(unsigned int uses) {
	this->maxUses = uses;
}

///////////////////
// inc: increments this node's usage count; checks for overflow
int Node::inc() {
	if (this->maxUses < MAX_UNSIGNED_INT) {
		this->maxUses++;
		this->parent->setMaxUses(this->parent->biggestKid()->getMaxUses());
		return NO_ERROR;
	} else { // cannot increment
		return USG_CNT_OVERFLOW;
	}
}
///////////////////
// dec: decrements this node's usage count; deletes if empty
void Node::dec() {
	Node* par = this->parent;
	if (this->maxUses <= 0) {
		if (this->parent->biggestKid() == this) {
			delete this;
			par->setMaxUses(par->biggestKid()->getMaxUses());
		} else {
			delete this;
		}
	} else {
		this->maxUses--;
		par->setMaxUses(par->biggestKid()->getMaxUses());
	}
}

////////////////
// biggestKid: Finds most used child of this node
Node* Node::biggestKid() {
	int i, maxIdx = 0;
	for (i = 0; i < NUM_CHARS; i++) {
		// compare usageCounts
		if (this->children[i] != nullptr) {
			if (this->children[i]->getMaxUses() > this->children[maxIdx]->getMaxUses()) {
				maxIdx = i;
			}
		}
	}
	// Note: defaults to nullptr if no children
	return this->children[maxIdx];
}

////////////////
// addKid: Adds the provided node to this node's list of children, if possible
int Node::addKid(Node* kid) {
	int i;
	for (i = 0; i < NUM_CHARS; i++) {
		// find empty spot
		if (this->children[i] == nullptr) {
			this->children[i] = kid;
			kid->setParent(this);
			return NO_ERROR;
		}
	}
	// no more spots for children
	return TOO_MANY_KIDS;
}

////////////////
// find: Finds a node with character c among this node's children; default nullptr
Node* Node::find(char c) {
	for (int i = 0; i < NUM_CHARS; i++) {
		if ((this->children[i] != nullptr) &&
			(this->children[i]->getChar() == c)) {
				return this->children[i];
		}
	}
	return nullptr;
}



////////////////
// print: Prints node to console (for debugging)
void Node::print(char end[]) {
	int i;
	bool addComma = false;
	printf(NODE_HEADER_FORMAT, this->character, this->maxUses);
	for (i = 0; i < NUM_CHARS; i++) {
		if (this->children[i] != nullptr) {
			if (addComma) {
				printf(",\n");
			} else {
				printf("\n");
				addComma = true;
			}
			this->children[i]->printInd(1);
		}
	}
	printf(NODE_FOOTER_FORMAT, end);
}
// print with ability for indents
void Node::printInd(int indents) {
	int i;
	bool addComma = false;
	for (i = 0; i < indents; i++) {
		printf("\t");
	}
	printf(NODE_HEADER_FORMAT, this->character, this->maxUses);
	for (i = 0; i < NUM_CHARS; i++) {
		if (this->children[i] != nullptr) {
			if (addComma) {
				printf(",");
			}
			printf("\n");
			this->children[i]->printInd(indents + 1);
			addComma = true;
		}
	}
	printf(NODE_FOOTER_FORMAT,"");
}

////////////////
// writeOut: Writes Node to file (for permanent storage)
int Node::writeOut(FILE* fp) {
	int i;
	bool addComma = false;
	fprintf(fp, NODE_HEADER_FORMAT, this->character, this->maxUses);
	for (i = 0; i < NUM_CHARS; i++) {
		if (this->children[i] != nullptr) {
			if (addComma) {
				fprintf(fp, ",");
			}
			//fprintf(fp, "\n");
			this->children[i]->writeOutInd(fp, 1);
			addComma = true;
		}
	}
	fprintf(fp, NODE_FOOTER_FORMAT,"");

	return NO_ERROR;
}
// writeOut with ability for indents
void Node::writeOutInd(FILE* fp, int indents) {
	int i;
	bool addComma = false;
	//for (i = 0; i < indents; i++) { // comment out to save about half the file size (but reduce readability)
	//	fprintf(fp, "\t");
	//}
	fprintf(fp, NODE_HEADER_FORMAT, this->character, this->maxUses);
	for (i = 0; i < NUM_CHARS; i++) {
		if (this->children[i] != nullptr) {
			if (addComma) {
				fprintf(fp, ",");
			}
			//fprintf(fp, "\n");
			this->children[i]->writeOutInd(fp, indents + 1);
			addComma = true;
		}
	}
	fprintf(fp, NODE_FOOTER_FORMAT,"");
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////	CharTree	////////////////////////////////////////////////////////

////////////////
// CharTree: makes blank Node for head; curr defaults to head
CharTree::CharTree() {
	this->root = new Node();
	this->root->setMaxUses(MAX_UNSIGNED_INT); // if left at 0, error occurs
	this->curr = this->root;
	this->depth = 0;
}

///////////////////
// ~CharTree: deletes all nodes (recursively) before deleting this tree
CharTree::~CharTree() {
	delete this->root;
}

///////////////////
// getters/setters
Node* CharTree::getRoot() {
	return this->root;
}
Node* CharTree::getCurr() {
	return this->curr;
}

///////////////////
// inherited from Node
void CharTree::writeOut(FILE* fp) {
	this->root->writeOut(fp);
}
int CharTree::parseIn(FILE* fp) {
	return fileToTree(fp, this->root);
}
void CharTree::print() {
	this->root->print("\n");
}

///////////////////
// charAction: adjusts the tree as necessary for new character
void CharTree::charAction(char c) {
	Node* charNode;
	if (trackedChar(c)) { // part of a word
		charNode = curr->find(c);
		if (charNode == nullptr) {
			charNode = new Node(c);
			this->curr->addKid(charNode);
		}
		this->curr = charNode;
		this->depth++;
	} else { // end of word
		// increment the word-terminator (or create one)
		charNode = curr->find('\0');
		if (charNode == nullptr) {
			charNode = new Node('\0');
			this->curr->addKid(charNode);
		}
		charNode->inc();

		// now update parents if needed
		while (this->depth > 0) { // breaks if 0
			if (charNode->getMaxUses() > this->curr->getMaxUses()) { // there's a new max in town
				this->curr->setMaxUses(charNode->getMaxUses());
			}
			this->curr = this->curr->getParent(); // go up one
			this->depth--;
		}
	}
}

///////////////////
// learnFromFile: the character tree reads the file and populates/modifies its tree based on the words it finds 
void CharTree::learnFromFile(char filename[]) {
	FILE* fp = fopen(filename, "r");
	if (fp == nullptr) {
		printf("Invalid file: %s\n",filename);
		return;
	}
	char c;
	this->curr = this->root;
	this->depth = 0;
	for (c = fgetc(fp); c != EOF; c = fgetc(fp)) {
		this->charAction(c);
	}
	closeFile(fp);
	printf("Read file: %s\n", filename);
}

///////////////////
// predictWord: follows most used path until reaches end node; stores word in buff, returns size of word
void CharTree::predictWord(char inp[], char buff[], int buffSize) {	
	int i;
	Node* temp = this->root;

	for (i = 0; inp[i] != '\0'; i++) {
		temp = temp->find(inp[i]);
		if (temp == nullptr) { // no word exists
			strcpy(buff, inp);
			return;
		}
	}

	while (temp->biggestKid() != nullptr) {
		temp = temp->biggestKid(); // seek out most common word
		i++;
	}
	if (i > buffSize) {
		do { // clip if necessary
			temp = temp->getParent();
			i--;
		} while (i >= buffSize); // until in valid memory
		buff[i] = '\0'; // null-terminate
		temp = temp->getParent(); // now go up again
		i--;
	}
	i--; // omit 0 (root of tree '\0')
	// now go up to top, copying as you go
	for (; i >= 0; i--) {
		buff[i] = temp->getChar();
		temp = temp->getParent();
	}
}

void CharTree::learnWord(char word[]) {
	this->curr = this->root;
	this->depth = 0;
	int i;
	for (i = 0; word[i] != '\0'; i++) {
		this->charAction(word[i]);
	}
	this->charAction(' ');
}