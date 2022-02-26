#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include "File_utils.h"
#include "LinkedList.h"
#include "Macro_Handler.h"
#include "LabelCollect.h"


int main(int argc, char **argv);
void handleParams(int argc, char **argv);
void doSomthingToFile(FILE *file, char *path);
#define AS_FILE_ENDING ".as"


#endif