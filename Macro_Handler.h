#ifndef Macro_Handler_h
#define Macro_Handler_h

#include "LinkedList.h"
#include "Text_parse.h"

void macroStage(FILE *file, char *file_name);/*start of acro stage*/
FILE *createMacroFile(char *file_name);
void collectMacros(FILE *file, node *LL);/*collect all macros and store them in giver linked List*/
void storeMacro(node *LL, char *macro_name, char *macro_body);/*stores a new macro in list*/
node *searchMacro(node *LL, char *key);/*searches for a macro in a given linked list, returns NULL in case of failure*/
void spreadMacros(FILE *src_file, FILE *dest_file, node *LL);/*the part that prints out all the macros found in the output file*/
void copySubstringToFile(FILE *dest_file, char *mystring, int start, int length);
int isMacroStart(char *text);/*checks if word is macro start*/
int isMacroEnd(char *text);/*checks if word is macro end*/

#define MACRO_START "macro"
#define MACRO_END "endm"
#define MACRO_END_LENGTH 5
#define AM_FILE_NAME_ENDING ".am"

#endif

