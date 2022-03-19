#include "Assembler_Pass.h"

/*
    In the first pass there is no need to write to the instruction image,
     Only to understand how many lines does each instruction takes, so that IC will be correct all the way.
     In the first pass all errors are handled, so the second pass only starts if there are no errors in code.
     In the second pass the instructions will be translated.
    The data image will be filled in the first pass.
    And all the labels will be collected*/

/*this function is the first pass where all label data is collected,
all .data/.string array data is collected
 and all the errors are handled*/
void assemblerFirstPass(FILE *src, Assembler_mem *mem)
{

    char *curr_Line, *curr_Word;

    fseek(src, 0, SEEK_SET); /*set file read point to start*/
    curr_Line = getLine(src);
    while (curr_Line != NULL) /*loop through the lines*/
    {
        if (!isCommentLine(curr_Line) && !isOnlyWhiteChars(curr_Line)) /*if its a comment then Ignore the line*/
        {
            if (strlen(curr_Line) > MAX_Line_LENGTH)
                announceSyntaxError("Line is too long! max length is 80 characters.", mem);

            curr_Word = getTrimmedWordFromLine(curr_Line);

            if (isEntryDefinition(curr_Word) || isExternDefinition(curr_Word) || isDataLabelDefinition(curr_Word) || isStringLabelDefinition(curr_Word))
            {
                /*handle special lables, no instructions handling needed here*/
                if (isExternDefinition(curr_Word)) /*handle Extern def */
                {
                    free(curr_Word);
                    curr_Line = extractWordFromStart(curr_Line);
                    curr_Word = getTrimmedWordFromLine(curr_Line); /*get name of label*/

                    handleExtern(curr_Word, curr_Line, mem);
                }
                else
                {
                    if (isEntryDefinition(curr_Word)) /*handle entry def*/
                    {
                        free(curr_Word);
                        curr_Line = extractWordFromStart(curr_Line);
                        curr_Word = getTrimmedWordFromLine(curr_Line); /*get name of label*/

                        handleEntry(curr_Word, curr_Line, mem);
                    }
                    else
                    {
                        if (isDataLabelDefinition(curr_Word)) /*handle .data array*/
                        {
                            free(curr_Word);
                            curr_Line = extractWordFromStart(curr_Line);
                            handleDataLine(curr_Line, mem);
                            free(curr_Word);
                        }
                        else
                        {
                            if (isStringLabelDefinition(curr_Word)) /*handle .string array*/
                            {
                                free(curr_Word);
                                curr_Line = extractWordFromStart(curr_Line);
                                handleStringLine(curr_Line, mem);
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
                    handleLabel(curr_Word, curr_Line, mem); /*handles options for .data .string .entry .extern and possible command*/
                }
                else
                {

                    free(curr_Word);
                    handleCommand(curr_Line, mem); /* adds command length to mem->IC*/
                }
            }
        }
        else
        {
            if (curr_Line != NULL)
                free(curr_Line);
        }

        curr_Line = getLine(src); /* get next line in file */
        mem->line_counter++;
    }

    if ((mem->IC + mem->Data_Image_Length) > MAX_PROGRAM_LENGTH) /*handle possible error for a too long program*/
        announceSyntaxError("program two long, max legnth is 8092 lines!", mem);

    checkEntryLables(mem);  /*make sure there arent any entry lables that are not defined*/
    checkUnusedLabels(mem); /*make sure there arent any labels used that don't exist */

    if (mem->no_Errors)
    {
        /*set correct values for labels*/
        reCalcLabels(mem);
    }
}

/*the second pass is called knowing there arent any errors.
it translate each command*/
void assemblerSecondPass(FILE *src, Assembler_mem *mem)
{
    char *curr_Line, *curr_Word;
    fseek(src, 0, SEEK_SET); /*set file read point to start*/
    mem->line_counter = 0;
    mem->IC = 100;

    curr_Line = getLine(src);
    while (curr_Line != NULL) /*loop through the lines*/
    {
        if (!isCommentLine(curr_Line) && !isOnlyWhiteChars(curr_Line)) /*if its a comment then Ignore the line*/
        {
            curr_Word = getTrimmedWordFromLine(curr_Line);

            if (isLabelDefinition(curr_Word)) /*if its label then remove the label from line and keep going*/
            {
                free(curr_Word);
                curr_Line = extractWordFromStart(curr_Line);
                curr_Word = getTrimmedWordFromLine(curr_Line);
            } /*if its instruction then translate it*/
            if (isInstructionName(curr_Word) != FALSE)
                SpreadCommand(curr_Line, mem); /* adds command length to mem->IC*/

            if (curr_Word != NULL)
            {
                free(curr_Word);
                curr_Word = NULL;
            }
        }
        if (curr_Line != NULL)
            free(curr_Line);

        curr_Line = getLine(src);
        mem->line_counter++;
    }
    translateDataImage(mem); /*add the data image at the end of the String image which holds the instructions*/
}

void finalStage(Assembler_mem *mem) /*translate binary to special format and build files*/
{

    createObFile(mem);
    createEntFile(mem);
    createExtFile(mem);
}

void createExtFile(Assembler_mem *mem)
{
    FILE *EXT_FILE;
    node *ext_List;
    /*create and fill the ext file*/
    EXT_FILE = CreateFileWithEnding(mem->file_name, FILE_ENDING_EXT);
    fseek(EXT_FILE, 0, SEEK_SET);
    ext_List = mem->ext_file_table;
    while (ext_List != NULL)
    {
        if (ext_List->key != NULL)
        {
            fprintf(EXT_FILE, "%s BASE %04d\n", ext_List->key, *((int *)ext_List->data));
            fprintf(EXT_FILE, "%s OFFSET %04d\n\n", ext_List->key, *((int *)ext_List->data) + 1);
        }
        ext_List = ext_List->next;
    }
}
void createEntFile(Assembler_mem *mem)
{
    FILE *ENT_FILE;
    node *ent_List;
    Label *temp_label;
    /*create and fill the ext file*/
    ENT_FILE = CreateFileWithEnding(mem->file_name, FILE_ENDING_ENT);
    fseek(ENT_FILE, 0, SEEK_SET);
    ent_List = mem->label_Table;
    while (ent_List != NULL)/*loop through eall labels*/
    {
        if (ent_List->key != NULL)
        {
            temp_label = (Label *)ent_List->data;
            if (temp_label->_attrib_entry == TRUE)/*only output entry labels*/
            {
                fprintf(ENT_FILE, "%s,%04d,%04d\n", ent_List->key, temp_label->_base_address, temp_label->_offset);
            }
        }
        ent_List = ent_List->next;
    }
}
void createObFile(Assembler_mem *mem)
{
    int lineCounter = 100;
    char *startOfRow;
    FILE *OB_FILE;
    /*create and fill the .ob file*/
    if (mem->IC == 100)
        mem->IC++;
    OB_FILE = CreateFileWithEnding(mem->file_name, FILE_ENDING_OB);
    fseek(OB_FILE, 0, SEEK_SET);
    fprintf(OB_FILE, "%d %d\n", mem->IC - 101, mem->Data_Image_Length); /*write the first line with size data*/
    while (lineCounter < (mem->IC + mem->Data_Image_Length - 1))
    {
        startOfRow = (mem->String_Image + (lineCounter - 100) * 21);
        fprintf(OB_FILE, "%04d A%x-B%x-C%x-D%x-E%x\n", lineCounter, binStringToInt(startOfRow), binStringToInt(startOfRow + 4), binStringToInt(startOfRow + 8), binStringToInt(startOfRow + 12), binStringToInt(startOfRow + 16));
        lineCounter++;
    }
    fclose(OB_FILE);
}

/*handles .data line*/
void handleDataLine(char *str, Assembler_mem *mem)
{
    int is_good_data = TRUE;
    char *trimmedLine;
    int curr_num;

    trimmedLine = trimAll(str);

    if (trimmedLine == NULL)
    {
        announceSyntaxError("no input after .data decleration.", mem);
        return;
    }
    if (isOnlyWhiteChars(trimmedLine)) /*check for an empty line after .data*/
    {
        announceSyntaxError("no input after .data decleration.", mem);
        is_good_data = FALSE;
    }

    if (checkIntegerInText(trimmedLine) && is_good_data) /*check for first int*/
    {
        curr_num = getIntegerFromText(trimmedLine);
        if (!isIntInRange(curr_num))
        {
            announceSyntaxError("number is out of of range(16 bit max).", mem);
            is_good_data = FALSE;
        }
        addToDataImage(curr_num, mem);
        mem->DC++;
        removeIntegerFromText(trimmedLine);
    }
    else
    {
        if (countCommas(trimmedLine) > 0)
        {
            announceSyntaxError("missing first number before comma.", mem);
            is_good_data = FALSE;
        }

        else
        {
            announceSyntaxError("paramter is not a number.", mem);
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
                    announceSyntaxError("number is out of of range(16 bit max).", mem);

                    is_good_data = FALSE;
                }
                addToDataImage(curr_num, mem);
                mem->DC++;
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
                    announceSyntaxError("multiple consecutive parameters.", mem);
                }
            }
            else
            {
                announceSyntaxError("multiple consecutive commas.", mem);
            }
        }
    }
}

