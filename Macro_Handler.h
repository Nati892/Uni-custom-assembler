#ifndef Macro_Handler_h
#define Macro_Handler_h

#include "LinkedList.h"
#include "Text_parse.h"

void macroStage(FILE *file, char *file_name); /*start of acro stage*/
FILE *createMacroFile(char *file_name);
void collectMacros(FILE *file, node *LL);                     /*collect all macros and store them in giver linked List*/
void spreadMacros(FILE *src_file, FILE *dest_file, node *LL); /*the part that prints out all the macros found in the output file*/

#define MACRO_END_LENGTH 5
#define AM_FILE_NAME_ENDING ".am"

#endif
