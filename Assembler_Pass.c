#include "Assembler_Pass.h"

static int no_Errors;
static int DC;
static int IC;
static int line_counter;
static int *Data_Image; /*int array, both numbers and characters are converted to numbers in the end, so its beter*/
static int Data_Image_Length;
static char *String_Image;
static node *label_Table;
static node *ext_file_table; /*used in second pass*/

void assemblerFirstPass(FILE *src)
{
    /*setting up some  global normal and static variables, and setting file pointer to start.
    In the first pass there is no need to write to the instruction image, only to understand how long is each instruction,
    for label usage, in the second pass the instructions will be translated.
    The data image will be filled in the first pass;
    And all the labels will be collected*/
    char *curr_Line, *temp, *curr_Word;
    node *currLabel;
    label_Table = initList();
    fseek(src, 0, SEEK_SET); /*set file read point to start*/
    line_counter = 1;        /*line count starts at 1*/
    no_Errors = 1;
    DC = 0;
    IC = 100;
    Data_Image = (char *)malloc(1);
    Data_Image_Length = 0;

    curr_Line = getLine(src);
    while (curr_Line != NULL) /*loop through the lines*/
    {
        if (!isCommentLine(curr_Line) && !isOnlyWhiteChars(curr_Line)) /*if its a comment then Ignore the line*/
        {
            /*ToDo add check for line length*/

            curr_Word = getTrimmedWordFromLine(curr_Line);
            if (isEntryDefinition(curr_Word) || isExternDefinition(curr_Word) || isDataLabelDefinition(curr_Word) || isStringLabelDefinition(curr_Word))
            {
                /*handle special lables, no instructions handling needed here*/
                if (isExternDefinition(curr_Word)) /*handle Extern def */
                {
                    free(curr_Word);
                    curr_Line = extractWordFromStart(curr_Line);
                    curr_Word = getTrimmedWordFromLine(curr_Line); /*get name of label*/

                    handleExtern(curr_Word, curr_Line);
                }
                else
                {
                    if (isEntryDefinition(curr_Word)) /*handle entry def*/
                    {
                        free(curr_Word);
                        curr_Line = extractWordFromStart(curr_Line);
                        curr_Word = getTrimmedWordFromLine(curr_Line); /*get name of label*/

                        handleEntry(curr_Word, curr_Line);
                        free(curr_Word);
                    }
                    else
                    {
                        if (isDataLabelDefinition(curr_Word)) /*handle .data array*/
                        {
                            handleDataLine(curr_Line); /*ToDo*/
                            free(curr_Word);
                        }
                        else
                        {
                            if (isStringLabelDefinition(curr_Word)) /*handle String array*/
                            {
                                handleStringLine(curr_Line); /*ToDo*/
                                free(curr_Word);
                            }
                        }
                    }
                }
            }
            else /*if just an instruction or label and then .data/.string*/
            {
                if (isLabelDefinition(curr_Word))
                {
                    handleLabel(curr_Word, curr_Line); /*handles options for .data .string .entry .extern and possible command*/
                }
                else
                {
                    handleCommand(curr_Line); /* adds command length to IC*/
                }
                free(curr_Word);
                /*handle insruction*/
            }
        }
        if (curr_Line != NULL)
            free(curr_Line);
        curr_Line = getLine(src); /* get next line in file */
        line_counter++;
    }
}

void handleDataLine(char *str)
{
    char *trimmedLine;
    int curr_num;
    int i = 0;

    trimmedLine = trimAll(str);

    printf(".data: got line->%s<-\n", str);
    if (trimmedLine == NULL)
    {
        announceSyntaxError("no input after .data decleration.");
        return;
    }
    if (isOnlyWhiteChars(trimmedLine)) /*check for an empty line after .data*/
    {
        announceSyntaxError("no input after .data decleration.");
        printf("blat empty line\n");
        no_Errors = FALSE;
    }

    if (checkIntegerInText(trimmedLine) && no_Errors) /*check for first int*/
    {
        curr_num = getIntegerFromText(trimmedLine);
        if (!isIntInRange(curr_num))
        {
            announceSyntaxError("number is out of of range(16 bit max).");
            no_Errors = FALSE;
        }
        addToDataImage(curr_num);
        DC++;
        removeIntegerFromText(trimmedLine);
    }
    else
    {
        if (countCommas(trimmedLine) > 0)
            announceSyntaxError("missing first number before comma.");
        else
            announceSyntaxError("paramter is not a number.");
    }
    while (!isOnlyWhiteChars(trimmedLine) && no_Errors) /*now only get comma and then Integer*/
    {
        if (countCommas(trimmedLine) == 1)
        {
            removeComma(trimmedLine);
            if (checkIntegerInText(trimmedLine)) /*check get number*/
            {
                curr_num = getIntegerFromText(trimmedLine);
                if (!isIntInRange(curr_num))
                {
                    announceSyntaxError("number is out of of range(16 bit max).");

                    no_Errors = FALSE;
                }
                addToDataImage(curr_num);
                DC++;
                removeIntegerFromText(trimmedLine);
            }
            else
            {

                no_Errors = FALSE;
            }
        }
        else
        {
            if (countCommas(trimmedLine) == 0) /*if there are no commas but there is text*/
            {
                if (!isOnlyWhiteChars(trimmedLine))
                {
                    announceSyntaxError("multiple consecutive parameters.");
                    no_Errors = FALSE;
                }
            }
            else
            {
                announceSyntaxError("multiple consecutive commas.");
                no_Errors = FALSE;
            }
        }
    }
}

