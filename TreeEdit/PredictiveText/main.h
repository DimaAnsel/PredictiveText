/*********
* main.h
* Noah Ansel
* 2015-09-25
*************
* Contains all necessary definitions for 
* the program. Common include.
*************/

#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <cstdlib>

#define CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'"
#define NUM_CHARS (26*2 + 2)

// used for parsing file into a tree
#define NODE_HEADER_FORMAT "{'%c,x%X,["
#define NODE_FOOTER_FORMAT "]}%s"
#define MAX_UNSIGNED_INT 0xFFFFFFFF
#define MAX_WORD_LEN 512 // unnecessarily large, but who really cares


// TreeEdit
#define MAX_CMDHEAD_LEN 16 // max length of an input string
#define MAX_CMDTAIL_LEN 2048 // sufficiently long for any reasonable command
#define MAX_CMD_LEN (MAX_CMDHEAD_LEN + 1 + MAX_CMDTAIL_LEN)
#define CONSOLE_PROGRAM_NAME "TreeEdit"
#define TREE_FILENAME "C:/Temp/wordTree.txt"

// Testing
#define TEST_1 "C:/Temp/commonverbs.txt"
#define TEST_2 "C:/Temp/testwords.txt"
#define TEST_FILENAME "C:/Temp/testOutput.csv"

#define TREE_EDIT // console editing program
//#define TESTING // for testing word prediction