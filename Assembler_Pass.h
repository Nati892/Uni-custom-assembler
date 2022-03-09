#ifndef ASSEMBLER_PASS
#define ASSEMBLER_PASS
#include "Text_parse.h"
#include "LabelCollect.h"
static int no_Errors;
static int DC;
static int IC;
static int line_counter;
static int *Data_Image; /*int array, both numbers and characters are converted to numbers in the end, so its beter*/
static int Data_Image_Length;
static char *String_Image;
static node *label_Table;
static node *ext_file_table; /*used in second pass*/

enum ARE_FIELD
{
    A,
    R,
    E
};

enum SyntaxErrors
{
    CORRECT,

};

int assemblerFirstPass(FILE src);
int assemblerSecondPass(FILE src);

void handleDataLine(char *str);
void handleStringLine(char *str);
int ResetAssembler() {} /*to implement in future for more then one input file*/
#endif