/*handles .string line*/
void handleStringLine(char *str, Assembler_mem *mem)
{
    int is_good_string = TRUE;
    int i = 0;
    char *trimmedLine = trimAll(str);

    if (trimmedLine[i] != QUOTATION_MARK)
    {
        announceSyntaxError("no quotes at start.", mem);
        is_good_string = FALSE;
    }
    else
    {
        for (i = 1; i < strlen(trimmedLine) - 1 && is_good_string; i++)
        {
            if (!isprint(trimmedLine[i]))
            {
                announceSyntaxError("none printable characters.", mem);
                is_good_string = FALSE;
            }
            else
            {
                if (trimmedLine[i] == QUOTATION_MARK)
                {
                    announceSyntaxError("missing quotes in the end.", mem);
                    is_good_string = FALSE;
                }
                else
                {
                    addToDataImage(((int)trimmedLine[i]), mem);
                    mem->DC++;
                }
            }
        }
        if (is_good_string)
        {
            if (trimmedLine[i] != QUOTATION_MARK)
            {
                announceSyntaxError("text should end with quotetion mark.", mem);
            }
            else
            {
                addToDataImage(((int)END_OF_STRING), mem); /*add null terminator in the end of string*/
                mem->DC++;
            }
        }
    }
}

/*handles .extern line*/
void handleExtern(char *name, char *line, Assembler_mem *mem)
{
    char *temp = NULL;
    node *currLabel;
    if (name == NULL)
    {
        announceSyntaxError("missing label name after \".extern\" .", mem);
    }
    else                            /*if there is a label name*/
    {                               /*check if name is good*/
        if (!isGoodLabelName(name)) /*in case of a bad label name*/
        {
            announceSyntaxError("bad label name.", mem);
            free(name);
        }
        else
        {
            line = extractWordFromStart(line);
            temp = getTrimmedWordFromLine(line);
            if (temp != NULL) /*there should not be any other text after the name of the extern label*/
            {
                free(temp);
                announceSyntaxError("extraneous text at end of line.", mem);
                free(name);
            }
            else
            {
                currLabel = findNode(mem->label_Table, name);
                if (currLabel == NULL)
                {
                    storeLable(mem->label_Table, name, TRUE, FALSE, UNDEF, 0, 0, 0);
                }
                else
                {
                    if (((Label *)currLabel->data)->_attrib_extern != TRUE) /*if the label is already defined as not extern*/
                    {
                        announceSyntaxError("label already exists and is not extern.", mem);
                        free(name);
                    }
                }
            }
        }
    }
}

