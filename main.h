#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Macro_Handler.h"
#include "LabelCollect.h"
#include "Assembler_Pass.h"

int main(int argc, char **argv);
void handleParams(int argc, char **argv);
void doSomthingToFile(FILE *file, char *path);
void LabelTester(FILE *file);
#define AS_FILE_ENDING ".as"


#endif