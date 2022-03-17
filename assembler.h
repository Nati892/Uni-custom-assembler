#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Macro_Handler.h"
#include "asm_utils.h"
#include "Assembler_Pass.h"
#include "File_utils.h"

int main(int argc, char **argv);
void handleFiles(int argc, char **argv);
void runAssembler(FILE *file, char *path);
void deleteOutputFiles(char *path);

#endif