/*handles .entry line*/
void handleEntry(char *name, char *line, Assembler_mem *mem)
{
    char *temp;
    node *currLabel;
    if (name == NULL)
    {
        announceSyntaxError("missing name for label", mem);
    }
    else
    {
        if (!isGoodLabelName(name))
        {
            announceSyntaxError("bad label name", mem);
            free(name);
        }
        else
        {
            line = extractWordFromStart(line);
            temp = getTrimmedWordFromLine(line);
            if (temp != NULL)
            {
                announceSyntaxError("extraneous text at end of line", mem);
                free(name);
            }
            else
            {
                currLabel = findNode(mem->label_Table, name);
                if (currLabel == NULL) /*if doesnt exist yet then create*/
                {
                    storeLable(mem->label_Table, name, FALSE, TRUE, UNDEF, mem->line_counter, UNDEF, UNDEF);
                    /*save line num for error checking in the end*/
                }
                else
                {
                    if (((Label *)currLabel->data)->_attrib_extern == TRUE) /*if already defined as extern then thats a problem*/
                    {
                        announceSyntaxError("label already defined and as extern.", mem);
                        free(name);
                    }
                    else
                    { /*if exists then update to .entry*/
                        ((Label *)currLabel->data)->_attrib_entry = TRUE;
                    }
                }
            }
        }
    }
}

