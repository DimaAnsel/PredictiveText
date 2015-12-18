/*********
* main.cpp
* Noah Ansel
* 2015-09-25
*************
* Location of the main function which
* executes the program.
*************/

#include "main.h"
#include "CharTree.h"
#include "functs.h"
#include "TreeEdit.h"
#include "test.h"

int main(void) {

	CharTree* tree = new CharTree();

#ifdef TREE_EDIT // console edit program
	int ret_code = NO_CODE;

	while (ret_code != EXIT_CODE) {
		ret_code = getAndDoCommand(tree);
	}
#else
#ifdef TESTING
	FILE* fp;
	fp = fopen(TREE_FILENAME, "r");
	tree->parseIn(fp);
	closeFile(fp);
	printf("Loaded tree.\n");
	fp = fopen(TEST_FILENAME, "w"); // erases previous content
	closeFile(fp);

	printf("Testing %s . . .", TEST_1);
	testFile(tree, TEST_1);
	printf(" Done.\n");

	printf("Testing %s . . .", TEST_2);
	testFile(tree, TEST_2);
	printf(" Done.\n");

	printf("Press enter to exit . . .");
	getchar();
#endif
#endif
	//system("pause");
	return 0;
}