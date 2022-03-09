#include "Assembler_Pass.h"

int assemblerFirstPass(FILE src)
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

    curr_Line = getline(src);
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
                    curr_Word = getTrimmedWordFromLine(curr_Line); /*get name*/

                    handleExtern(curr_Word, curr_Line);
                }
                else
                {
                    if (isEntryDefinition(curr_Word)) /*handle entry def*/
                    {
                        free(curr_Word);
                        curr_Line = extractWordFromStart(curr_Line);
                        curr_Word = getTrimmedWordFromLine(curr_Line); /*get name*/

                        handleEntry(curr_Word, curr_Line);
                    }
                    else
                    {
                        if (isDataLabelDefinition(curr_Word)) /*handle .data array*/
                        {
                            handleDataLine(curr_Line); /*ToDo*/
                        }
                        else
                        {
                            if (isStringLabelDefinition(curr_Word)) /*handle String array*/
                            {
                                handleStringLine(curr_Line); /*ToDo*/
                            }
                        }
                    }
                }
            }
            else /*if just an instruction or label and data/string*/
            {
                if (isLabelDefinition(curr_Word))
                {
                    handleLabel(curr_Word, curr_Line); /*handles options for .data .string .entry .extern and posddible command*/
                }
                else
                {
                    handleCommand(curr_Line); /* adds command length to IC*/
                }
                /*handle insruction*/
            }
        }
        if (curr_Line != NULL)
            free(curr_Line);
        curr_Line = getline(src); /* get next line in file */
        line_counter++;
    }
}

/*TODO ass the function protoypes to the header*/

void handleDataLine(char *str) /*ToDo*/
{
    int curr_num;
    int i = 0;
    char *curr_num_string = NULL;
    char *trimmedLine = trimAll(line);

    printf(".data: got line->%s<-\n", str);
    if (trimmedLine == NULL)
    {
        /*ERROR no values to insert*/
        return;
    }

    if (no_Errors && strlen(trimmedLine) > 0)
    {
        curr_num_string = (char *)malloc(1);
        curr_num_string[0] = END_OF_STRING;
        while (no_Errors && strlen(trimmedLine) > 0)
        {
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
            /*ERROR  no quots at start*/
        }
        else
        {
            for (i = 1; i < strlen(trimmedLine) - 1 && no_Errors; i++)
            {
                if (!isprint(trimmedLine[i]))
                {
                    /*Error non printable character*/
                }
                else
                {
                    if (trimmedLine[i] == QUOTATION_MARK)
                    {
                        /*ERROR no quots at end*/
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
                    /*ERROR text should end with  qoutation mark*/
                }
                else
                {
                    addToDataImage(END_OF_STRING); /*add string in the end of stuff*/
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
        /*ERROR*/
        /*print error for MISSING LABEL NAME AT LINE ... */
    }
    else                            /*if there is a label name*/
    {                               /*check if name is good*/
        if (!isGoodLabelName(name)) /*in case of a bad label name*/
        {
            /*ERROR*/
            /*print error for bad label name for extern label in line ... */
        }
        else
        {
            line = extractWordFromStart(line);
            temp = getTrimmedWordFromLine(line);
            if (temp != NULL) /*there should not be any other text after the name of the extern label*/
            {
                free(temp);
                /*ERROR*/
                /* throw error for extra text after extern def ... */
            }
            else
            {
                currLabel = findNode(label_Table, name);
                if (currLabel == NULL)
                {
                    currLabel = LabelConstructor(curr_Word, TRUE, FALSE, UNDEFINED, 0, 0, 0);
                    /*store label in label table*/
                    /*change command to store label istead of constructing a new one*/
                }
                else
                {
                    if (((Label *)currLabel->data)->_attrib_extern != TRUE) /*if the label is already defined as not extern*/
                    {
                        /*ERROR*/
                        /* throw error for ext label already defined and not as external*/
                    }
                }
            }
        }
    }
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
                    LabelConstructor(name, FALSE, TRUE, UNDEFINED, 0, 0, 0);
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

/*ToDo dont forget ot chekc if ther are no errors and therefor */
void handleLabel(char *name, char *line) {}

void handleCommand(char *str)
{
}
/*checks for syntax errors and if there are none then increment IC*/

/*void getStringArray(char *str);*/
/*ToDo store label*/
/*make macro for error output FIRST_PASS_ERROR*/

void addToDataImage(int num)
{
    Data_Image_Length++;
    Data_Image = realloc(Data_Image, Data_Image_Length);
    Data_Image[Data_Image_Length - 1] = num;
}