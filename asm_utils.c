#include "asm_utils.h"
Assembler_mem *InitAssemblerMem()
{
    Assembler_mem *mem = (Assembler_mem *)malloc(sizeof(Assembler_mem));
    mem->no_Errors = 1;
    mem->Data_Image = (int *)malloc(1 * sizeof(int));
    mem->Data_Image_Length = 0;
    mem->DC = 1;
    mem->IC = 100;
    mem->line_counter = 1;
    mem->no_Errors = 1;
    mem->label_Table = initList();
    mem->ext_labels = initList();
    mem->ext_file_table = initList();
    mem->String_Image = initString();
    mem->file_name = NULL;
    return mem;
}

void freeAssemblerMem(Assembler_mem *mem)
{
    free(mem->Data_Image);
    killList(mem->label_Table);
    killList(mem->ext_labels);
    killList(mem->ext_file_table);
    free(mem->String_Image);
    free(mem);
}

void announceSyntaxError(char *ERR, Assembler_mem *mem)
{
    mem->no_Errors = FALSE;
    printf("ERROR in line %d:: %s\n", mem->line_counter, ERR);
}

void announceSyntaxErrorAtLine(char *str, int lineNumber, Assembler_mem *mem)
{
    mem->no_Errors = FALSE;
    printf("ERROR in line %d:: %s\n", lineNumber, str);
}

void setField_ARE(char *word, int ARE)
{
    switch (ARE)
    {
    case ARE_A:
        word[1] = CHAR_ONE;
        break;
    case ARE_R:
        word[2] = CHAR_ONE;
        break;
    case ARE_E:
        word[3] = CHAR_ONE;
        break;
    }
}

char *convertIntToBitSizedUnsignedBinary(int num, int BitSize)
{
    char *newnum;
    int i;
    unsigned int mask = 0x00000001;
    if (BitSize <= 0)
        return NULL;
    if (BitSize > DATA_WORD_LENGTH)
        BitSize = DATA_WORD_LENGTH;
    newnum = (char *)malloc(BitSize + 1);
    newnum[BitSize] = END_OF_STRING;
    for (i = 0; i < BitSize; i++)
    {
        if ((num & mask))
        {
            newnum[BitSize - i - 1] = CHAR_ONE;
        }
        else
        {
            newnum[BitSize - i - 1] = CHAR_ZERO;
        }
        mask = mask << 1;
    }
    return newnum;
}

/*sets a substring to be a certin unsigned num*/
void setSubStringToBinary(char *str, int num, int start, int finish)
{
    char *newNum;
    int i;
    if (str != NULL && finish <= strlen(str))
    {
        newNum = convertIntToBitSizedUnsignedBinary(num, finish - start);
        if (newNum != NULL)
        {
            for (i = 0; (i + start) < finish; i++)
            {
                str[start + i] = newNum[i];
            }
            free(newNum);
        }
    }
}

/*set the funct field (int binary) of a given string with a given number */
void setField_Funct(char *line, int num)
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 4);
    line = line + 4;
    memcpy(line, src, strlen(src));
    free(src);
}

void setField_Opcode(char *line, int num) /*set the opcode field (int binary) of a given string with a given number */
{
    line[19 - num] = CHAR_ONE;
}

void setField_srcReg(char *line, int num) /*set the source register field (int binary) of a given string with a given number */
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 4);
    line = line + 8;
    memcpy(line, src, strlen(src));
    free(src);
}

void setField_srcIndexMethod(char *line, int num) /*set the source register index field (int binary) of a given string with a given number */
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 2);
    line = line + 12;
    memcpy(line, src, strlen(src));
    free(src);
}

void setField_dstReg(char *line, int num) /*set the dest' register field (int binary) of a given string with a given number */
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 4);
    line = line + 14;
    memcpy(line, src, strlen(src));
    free(src);
}

void setField_dstIndexMethod(char *line, int num) /*set the dest' register index field (int binary) of a given string with a given number */
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 2);
    line = line + 18;
    memcpy(line, src, strlen(src));
    free(src);
}

void setField_16bitNum(char *line, int num) /*set the 16 digit field (int binary) of a given string with a given number */
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 16);
    line = line + 4;
    memcpy(line, src, strlen(src));
    free(src);
}

char *initDataLine() /*intializes data line with a \n in the end*/
{
    char *newLine;
    int i;
    newLine = (char *)malloc(DATA_WORD_LENGTH + 2);
    for (i = 0; i < DATA_WORD_LENGTH; i++)
    {
        newLine[i] = CHAR_ZERO;
    }

    newLine[DATA_WORD_LENGTH + 1] = END_OF_STRING;
    newLine[DATA_WORD_LENGTH] = ENDLINE;
    return newLine;
}

/*when seeing extern label used then saves it to the mem->*/
void saveExternUsedInLine(char *label_name, Assembler_mem *mem)
{
    char *trimmedParam;
    node *tempNode = NULL;
    Label *tempLabel = NULL;
    trimmedParam = trimAll(label_name);
    tempNode = findNode(mem->label_Table, trimmedParam);
    if (tempNode != NULL)
    {
        tempLabel = (Label *)tempNode->data;
        if (tempLabel != NULL && tempLabel->_attrib_extern == TRUE)
        {
            int *LineNum = (int *)malloc(sizeof(int));
            *LineNum = mem->IC;
            insertnewnode(mem->ext_file_table, trimmedParam, LineNum);
        }
    }
}

