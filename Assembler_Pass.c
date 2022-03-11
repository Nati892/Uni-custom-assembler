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
    char *curr_Line, *curr_Word;
    label_Table = initList();
    fseek(src, 0, SEEK_SET); /*set file read point to start*/
    line_counter = 1;        /*line count starts at 1*/
    no_Errors = 1;
    DC = 0;
    IC = 100;
    Data_Image = (int *)malloc(1 * sizeof(int));
    Data_Image_Length = 0;

    curr_Line = getLine(src);
    printf("Line->%s<-\n", curr_Line);
    while (curr_Line != NULL) /*loop through the lines*/
    {
        printf("Line->%s<-\n", curr_Line);
        if (!isCommentLine(curr_Line) && !isOnlyWhiteChars(curr_Line)) /*if its a comment then Ignore the line*/
        {
            /*ToDo add check for line length*/

            curr_Word = getTrimmedWordFromLine(curr_Line);
            if (isEntryDefinition(curr_Word) || isExternDefinition(curr_Word) || isDataLabelDefinition(curr_Word) || isStringLabelDefinition(curr_Word))
            {
                /*handle special lables, no instructions handling needed here*/
                if (isExternDefinition(curr_Word)) /*handle Extern def */
                {
                    printf("ITS extern!\n");
                    free(curr_Word);
                    curr_Line = extractWordFromStart(curr_Line);
                    curr_Word = getTrimmedWordFromLine(curr_Line); /*get name of label*/

                    handleExtern(curr_Word, curr_Line);
                    printf("done extern\n");
                }
                else
                {
                    if (isEntryDefinition(curr_Word)) /*handle entry def*/
                    {
                        printf("ITS entry!\n");
                        free(curr_Word);
                        curr_Line = extractWordFromStart(curr_Line);
                        curr_Word = getTrimmedWordFromLine(curr_Line); /*get name of label*/

                        handleEntry(curr_Word, curr_Line);
                    }
                    else
                    {
                        if (isDataLabelDefinition(curr_Word)) /*handle .data array*/
                        {
                            printf("ITS data!\n");
                            free(curr_Word);
                            curr_Line = extractWordFromStart(curr_Line);
                            handleDataLine(curr_Line); /*ToDo*/
                            free(curr_Word);
                        }
                        else
                        {
                            if (isStringLabelDefinition(curr_Word)) /*handle String array*/
                            {
                                printf("ITS string!\n");
                                free(curr_Word);
                                curr_Line = extractWordFromStart(curr_Line);
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
                    printf("ITS label!\n");
                    handleLabel(curr_Word, curr_Line); /*handles options for .data .string .entry .extern and possible command*/
                }
                else
                {
                    free(curr_Word);
                    printf("ITS command!\n");
                    handleCommand(curr_Line); /* adds command length to IC*/
                }

                /*handle insruction*/
            }
        }
        else
        {
            if (curr_Line != NULL)
                free(curr_Line);
        }

        curr_Line = getLine(src); /* get next line in file */
        line_counter++;
    }
}

void handleDataLine(char *str)
{
    int is_good_data = TRUE;
    char *trimmedLine;
    int curr_num;

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
        is_good_data = FALSE;
    }

    if (checkIntegerInText(trimmedLine) && is_good_data) /*check for first int*/
    {
        curr_num = getIntegerFromText(trimmedLine);
        if (!isIntInRange(curr_num))
        {
            announceSyntaxError("number is out of of range(16 bit max).");
            is_good_data = FALSE;
        }
        addToDataImage(curr_num);
        DC++;
        removeIntegerFromText(trimmedLine);
    }
    else
    {
        if (countCommas(trimmedLine) > 0)
        {
            announceSyntaxError("missing first number before comma.");
            is_good_data = FALSE;
        }

        else
        {
            announceSyntaxError("paramter is not a number.");
            is_good_data = FALSE;
        }
    }
    while (!isOnlyWhiteChars(trimmedLine) && is_good_data) /*now only get comma and then Integer*/
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

                    is_good_data = FALSE;
                }
                addToDataImage(curr_num);
                DC++;
                removeIntegerFromText(trimmedLine);
            }
            else
            {

                is_good_data = FALSE;
            }
        }
        else
        {
            if (countCommas(trimmedLine) == 0) /*if there are no commas but there is text*/
            {
                if (!isOnlyWhiteChars(trimmedLine))
                {
                    announceSyntaxError("multiple consecutive parameters.");
                }
            }
            else
            {
                announceSyntaxError("multiple consecutive commas.");
            }
        }
    }
}

