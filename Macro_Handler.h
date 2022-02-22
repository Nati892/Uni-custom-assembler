#ifndef Macro_Handler_h
#define Macro_Handler_h

#include "LinkedList.h"
#include "File_utils.h"
#include "Text_parse.h"
void macroStage(FILE *file, char *file_name);/*start of acro stage*/
FILE *createMacroFile(char *file_name);
void collectMacros(FILE *file, node *LL);/*collect all macros and store them in giver linked List*/
void printMacro(FILE *output_file, node *macro);/*given a macro, the function prints the macro's contents to a given file*/
void storeMacro(node *LL, char *macro_name, char *macro_body);/*stores a new macro in list*/
node *searchMacro(node *LL, char *key);/*searches for a macro in a given linked list, returns NULL in case of failure*/

void spreadMacros(FILE *src_file, FILE *dest_file, node *LL);/*the part that prints out all the macros found in the output file*/


int isCommentLine(char *line);/*returns 1 if its a comment line and 0 if not*/
void copySubstringToFile(FILE *dest_file, char *mystring, int start, int length);
int isMacroStart(char *text);
int isMacroEnd(char *text);
int ReachedEOF(char* txt);


#define MACRO_START "macro"
#define MACRO_END "endm"
#define MACRO_END_LENGTH 5
#define AM_FILE_NAME_ENDING ".am"

#endif

/*
TODO:
BACK UP PROJET TO PC!!!!
LOOK AT GIT IN MAKING YOUR OWN PRIVATE RASPBY PI TO BE GIT SERVER AND BACKUP!
make general 'create file function' in file handler
go throug code again and look for bugs
make test files!
and tester!
clean up printf's
make parsing file, move parsing methods to there.
Go through code and look for functions that need to be generalized.
make sure this stage is complete and replan the next thing in the project

*/