#ifndef ASSEMBLER_PASS
#define ASSEMBLER_PASS
#include "Text_parse.h"
#include "LabelCollect.h"

enum ARE_FIELD
{
    A,
    R,
    E
};

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

void assemblerFirstPass(FILE *src, Assembler_mem *mem);
void assemblerSecondPass(FILE *src, Assembler_mem *mem);
void InitAssemblerMem(Assembler_mem *mem);
void restartAssemblerMem(Assembler_mem *mem);
void freeAssemblerMem(Assembler_mem *mem);
/*int ResetAssembler() {} */ /*to implement in future for more then one input file*/

/*helper methods for the main two big methods*/
void handleDataLine(char *str, Assembler_mem *mem);
void handleStringLine(char *str, Assembler_mem *mem);
void handleExtern(char *name, char *line, Assembler_mem *mem);
void handleEntry(char *name, char *line, Assembler_mem *mem);
void handleLabel(char *name, char *line, Assembler_mem *mem);
void handleCommand(char *str, Assembler_mem *mem);
void addToDataImage(int num, Assembler_mem *mem);
void announceSyntaxError(char *ERR, Assembler_mem *mem);
void checkExternSyntax(char *name, char *line, Assembler_mem *mem);
void checkEntrySyntax(char *name, char *line, Assembler_mem *mem);
void debugAsm(Assembler_mem *mem);

#endif

/*
add functions prototypes
write code for cammand handeling
write code for label handling
write code for ext detection when rewriting the commands

write second pass and translation

add files to compilation in end

add struct assembler_mem that will be generated prior to assembler



*/