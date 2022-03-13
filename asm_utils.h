#ifndef ASM_UTILS_H
#define ASM_UTILS_H

#include "LinkedList.h"
#include "Text_parse.h"
/*this struct represents all the memory needed for the assembler to operate*/
typedef struct
{
    int no_Errors;
    int DC;
    int IC;
    int line_counter;
    int *Data_Image; /*int array, both numbers and characters are converted to numbers in the end, so its beter*/
    int Data_Image_Length;
    char *String_Image;
    node *label_Table;
    node *ext_file_table; /*used in second pass*/
} Assembler_mem;

enum ARE_FIELD
{
    ARE_A,
    ARE_R,
    ARE_E
};

void InitAssemblerMem(Assembler_mem *mem);
void restartAssemblerMem(Assembler_mem *mem);
void freeAssemblerMem(Assembler_mem *mem);
void announceSyntaxError(char *ERR, Assembler_mem *mem);
void setARE(char *word, int ARE);
#endif