void handleStringLine(char *str)
{
    int i = 0;
    char *trimmedLine = trimAll(str);

    printf(".string: got line->%s<-\n", str);
    if (no_Errors)
    {
        if (trimmedLine[i] != QUOTATION_MARK)
        {
            announceSyntaxError("no quotes at start.");
        }
        else
        {
            for (i = 1; i < strlen(trimmedLine) - 1 && no_Errors; i++)
            {
                if (!isprint(trimmedLine[i]))
                {
                    announceSyntaxError("none printable characters.");
                }
                else
                {
                    if (trimmedLine[i] == QUOTATION_MARK)
                    {
                        announceSyntaxError("missing quotes in the end.");
                    }
                    else
                    {
                        addToDataImage(((int)trimmedLine[i]));
                        DC++;
                    }
                }
            }
            i++;
            if (no_Errors)
            {
                if (trimmedLine[i] != QUOTATION_MARK)
                {
                    announceSyntaxError("text should end with quotetion mark.");
                }
                else
                {
                    addToDataImage(END_OF_STRING); /*add null terminator in the end of string*/
                    DC++;
                }
            }
        }
    }
}

void handleExtern(char *name, char *line)
{
    char *temp = NULL;
    node *currLabel;
    if (name == NULL)
    {
        announceSyntaxError("missing label name after \".extern\" .");
    }
    else                            /*if there is a label name*/
    {                               /*check if name is good*/
        if (!isGoodLabelName(name)) /*in case of a bad label name*/
        {
            announceSyntaxError("bad label name.");
        }
        else
        {
            line = extractWordFromStart(line);
            temp = getTrimmedWordFromLine(line);
            if (temp != NULL) /*there should not be any other text after the name of the extern label*/
            {
                free(temp);
                announceSyntaxError("extraneous text at end of line.");
            }
            else
            {
                currLabel = findNode(label_Table, name);
                if (currLabel == NULL)
                {
                    storeLable(label_Table, name, TRUE, FALSE, UNDEFINED, 0, 0, 0);
                }
                else
                {
                    if (((Label *)currLabel->data)->_attrib_extern != TRUE) /*if the label is already defined as not extern*/
                    {
                        announceSyntaxError("label already exists and is not extern.");
                    }
                }
            }
        }
    }
}

void checkExternSyntax(char *name, char *line)
{
    int result = 1;
    char *temp = NULL;
    if (name == NULL)
    {
        announceSyntaxError("missing label name after \".extern\" .");
        result = 0;
    }
    else                            /*if there is a label name*/
    {                               /*check if name is good*/
        if (!isGoodLabelName(name)) /*in case of a bad label name*/
        {
            announceSyntaxError("bad label name.");
            result = 0;
        }
        else
        {
            line = extractWordFromStart(line);
            temp = getTrimmedWordFromLine(line);
            if (temp != NULL) /*there should not be any other text after the name of the extern label*/
            {
                free(temp);
                announceSyntaxError("extraneous text at end of line.");
                result = 0;
            }
        }
    }
    return result;
}

void checkEntrySyntax(char *name, char *line)
{
    int result = 1;
    char *temp = NULL;
    if (name == NULL)
    {
        announceSyntaxError("missing label name after \".entry\" .");
        result = 0;
    }
    else                            /*if there is a label name*/
    {                               /*check if name is good*/
        if (!isGoodLabelName(name)) /*in case of a bad label name*/
        {
            announceSyntaxError("bad label name.");
            result = 0;
        }
        else
        {
            line = extractWordFromStart(line);
            temp = getTrimmedWordFromLine(line);
            if (temp != NULL) /*there should not be any other text after the name of the extern label*/
            {
                free(temp);
                announceSyntaxError("extraneous text at end of line.");
                result = 0;
            }
        }
    }
    return result;
}

void handleEntry(char *name, char *line)
{
    char *temp;
    node *currLabel;
    if (name == NULL)
    {
        /*ERROR*/
        /*print error for MISSING LABEL NAME AT LINE ... */
    }
    else
    {
        if (!isGoodLabelName(name))
        {
            /*ERROR*/
            /*print error for ba label name at line...*/
        }
        else
        {
            line = extractWordFromStart(line);
            temp = getTrimmedWordFromLine(line);
            if (temp != NULL)
            {
                /*ERROR*/
                /* throw error for extra text after entry def ... */
            }
            else
            {
                currLabel = findNode(label_Table, name);
                if (currLabel == NULL)
                {
                    storeLable(label_Table, name, FALSE, TRUE, UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED);
                    /**/
                }
                else
                {
                    if (((Label *)currLabel->data)->_attrib_extern == TRUE) /*if already defined as extern then thats a problem*/
                    {
                        /*ERROR*/
                        /* throw error for entry label already defined and not as entry*/
                    }
                    else
                    {
                        ((Label *)currLabel->data)->_attrib_entry = TRUE;
                    }
                }
            }
        }
    }
}