void handleStringLine(char *str)
{
    int is_good_string = TRUE;
    int i = 0;
    char *trimmedLine = trimAll(str);

    printf(".string: got line->%s<-\n", str);
    if (trimmedLine[i] != QUOTATION_MARK)
    {
        announceSyntaxError("no quotes at start.");
        is_good_string = FALSE;
    }
    else
    {
        for (i = 1; i < strlen(trimmedLine) - 1 && is_good_string; i++)
        {
            if (!isprint(trimmedLine[i]))
            {
                announceSyntaxError("none printable characters.");
                is_good_string = FALSE;
            }
            else
            {
                if (trimmedLine[i] == QUOTATION_MARK)
                {
                    announceSyntaxError("missing quotes in the end.");
                    is_good_string = FALSE;
                }
                else
                {
                    addToDataImage(((int)trimmedLine[i]));
                    DC++;
                }
            }
        }
        if (is_good_string)
        {
            if (trimmedLine[i] != QUOTATION_MARK)
            {
                announceSyntaxError("text should end with quotetion mark.");
            }
            else
            {
                addToDataImage(((int)END_OF_STRING)); /*add null terminator in the end of string*/
                DC++;
            }
        }
    }
}

void handleExtern(char *name, char *line)
{
    char *temp = NULL;
    node *currLabel;
    printf("handleExtern name:->%s<-, line->%s<-\n", name, line);
    if (name == NULL)
    {
        announceSyntaxError("missing label name after \".extern\" .");
    }
    else                            /*if there is a label name*/
    {                               /*check if name is good*/
        if (!isGoodLabelName(name)) /*in case of a bad label name*/
        {
            announceSyntaxError("bad label name.");
            free(name);
        }
        else
        {
            line = extractWordFromStart(line);
            temp = getTrimmedWordFromLine(line);
            if (temp != NULL) /*there should not be any other text after the name of the extern label*/
            {
                free(temp);
                announceSyntaxError("extraneous text at end of line.");
                free(name);
            }
            else
            {
                currLabel = findNode(label_Table, name);
                if (currLabel == NULL)
                {
                    storeLable(label_Table, name, TRUE, FALSE, UNDEF, 0, 0, 0);
                }
                else
                {
                    if (((Label *)currLabel->data)->_attrib_extern != TRUE) /*if the label is already defined as not extern*/
                    {
                        announceSyntaxError("label already exists and is not extern.");
                        free(name);
                    }
                }
            }
        }
    }
    printf("done function\n");
}

void checkExternSyntax(char *name, char *line)
{

    char *temp = NULL;
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
        }
    }
}

void checkEntrySyntax(char *name, char *line)
{
    char *temp = NULL;
    if (name == NULL)
    {
        announceSyntaxError("missing label name after \".entry\" .");
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
        }
    }
}

