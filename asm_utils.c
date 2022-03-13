#include "asm_utils.h"
void InitAssemblerMem(Assembler_mem *mem)
{
    mem->no_Errors = 1;
    mem->Data_Image = (int *)malloc(1 * sizeof(int));
    mem->Data_Image_Length = 0;
    mem->DC = 1;
    mem->IC = 100;
    mem->line_counter = 1;
    mem->no_Errors = 1;
    mem->label_Table = initList();
    mem->String_Image = initString();
}

void restartAssemblerMem(Assembler_mem *mem)
{
    mem->no_Errors = 1;
    free(mem->Data_Image);
    mem->Data_Image = (int *)malloc(1 * sizeof(int));
    mem->Data_Image_Length = 0;
    mem->DC = 0;
    mem->IC = 100;
    mem->line_counter = 1;
    mem->no_Errors = 1;
    killList(mem->label_Table);
    mem->label_Table = initList();
    free(mem->String_Image);
    mem->String_Image = initString();
}

void freeAssemblerMem(Assembler_mem *mem)
{
    free(mem->Data_Image);
    killList(mem->label_Table);
    free(mem->String_Image);
    free(mem);
}

void announceSyntaxError(char *ERR, Assembler_mem *mem)
{
    mem->no_Errors = FALSE;
    printf("ERROR in line %d:: %s\n", mem->line_counter, ERR);
}
