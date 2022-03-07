#ifndef ASSEMBLER_PASS
#define ASSEMBLER_PASS
#include "Text_parse.h"
#include "LabelCollect.h"
static int no_Errors;
static int DC;
static int IC;
static int line_counter;
static char *Data_Image;
static char *String_Image;
static node *label_Table;

enum ARE_FIELD
{
    A,
    R,
    E
};

enum SyntaxErrors{
    CORRECT,

};

int assemblerFirstPass(FILE src) {}
int assemblerSecondPass(FILE src) {}

int ResetAssembler() {} /*to implement in future for more then one input file*/
#endif