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
    mem->String_Image = initString();
    return mem;
}

void restartAssemblerMem(Assembler_mem *mem)
{
    mem->no_Errors = 1;
    free(mem->Data_Image);
    mem->Data_Image = (int *)malloc(1 * sizeof(int));
    mem->Data_Image_Length = 0;
    mem->DC = 0;
    mem->IC = 100;
    mem->line_counter = 1;
    mem->no_Errors = 1;
    killList(mem->label_Table);
    mem->label_Table = initList();
    killList(mem->ext_labels);
    mem->ext_labels = initList();
    free(mem->String_Image);
    mem->String_Image = initString();
}

void freeAssemblerMem(Assembler_mem *mem)
{
    free(mem->Data_Image);
    killList(mem->label_Table);
    killList(mem->ext_labels);
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

void setARE(char *word, int ARE)
{
    switch (ARE)
    {
    case ARE_A:
        word[1] = '1';
        break;
    case ARE_R:
        word[2] = '1';
        break;
    case ARE_E:
        word[3] = '1';
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
    if (BitSize > 20)
        BitSize = 20;
    newnum = (char *)malloc(BitSize + 1);
    newnum[BitSize] = '\0';
    for (i = 0; i < BitSize; i++)
    {
        if ((num & mask))
        {
            newnum[BitSize - i - 1] = '1';
        }
        else
        {
            newnum[BitSize - i - 1] = '0';
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

void setField_Funct(char *line, int num)
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 4);
    line = line + 4;
    memcpy(line, src, strlen(src));
    free(src);
}
void setField_Opcode(char *line, int num)
{
    line[19 - num] = '1';
}
void setField_srcReg(char *line, int num)
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 4);
    line = line + 8;
    memcpy(line, src, strlen(src));
    free(src);
}
void setField_srcIndexMethod(char *line, int num)
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 2);
    line = line + 12;
    memcpy(line, src, strlen(src));
    free(src);
}
void setField_dstReg(char *line, int num)
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 4);
    line = line + 14;
    memcpy(line, src, strlen(src));
    free(src);
}
void setField_dstIndexMethod(char *line, int num)
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 2);
    line = line + 18;
    memcpy(line, src, strlen(src));
    free(src);
}
void setField_16bitNum(char *line, int num)
{
    char *src = convertIntToBitSizedUnsignedBinary(num, 16);
    line = line + 4;
    memcpy(line, src, strlen(src));
    free(src);
}

char *addLabelLines(Label *label)
{
    int i = 0;
    char *word, *result;
    char firstLine[20];
    char secondLine[20];
    for (i = 0; i < 20; i++)
    {
        firstLine[i] = '0';
        secondLine[i] = '0';
    }
    if (label->_attrib_extern == TRUE)
    {
        setARE(firstLine, ARE_E);
        setARE(secondLine, ARE_E);
    }
    else
    {
        setARE(firstLine, ARE_R);
        setARE(secondLine, ARE_R);
    }
    word = convertIntToBitSizedUnsignedBinary(label->_base_address, 16);
    memcpy((firstLine + 4), word, 16);
    free(word);
    word = convertIntToBitSizedUnsignedBinary(label->_offset, 16);
    memcpy((secondLine + 4), word, 16);
    free(word);
    result = initString();
    strcat(result, firstLine);
    strcat(result, "\n");
    strcat(result, secondLine);
    strcat(result, "\n");
    return result;
}

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
            LineValue = (int *)malloc(sizeof(int));
            *LineValue = mem->line_counter;
            insertnewnode(mem->ext_labels, trimmed_parm, LineValue);
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
    if (!isGoodLabelName(temp)) /*checklabel name prior to [rXX]*/
    {
        result = FALSE;
        free(temp);
    }
    else /*save label name for future error checking*/
    {
        LineValue = (int *)malloc(sizeof(int));
        *LineValue = mem->line_counter;
        insertnewnode(mem->ext_labels, temp, LineValue);
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