/*handle .extern that is in some line*/
void checkExternSyntax(char *name, char *line, Assembler_mem *mem)
{

    char *temp = NULL;
    if (name == NULL)
    {
        announceSyntaxError("missing label name after \".extern\" .", mem);
    }
    else                            /*if there is a label name*/
    {                               /*check if name is good*/
        if (!isGoodLabelName(name)) /*in case of a bad label name*/
        {
            announceSyntaxError("bad label name.", mem);
        }
        else
        {
            line = extractWordFromStart(line);
            temp = getTrimmedWordFromLine(line);
            if (temp != NULL) /*there should not be any other text after the name of the extern label*/
            {
                free(temp);
                announceSyntaxError("extraneous text at end of line.", mem);
            }
        }
    }
}

/*handle .entry that is in some line*/
void checkEntrySyntax(char *name, char *line, Assembler_mem *mem)
{
    char *temp = NULL;
    if (name == NULL)
    {
        announceSyntaxError("missing label name after \".entry\" .", mem);
    }
    else                            /*if there is a label name*/
    {                               /*check if name is good*/
        if (!isGoodLabelName(name)) /*in case of a bad label name*/
        {
            announceSyntaxError("bad label name.", mem);
        }
        else
        {
            line = extractWordFromStart(line);
            temp = getTrimmedWordFromLine(line);
            if (temp != NULL) /*there should not be any other text after the name of the extern label*/
            {
                free(temp);
                announceSyntaxError("extraneous text at end of line.", mem);
            }
        }
    }
}

