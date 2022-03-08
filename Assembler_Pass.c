#include "Assembler_Pass.h"

int assemblerFirstPass(FILE src)
{
    /*setting up some normal and static variables, and setting file pointer to start.
    In the first pass there is no need to write to the instruction image, only to understand how long is each instruction,
    for label usage, in the second pass the instructions will be translated.
    The data image will be filled in the first pass;*/
    char *curr_Line, *temp, *curr_Word;
    node *currLabel;
    label_Table = initList();
    fseek(src, 0, SEEK_SET); /*set file read point to start*/
    line_counter = 1;        /*line count starts at 1*/
    no_Errors = 1;
    DC = 0;
    IC = 100;
    Data_Image = (char *)malloc(1);
    Data_Image[0] = END_OF_STRING;

    curr_Line = getline(src);
    while (curr_Line != NULL) /*loop through the lines*/
    {
        if (!isCommentLine(curr_Line) && !isOnlyWhiteChars(curr_Line)) /*if its a comment then Ignore the line*/
        {
            curr_Word = getWordFromLine(curr_Line);
            if (isEntryDefinition(curr_Word) || isExternDefinition(curr_Word) || isDataLabelDefinition(curr_Word) || isStringLabelDefinition(curr_Word))
            {
                /*handle special lables, no instructions handling needed here*/
                if (isExternDefinition(curr_Word)) /*handle Extern def */
                {
                    free(curr_Word);
                    curr_Line = extractWordFromStart(curr_Line);
                    curr_Word = getTrimmedWordFromLine(curr_Line); /*get name*/
                    if (curr_Word == NULL)
                    {
                        /*ERROR*/
                        /*print error for MISSING LABEL NAME AT LINE ... */
                    }
                }
                else                                 /*if there is a label name*/
                {                                    /*check if name is good*/
                    if (!isGoodLabelName(curr_Word)) /*in case of a bad label name*/
                    {
                        /*ERROR*/
                        /*print error for bad label name for extern label in line ... */
                    }
                    else
                    {
                        curr_Line = extractWordFromStart(curr_Line);
                        temp = getTrimmedWordFromLine(curr_Line);
                        if (temp != NULL)
                        {
                            /*ERROR*/
                            /* throw error for extra text after extern def ... */
                        }
                        else
                        {
                            currLabel = findNode(label_Table, curr_Word);
                            if (currLabel == NULL)
                            {
                                LabelConstructor(curr_Word, TRUE, FALSE, UNDEFINED, 0, 0, 0);
                            }
                            else
                            {
                                if (((Label *)currLabel->data)->_attrib_extern != TRUE)
                                {
                                    /*ERROR*/
                                    /* throw error for ext label already defined and not as external*/
                                }
                            }
                        }
                        free(temp);
                    }
                }
            }
            else
            {
                if (isEntryDefinition(curr_Word)) /*handle entry def*/
                {
                    free(curr_Word);
                    curr_Line = extractWordFromStart(curr_Line);
                    curr_Word = getTrimmedWordFromLine(curr_Line); /*get name*/
                    if (curr_Word == NULL)
                    {
                        /*ERROR*/
                        /*print error for MISSING LABEL NAME AT LINE ... */
                    }
                    else
                    {
                        if (!isGoodLabelName(curr_Word))
                        {
                            /*ERROR*/
                            /*print error for ba label name at line...*/
                        }
                        else
                        {
                            curr_Line = extractWordFromStart(curr_Line);
                            temp = getTrimmedWordFromLine(curr_Line);
                            if (temp != NULL)
                            {
                                /*ERROR*/
                                /* throw error for extra text after entry def ... */
                            }
                            else
                            {
                                currLabel = findNode(label_Table, curr_Word);
                                if (currLabel == NULL)
                                {
                                    LabelConstructor(curr_Word, FALSE, TRUE, UNDEFINED, 0, 0, 0);
                                }
                                else
                                {
                                    if (((Label *)currLabel->data)->_attrib_entry != TRUE)
                                    {
                                        /*ERROR*/
                                        /* throw error for entry label already defined and not as entry*/
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (isDataLabelDefinition(curr_Word)) /*handle .data array*/
                    {
                    }
                    else
                    {
                        isStringLabelDefinition(curr_Word) /*handle String array*/
                    }
                }
            }
        }
        else /*if just an instruction or label and data/string*/
        {
            if (isLabelDefinition)
            { /*save label*/
            }
            else
            {
            }
            /*handle istruction*/
        }
    }
    free(curr_Line);
    curr_Line = getline(src); /*get next line in file*/
    line_counter++;
}
}

void handleDataLine(char *str)
{


}

void handleStringLine(char *str)
{
}

/*void getStringArray(char *str);*/