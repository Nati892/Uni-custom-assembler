#ifndef ASSEMBLER_PASS_STAGES
#define ASSEMBLER_PASS_STAGES
#include "Text_parse.h"
#include "cmd_handler.h"
#include "asm_utils.h"
#include "File_utils.h"

void assemblerFirstPass(FILE *src, Assembler_mem *mem);  /*run assemblers first pass, collect all labels and look for syntax errors*/
void assemblerSecondPass(FILE *src, Assembler_mem *mem); /*look for errors that are not possible to find on first pass and translate the code to binary*/
void finalStage(Assembler_mem *mem);                     /*translate binary to special format and build files*/
/*int ResetAssembler() {} */                             /*to implement in future for more then one input file*/

/*helper methods for the main two big methods*/
void handleDataLine(char *str, Assembler_mem *mem);
void handleStringLine(char *str, Assembler_mem *mem);
void handleExtern(char *name, char *line, Assembler_mem *mem);
void handleEntry(char *name, char *line, Assembler_mem *mem);
void handleLabel(char *name, char *line, Assembler_mem *mem);
void handleCommand(char *str, Assembler_mem *mem);
void addToDataImage(int num, Assembler_mem *mem);
void checkExternSyntax(char *name, char *line, Assembler_mem *mem);
void checkEntrySyntax(char *name, char *line, Assembler_mem *mem);
void debugAsm(Assembler_mem *mem); /*DEBUG TODELETE*/
void reCalcLabels(Assembler_mem *mem);
void checkExternExists(Assembler_mem *mem); /*search from used lables, for lables that have not been announced*/
void translateDataImage(Assembler_mem *mem);

void createExtFile(Assembler_mem *mem);
void createEntFile(Assembler_mem *mem);
void createObFile(Assembler_mem *mem);

void checkEntryLables(Assembler_mem *mem);

void SpreadCommand(char *str, Assembler_mem *mem);

#define MAX_PROGRAM_LENGTH 8192
#define MAX_Line_LENGTH 80
#endif

/*
write code for ext detection when rewriting the commands

write second pass and translation
*/