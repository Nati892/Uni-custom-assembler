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

typedef struct Assembler_mem
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
};

void assemblerFirstPass(FILE *src);
void assemblerSecondPass(FILE *src);

/*int ResetAssembler() {} */ /*to implement in future for more then one input file*/

/*helper methods for the main two big methods*/
void handleDataLine(char *str);
void handleStringLine(char *str);
void handleExtern(char *name, char *line);
void handleEntry(char *name, char *line);
void handleLabel(char *name, char *line);
void handleCommand(char *str);
void addToDataImage(int num);
void announceSyntaxError(char *ERR);
void checkExternSyntax(char *name, char *line);
void checkEntrySyntax(char *name, char *line);
void debugAsm();

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