/*handle label line*/
void handleLabel(char *name, char *line, Assembler_mem *mem)
{
    node *temp_label;
    Label *temp_Label_holder = NULL;
    char *trimmed_Line, *temp_string, *curr_word;

    name[strlen(name) - 1] = END_OF_STRING; /*remove ':' at the end of label name*/
    trimmed_Line = trimAll(line);

    if (!isGoodLabelName(name)) /*check for correct label name*/
    {
        announceSyntaxError("Bad label name", mem);
    }
    else
    {

        temp_string = extractWordFromStart(trimmed_Line); /*get first word from line in temp string*/

        if (!isOnlyWhiteChars(temp_string))
        {
            trimmed_Line = trimAll(temp_string);
        }

        free(temp_string);
        temp_string = NULL;

        if (trimmed_Line == NULL || strlen(trimmed_Line) == 0) /*if its an empty line,then save label*/
        {
            temp_label = findNode(mem->label_Table, name);
            if (temp_label != NULL)
            {
                if (temp_Label_holder->_attrib_extern != TRUE)
                {
                    temp_Label_holder = (Label *)temp_label->data;
                    temp_Label_holder->_value = mem->IC;
                    temp_Label_holder->_base_address = calcBaseAddress(mem->IC);
                    temp_Label_holder->_offset = calcOffsetAddress(mem->IC);
                    temp_Label_holder->_label_type = INSTRUCTION;
                }
                else
                {
                    announceSyntaxError("label already defined as extern.", mem);
                }
            }
            else
            {
                storeLable(mem->label_Table, name, FALSE, UNDEF, INSTRUCTION, mem->IC, calcBaseAddress(mem->IC), calcOffsetAddress(mem->IC));
            }
        }
        else /*if line is not empty*/
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
                    checkExternSyntax(curr_word, trimmed_Line, mem);
                }
                else
                {
                    if (isExternDefinition(curr_word))
                    {
                        free(curr_word);
                        trimmed_Line = extractWordFromStart(trimmed_Line);
                        curr_word = getTrimmedWordFromLine(trimmed_Line);
                        checkExternSyntax(curr_word, trimmed_Line, mem);
                    }
                }
                temp_label = NULL;
                temp_Label_holder = NULL;
            }
            else /*if not .entry or .extern*/
            {
                temp_label = findNode(mem->label_Table, name); /*save label*/

                if (temp_label != NULL)
                {
                    temp_Label_holder = (Label *)temp_label->data;

                    /*if a label already exits it can only be entry and UNDEF*/
                    if (temp_Label_holder->_attrib_entry == TRUE && temp_Label_holder->_label_type == UNDEF)
                    {
                        temp_Label_holder = (Label *)temp_label->data;
                        temp_Label_holder->_value = mem->IC;
                        temp_Label_holder->_base_address = calcBaseAddress(mem->IC);
                        temp_Label_holder->_offset = calcOffsetAddress(mem->IC);
                    }
                    else
                    {
                        announceSyntaxError("label name already used.", mem);
                    }
                }
                else
                { /*if its not already defined then create label*/
                    storeLable(mem->label_Table, name, FALSE, UNDEF, INSTRUCTION, UNDEF, UNDEF, UNDEF);
                }

                if (isDataLabelDefinition(curr_word)) /*if its a .data line*/
                {
                    temp_label = findNode(mem->label_Table, name); /*find and change type of label to DATA*/
                    ((Label *)(temp_label->data))->_label_type = DATA;
                    ((Label *)(temp_label->data))->_value = mem->DC; /*the base and offset will be calcualted in the start of the second pass*/

                    trimmed_Line = extractWordFromStart(trimmed_Line);
                    handleDataLine(trimmed_Line, mem);
                }
                else
                {
                    if (isStringLabelDefinition(curr_word)) /*if its a .string line*/
                    {
                        temp_label = findNode(mem->label_Table, name); /*find and change type of label to DATA*/
                        ((Label *)(temp_label->data))->_label_type = DATA;
                        ((Label *)(temp_label->data))->_value = mem->DC; /*the base and offset will be calcualted in the start of the second pass*/

                        trimmed_Line = extractWordFromStart(trimmed_Line);
                        handleStringLine(trimmed_Line, mem);
                    }
                    else /*then it must be a command*/
                    {
                        temp_label = findNode(mem->label_Table, name); /*find and change type of label to DATA*/
                        ((Label *)(temp_label->data))->_label_type = INSTRUCTION;
                        ((Label *)(temp_label->data))->_value = mem->IC;
                        ((Label *)(temp_label->data))->_base_address = calcBaseAddress(mem->IC);
                        ((Label *)(temp_label->data))->_offset = calcOffsetAddress(mem->IC);
                        handleCommand(trimmed_Line, mem);
                    }
                }
            }
        }
    }
}

