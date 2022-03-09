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

/*
add functions prototypes
write code for cammand handeling
write code for label handling
write code for ext detection when rewriting the commands

write second pass and translation
write macro for error handling->
-no-error=False;
error in LINE, ERROR;

add files to compilation in end



*/