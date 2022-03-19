#ifndef ASSEMBLER_PASS_STAGES
#define ASSEMBLER_PASS_STAGES
#include "Text_utils.h"
#include "cmd_handler.h"
#include "asm_utils.h"
#include "File_utils.h"

void assemblerFirstPass(FILE *src, Assembler_mem *mem);  /*run assemblers first pass, collect all labels and look for syntax errors*/
void assemblerSecondPass(FILE *src, Assembler_mem *mem); /*look for errors that are not possible to find on first pass and translate the code to binary*/
void finalStage(Assembler_mem *mem);                     /*translate binary to special format and build files*/

/*helper methods for the first passes methods*/
void handleDataLine(char *str, Assembler_mem *mem);                 /*gets a .data line, and checks for errors*/
void handleStringLine(char *str, Assembler_mem *mem);               /*gets a .string line, and checks for errors*/
void handleExtern(char *name, char *line, Assembler_mem *mem);      /*gets a .extern line, checks for errors and handles label*/
void handleEntry(char *name, char *line, Assembler_mem *mem);       /*gets a .entry line, checks for errors and handles label*/
void handleLabel(char *name, char *line, Assembler_mem *mem);       /*handles a line that starts with a label declartion*/
void handleCommand(char *str, Assembler_mem *mem);                  /*checks for errors in a commad line */
void addToDataImage(int num, Assembler_mem *mem);                   /*stores .data and .string lines in Data image of Asm-mem*/
void checkExternSyntax(char *name, char *line, Assembler_mem *mem); /*handles extern syntax that is in the same line as label definition*/
void checkEntrySyntax(char *name, char *line, Assembler_mem *mem);  /*handles entry syntax that is in the same line as label definition*/
void reCalcLabels(Assembler_mem *mem);                              /*reclculates correct value for each label in table */
void checkUnusedLabels(Assembler_mem *mem);                         /*search from used lables, for lables that have not been announced*/
void translateDataImage(Assembler_mem *mem);                        /*translate the .data/.string lines into machine code after the Instruction image*/

void createExtFile(Assembler_mem *mem);
void createEntFile(Assembler_mem *mem);
void createObFile(Assembler_mem *mem);

void checkEntryLables(Assembler_mem *mem); /*make sure there arent any entry lables that are not defined*/

void SpreadCommand(char *str, Assembler_mem *mem); /*translate command to binary string and write it to the mem->String_image*/

#define MAX_PROGRAM_LENGTH 8192
#define MAX_Line_LENGTH 80
#endif

/*
write code for ext detection when rewriting the commands

write second pass and translation
*/