/*handle Instruction line*/
void handleCommand(char *str, Assembler_mem *mem)
{
    char *param = NULL;
    char *mystr = NULL;

    if (str != NULL && !isOnlyWhiteChars(str))
    {

        mystr = trimAll(str);
        param = getParam(mystr); /*get command name*/

        mystr = extractParam(mystr);

        switch (isInstructionName(param))
        {
        case MOV:
            MOVcountLines(mystr, mem);
            break;
        case CMP:
            CMPcountLines(mystr, mem);
            break;
        case ADD:
            ADDcountLines(mystr, mem);
            break;
        case SUB:
            SUBcountLines(mystr, mem);
            break;
        case LEA:
            LEAcountLines(mystr, mem);
            break;
        case CLR:
            CLRcountLines(mystr, mem);
            break;
        case NOT:
            NOTcountLines(mystr, mem);
            break;
        case INC:
            INCcountLines(mystr, mem);
            break;
        case DEC:
            DECcountLines(mystr, mem);
            break;
        case JMP:
            JMPcountLines(mystr, mem);
            break;
        case BNE:
            BNEcountLines(mystr, mem);
            break;
        case JSR:
            JSRcountLines(mystr, mem);
            break;
        case RED:
            REDcountLines(mystr, mem);
            break;
        case PRN:
            PRNcountLines(mystr, mem);
            break;
        case RTS:
            RTScountLines(mystr, mem);
            break;
        case STOP:
            STOPcountLines(mystr, mem);
            break;
        case UNKNOWN:
            announceSyntaxError("unknown command.", mem);
            break;
        }
    }
    else
    {
        mem->no_Errors = FALSE; /*empty line*/
    }
}

/*adds a num to the data array*/
void addToDataImage(int num, Assembler_mem *mem)
{
    mem->Data_Image_Length++;
    mem->Data_Image = realloc(mem->Data_Image, mem->Data_Image_Length * sizeof(int));
    mem->Data_Image[mem->Data_Image_Length - 1] = num;
}



/*recalc all the .data/.staring label address*/
void reCalcLabels(Assembler_mem *mem)
{

    node *label_table = mem->label_Table;
    Label *curr_label;
    while (label_table != NULL)
    {
        if (label_table->key != NULL)
        {
            curr_label = ((Label *)(label_table->data));
            if (curr_label->_label_type == DATA)
            {
                curr_label->_value = curr_label->_value + mem->IC - 1;
                curr_label->_base_address = calcBaseAddress(curr_label->_value);
                curr_label->_offset = calcOffsetAddress(curr_label->_value);
            }
        }
        label_table = label_table->next;
    }
}

/*search entry labels that have not really been intialized in file*/
void checkEntryLables(Assembler_mem *mem)
{
    node *label_table = mem->label_Table;
    Label *curr_label;
    while (label_table != NULL)
    {
        if (label_table->key != NULL)
        {
            curr_label = ((Label *)(label_table->data));
            if (curr_label->_attrib_entry == TRUE && curr_label->_label_type == UNDEF)
            {
                announceSyntaxErrorAtLine("entry label not defined in code", curr_label->_value, mem);
            }
        }
        label_table = label_table->next;
    }
}

/*translate command and write it to the mem->String_image*/
void SpreadCommand(char *str, Assembler_mem *mem)
{
    char *cmd_name, *new_str;
    cmd_name = getTrimmedWordFromLine(str);
    new_str = trimAll(str);
    new_str = extractWordFromStart(new_str);

    translateCommand(isInstructionName(cmd_name), new_str, mem);
}

/*search from used lables, for lables that have not been announced*/
void checkUnusedLabels(Assembler_mem *mem)
{
    node *label_name;
    char *trimmedNameToSearch;
    label_name = mem->ext_labels;
    while (label_name != NULL)
    {
        if (label_name->key != NULL)
        {
            trimmedNameToSearch = trimAll(label_name->key);
            if (findNode(mem->label_Table, trimmedNameToSearch) == NULL)
            {
                announceSyntaxErrorAtLine("unkown label name.", *((int *)(label_name->data)), mem);
            }
            free(trimmedNameToSearch);
        }

        label_name = label_name->next;
    }
}


void translateDataImage(Assembler_mem *mem)
{
    char *thisLine;
    int i = 0;
    if (mem->Data_Image_Length != 0)
    {
        while (i < (mem->Data_Image_Length))
        {
            thisLine = initDataLine();
            setField_ARE(thisLine, ARE_A);
            setField_16bitNum(thisLine, mem->Data_Image[i]);
            mem->String_Image = appendStringAndFreeBoth(mem->String_Image, thisLine);
            i++;
        }
    }
}