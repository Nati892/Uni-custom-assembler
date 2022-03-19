#ifndef Macro_Handler_h
#define Macro_Handler_h

#include <stdio.h>
#include "LinkedList.h"
#include "File_utils.h"
#include "Text_utils.h"

FILE *macroStage(FILE *file, char *file_name);                /*start of macro stage*/
FILE *createMacroFile(char *file_name);                       /*reaturns a new opend ".am" file*/
void collectMacros(FILE *file, node *LL);                     /*collect all macros and store them in given linked List*/
void spreadMacros(FILE *src_file, FILE *dest_file, node *LL); /*the part that prints out all the macros found in the output file*/
 
#define MACRO_END_LENGTH 5

#endif