void handleEntry(char *name, char *line)
{
    char *temp;
    node *currLabel;
    if (name == NULL)
    {
        announceSyntaxError("missing name for label");
    }
    else
    {
        if (!isGoodLabelName(name))
        {
            announceSyntaxError("bad label name");
            free(name);
        }
        else
        {
            line = extractWordFromStart(line);
            temp = getTrimmedWordFromLine(line);
            if (temp != NULL)
            {
                announceSyntaxError("extraneous text at end of line");
                free(name);
            }
            else
            {
                currLabel = findNode(label_Table, name);
                if (currLabel == NULL)
                {
                    storeLable(label_Table, name, FALSE, TRUE, UNDEF, UNDEF, UNDEF, UNDEF);
                    /**/
                }
                else
                {
                    if (((Label *)currLabel->data)->_attrib_extern == TRUE) /*if already defined as extern then thats a problem*/
                    {
                        announceSyntaxError("label already defined and as extern.");
                        free(name);
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

void handleLabel(char *name, char *line)
{
    node *temp_label;
    Label *temp_Label_holder = NULL;

    char *trimmed_Line, *temp_string, *curr_word;
    printf("handlelabel name:->%s<-, line->%s<-\n", name, line);
    name[strlen(name) - 1] = END_OF_STRING; /*remove ':' at the end of label name*/
    trimmed_Line = trimAll(line);
    if (!isGoodLabelName(name))
    {
        announceSyntaxError("Bad label name");
    }
    else
    {

        temp_string = extractWordFromStart(trimmed_Line);
        if (!isOnlyWhiteChars(temp_string))
            trimmed_Line = trimAll(temp_string);
        free(temp_string);

        if (trimmed_Line == NULL || strlen(trimmed_Line) == 0) /*if its an empty line*/
        {
            temp_label = findNode(label_Table, name);
            if (temp_label != NULL)
            {
                printf("label %s already exists\n", name);
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
                printf("saving labellll %s\n", name);
                storeLable(label_Table, name, FALSE, UNDEF, INSTRUCTION, IC, calcBaseAddress(IC), calcOffsetAddress(IC));
            }
        }
        else
        {
            curr_word = getTrimmedWordFromLine(trimmed_Line);
            printf("word after label def is ->%s<-\n", curr_word);
            /*check syntax for entry and extern, there is no need to save label in this case*/
            if (isExternDefinition(curr_word) || isEntryDefinition(curr_word))
            {
                if (isEntryDefinition(curr_word))
                {
                    printf("its entry def\n");
                    free(curr_word);
                    trimmed_Line = extractWordFromStart(trimmed_Line);
                    curr_word = getTrimmedWordFromLine(trimmed_Line);
                    checkExternSyntax(curr_word, trimmed_Line);
                }
                else
                {
                    if (isExternDefinition(curr_word))
                    {
                        printf("its extern def\n");
                        free(curr_word);
                        trimmed_Line = extractWordFromStart(trimmed_Line);
                        curr_word = getTrimmedWordFromLine(trimmed_Line);
                        checkExternSyntax(curr_word, trimmed_Line);
                    }
                }
            }
            else /*if not .entry or .extern*/
            {
                printf("got to second save section with %s\n", name);
                temp_label = findNode(label_Table, name); /*save label*/

                if (temp_label != NULL)
                {
                    temp_Label_holder = (Label *)temp_label->data;

                    /*if a label already exits it can only be entry and UNDEF*/
                    if (temp_Label_holder->_attrib_entry == TRUE && temp_Label_holder->_value == UNDEF)
                    {
                        temp_Label_holder = (Label *)temp_label->data;
                        temp_Label_holder->_value = IC;
                        temp_Label_holder->_base_address = calcBaseAddress(IC);
                        temp_Label_holder->_offset = calcOffsetAddress(IC);
                    }
                    else
                    {
                        announceSyntaxError("label name already used.");
                    }
                }
                else
                { /*if its not already defined then create label*/
                    storeLable(label_Table, name, FALSE, UNDEF, INSTRUCTION, UNDEF, UNDEF, UNDEF);
                    printf("saved %s\n", name);
                }

                if (isDataLabelDefinition(curr_word)) /*if its a .data line*/
                {
                    printf("its .data def\n");
                    temp_label = findNode(label_Table, name); /*find and change type of label to DATA*/
                    ((Label *)(temp_label->data))->_label_type = DATA;
                    ((Label *)(temp_label->data))->_value = DC; /*the base and offset will be calcualted in the start of the second pass*/

                    trimmed_Line = extractWordFromStart(trimmed_Line);
                    handleDataLine(trimmed_Line);
                }
                else
                {
                    if (isStringLabelDefinition(curr_word)) /*if its a .string line*/
                    {
                        temp_label = findNode(label_Table, name); /*find and change type of label to DATA*/
                        ((Label *)(temp_label->data))->_label_type = DATA;
                        ((Label *)(temp_label->data))->_value = DC; /*the base and offset will be calcualted in the start of the second pass*/

                        trimmed_Line = extractWordFromStart(trimmed_Line);
                        handleStringLine(trimmed_Line);
                    }
                    else /*then it must be a command*/
                    {
                        temp_label = findNode(label_Table, name); /*find and change type of label to DATA*/
                        ((Label *)(temp_label->data))->_label_type = DATA;
                        ((Label *)(temp_label->data))->_value = IC;
                        ((Label *)(temp_label->data))->_base_address = calcBaseAddress(IC);
                        ((Label *)(temp_label->data))->_offset = calcOffsetAddress(IC);
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

void addToDataImage(int num)
{
    Data_Image_Length++;
    Data_Image = realloc(Data_Image, Data_Image_Length * sizeof(int));
    Data_Image[Data_Image_Length - 1] = num;
}

void announceSyntaxError(char *ERR)
{
    no_Errors = FALSE;
    printf("ERROR in line %d: %s\n", line_counter, ERR);
}

void debugAsm()
{
    int i = 0;
    printf("\n\n\n********************\n *********\ndebug\n");
    printf("no errors: %d\n", no_Errors);
    printf("DC: %d\n", DC);
    printf("IC: %d\n", IC);
    printf("line counter: %d\n", line_counter - 1);
    for (i = 0; i < Data_Image_Length; i++)
        printf("value in cell %d -> %d\n", i, Data_Image[i]);
    printf("Data_Image_Length: %d\n", Data_Image_Length);
    printf("printing label table\n\n\n");
    printLables(label_Table);
}