/*checks if the recieved param is an immediate indexed param*/
int isIndextype0(char *Param)
{
    char *trimmedParam = NULL;
    char *temp;
    int result = FALSE;
    int len = 0;
    if (Param != NULL && !isOnlyWhiteChars(Param))
    {
        trimmedParam = trimAll(Param);
        temp = trimmedParam;
        len = strlen(trimmedParam);
        if (len > 2 && trimmedParam[0] == '#') /*set macro for hash*/
        {
            trimmedParam++; /*advance to first digit*/
            if (checkIntegerInText(trimmedParam))
            {

                if (isIntInRange(getIntegerFromText(trimmedParam))) /*check if int is in range of 16 bit numbers*/
                    result = TRUE;
                /*   free(trimmedParam);*/
            }
        }
        free(temp);
    }
    return result;
}
/*checks if the recieved param is an direct indexed param*/
int isIndextype1(char *Param, Assembler_mem *mem)
{
    int result = FALSE;
    char *trimmed_parm;
    int *LineValue;

    if (Param != NULL && !isOnlyWhiteChars(Param))
    {

        trimmed_parm = trimAll(Param);
        if (isGoodLabelName(trimmed_parm))
        {

            result = TRUE;
            if (mem != NULL)
            {
                LineValue = (int *)malloc(sizeof(int));
                *LineValue = mem->line_counter;
                insertnewnode(mem->ext_labels, trimmed_parm, LineValue);
            }
        }
    }
    return result;
}

/*checks if the recieved param is an 'Index' indexed param*/
int isIndextype2(char *Param, Assembler_mem *mem)
{
    int result = TRUE;
    char *trimmed_param;
    char *temp;
    int j = 0;
    int i = 0;
    int *LineValue;
    if (Param == NULL || isOnlyWhiteChars(Param))
    {
        return FALSE;
    }

    trimmed_param = trimAll(Param);
    while (trimmed_param[i] != END_OF_STRING && !isWhiteChar(trimmed_param[i]) && trimmed_param[i] != '[')
    {
        i++;
    } /*skip the first word, and check to see if its a valid name for a parameter*/
    temp = (char *)malloc(i + 1);
    temp[i] = END_OF_STRING;
    while (j < i)
    {
        temp[j] = trimmed_param[j];
        j++;
    }
    if (!isGoodLabelName(temp)) /*check label name prior to [rXX]*/
    {
        result = FALSE;
        free(temp);
    }
    else /*save label name for future error checking*/
    {
        if (mem != NULL)
        {
            LineValue = (int *)malloc(sizeof(int));
            *LineValue = mem->line_counter;
            insertnewnode(mem->ext_labels, temp, LineValue);
        }
    }

    if (trimmed_param[i] != '[')
        result = FALSE;
    i++;

    if (trimmed_param[strlen(trimmed_param) - 1] != ']')
        result = 0;
    if (strlen(trimmed_param) - i != 4)
    {
        result = 0;
    }
    else
    {

        temp = (char *)malloc(4);
        temp[3] = END_OF_STRING;
        j = 0;
        while (j < 3)
        {
            temp[j] = trimmed_param[j + i];
            j++;
        }
        if (!isRegisterNameInRange(temp))
            result = FALSE;
    }
    return result;
}

/*checks if the recieved param is an register direct indexed param*/
int isIndextype3(char *Param)
{
    char *trimmed_param;
    int result;

    if (Param != NULL && !isOnlyWhiteChars(Param))
    {
        trimmed_param = trimAll(Param);
        result = isRegisterNameInRange(trimmed_param);
    }
    return result;
}

int isLabelDefinition(char *str) /*checks if it is a 'label:' definition*/
{
    char *trimmed_str;
    int result = 1;

    if (str == NULL)
    {
        return 0;
    }

    trimmed_str = trimAll(str);
    if (trimmed_str[strlen(trimmed_str) - 1] != LABEL_DECLARATION_END)
    {
        result = 0;
    }

    free(trimmed_str);

    return result;
}

node *LabelConstructor(char *label_name, int is_extern, int attrib_entry, int label_type, int value, int base_address, int offset)
{
    node *new_node = NULL;
    Label *new_label = NULL;
    if (label_name != NULL)
    {
        new_label = (Label *)malloc(sizeof(Label));
        new_label->_attrib_extern = is_extern;
        new_label->_label_type = label_type;
        new_label->_attrib_entry = attrib_entry;
        new_label->_value = value;
        new_label->_base_address = base_address;
        new_label->_attrib_entry = attrib_entry;
        new_label->_offset = offset;

        new_node = createNode(label_name, new_label);
    }
    return new_node;
}

void storeLable(node *label_table, char *label_name, int is_extern, int attrib_entry, int label_type, int value, int base_address, int offset)
{
    Label *new_label = NULL;
    node *new_node = NULL;
    if (label_table->key == NULL) /*if first in list*/
    {
        if (label_name != NULL) /*if valid name for label*/
        {
            label_table->key = label_name;
            new_label = (Label *)malloc(sizeof(Label));
            new_label->_attrib_extern = is_extern;
            new_label->_label_type = label_type;
            new_label->_attrib_entry = attrib_entry;
            new_label->_value = value;
            new_label->_base_address = base_address;
            new_label->_attrib_entry = attrib_entry;
            new_label->_offset = offset;
            label_table->data = new_label;
        }
    }
    else
    {
        new_node = LabelConstructor(label_name, is_extern, attrib_entry, label_type, value, base_address, offset);
        insertnode(label_table, new_node);
    }
}

int calcBaseAddress(int line_num)
{
    return ((line_num / 16) * 16);
}

int calcOffsetAddress(int line_num)
{
    return line_num % 16;
}