/*ToDo dont forget to check if there are no errors and therefor */
void handleLabel(char *name, char *line)
{
    node *temp_label;
    Label *temp_Label_holder = NULL;

    char *trimmed_Line, *temp_string, *curr_word;

    name[strlen(name) - 1] = END_OF_STRING; /*remove : at the end of label name*/
    trimmed_Line = trimAll(line);
    if (!isGoodLabelName(name))
    {
        announceSyntaxError("Bad label name");
    }
    else
    {
        temp_string = extractWordFromStart(trimmed_Line);
        trimmed_Line = trimAll(temp_string);

        if (trimmed_Line == NULL || strlen(trimmed_Line) > 0) /*if its an empty line*/
        {
            temp_label = findNode(label_Table, name);
            if (temp_label != NULL)
            {
                if (temp_Label_holder->_attrib_extern != TRUE)
                {
                    temp_Label_holder = (Label *)temp_label->data;
                    temp_Label_holder->_value = IC;
                    temp_Label_holder->_base_address = calcBaseAddress(IC);
                    temp_Label_holder->_offset = calcOffsetAddress(IC);
                }
                else
                {
                    announceSyntaxError("label already defined as extern.");
                }
            }
            else
            {
                storeLable(label_Table, name, FALSE, UNDEFINED, INSTRUCTION, IC, calcBaseAddress(IC), calcOffsetAddress(IC));
            }
        }
        else
        {
            curr_word = getTrimmedWordFromLine(trimmed_Line);

            /*check syntax for entry and extern, there is no need to save label in this case*/
            if (isExternDefinition(curr_word) || isEntryDefinition(curr_word))
            {
                if (isEntryDefinition(curr_word))
                {
                    free(curr_word);
                    trimmed_Line = extractWordFromStart(trimmed_Line);
                    curr_word = getTrimmedWordFromLine(trimmed_Line);
                    checkExternSyntax(curr_word, trimmed_Line);
                }
                else
                {
                    if (isExternDefinition(curr_word))
                    {
                        free(curr_word);
                        trimmed_Line = extractWordFromStart(trimmed_Line);
                        curr_word = getTrimmedWordFromLine(trimmed_Line);
                        icheckExternSyntax(curr_word, trimmed_Line);
                    }
                }
            }
            else /*if not .entry or .extern*/
            {
                temp_label = findNode(label_Table, name); /*save label*/
                if (temp_label != NULL)
                {
                    /*if a label already exits it can only be entry and undefined*/
                    if (temp_Label_holder->_attrib_entry == TRUE && temp_Label_holder->_value == UNDEFINED)
                    {
                        temp_Label_holder = (Label *)temp_label->data;
                        temp_Label_holder->_value = IC;
                        temp_Label_holder->_base_address = calcBaseAddress(IC);
                        temp_Label_holder->_offset = calcOffsetAddress(IC);
                    }
                    else
                    {
                        announceSyntaxError("label already defined as extern.");
                    }
                }
                else
                { /*if its not already defined then create label*/
                    storeLable(label_Table, name, FALSE, UNDEFINED, INSTRUCTION, IC, calcBaseAddress(IC), calcOffsetAddress(IC));
                }

                if (isDataLabelDefinition(curr_word)) /*if its a .data line*/
                {
                    temp_label = findNode(label_Table, name); /*find and change type of label to DATA*/
                    ((Label *)(temp_label->data))->_label_type = DATA;

                    trimmed_Line = extractWordFromStart(trimmed_Line);
                    handleDataLine(trimmed_Line);
                }
                else
                {
                    if (isStringLabelDefinition(curr_word)) /*if its a .string line*/
                    {
                        temp_label = findNode(label_Table, name); /*find and change type of label to DATA*/
                        ((Label *)(temp_label->data))->_label_type = DATA;

                        trimmed_Line = extractWordFromStart(trimmed_Line);
                        handleStringLine(trimmed_Line);
                    }
                    else /*then it must be a command*/
                    {
                        handleCommand(trimmed_Line);
                    }
                }
            }
        }
    }
}

void handleCommand(char *str)
{
}
/*checks for syntax errors and if there are none then increment IC*/

/*ToDo store label*/
/*make macro for error output FIRST_PASS_ERROR*/

void addToDataImage(int num)
{
    Data_Image_Length++;
    Data_Image = realloc(Data_Image, Data_Image_Length);
    Data_Image[Data_Image_Length - 1] = num;
}

void announceSyntaxError(char *ERR)
{
    no_Errors = FALSE;
    printf("ERROR in line %d: %s\n", line_counter, ERR);
}
