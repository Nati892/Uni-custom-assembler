#include "Text_utils.h"
#include <math.h>

/*This function returns the next line,
the function returns NULL if line only holds EOF or holds nothing.
*/

int isInstructionName(char *str) /*if its an instruction name then returns the enum type of it,else returns FALSE*/
{
    int result = UNKNOWN;
    if (str != NULL)
    {
        if (!strcmp(str, "mov"))
        {
            result = MOV;
        }
        if (!strcmp(str, "cmp"))
        {
            result = CMP;
        }
        if (!strcmp(str, "add"))
        {
            result = ADD;
        }
        if (!strcmp(str, "sub"))
        {
            result = SUB;
        }
        if (!strcmp(str, "lea"))
        {
            result = LEA;
        }
        if (!strcmp(str, "clr"))
        {
            result = CLR;
        }
        if (!strcmp(str, "not"))
        {
            result = NOT;
        }
        if (!strcmp(str, "inc"))
        {
            result = INC;
        }
        if (!strcmp(str, "dec"))
        {
            result = DEC;
        }
        if (!strcmp(str, "jmp"))
        {
            result = JMP;
        }
        if (!strcmp(str, "bne"))
        {
            result = BNE;
        }
        if (!strcmp(str, "jsr"))
        {
            result = JSR;
        }
        if (!strcmp(str, "red"))
        {
            result = RED;
        }
        if (!strcmp(str, "prn"))
        {
            result = PRN;
        }
        if (!strcmp(str, "rts"))
        {
            result = RTS;
        }
        if (!strcmp(str, "stop"))
        {
            result = STOP;
        }
    }
    return result;
}

char *getLine(FILE *file)
{
    char *myString;
    int string_size = 0;
    char current_char = 0;

    myString = (char *)malloc(1); /*initialize string */
    while (current_char != ENDLINE && current_char != EOF)
    {
        current_char = getc(file);                          /*get first char from line*/
        if (current_char != ENDLINE && current_char != EOF) /*copy chars to string*/
        {
            string_size++;
            myString = (char *)realloc(myString, string_size);
            myString[string_size - 1] = current_char;
        }
    }

    if (current_char == ENDLINE) /*if reached end of line*/
    {
        string_size++;
        myString = (char *)realloc(myString, string_size);
        myString[string_size - 1] = current_char;
    }

    if (current_char == EOF)
    {
        if (string_size < 2)
        {
            free(myString);
            return NULL;
        }
        else
        {
            fseek(file, -1, SEEK_CUR);
        }
    }
    /*add \0 in the end of string*/
    string_size++;
    myString = (char *)realloc(myString, string_size);
    myString[string_size - 1] = END_OF_STRING;
    return myString;
}

/*returns new string made of (s1+s2), DOES NOT free s2 or s1*/
char *appendString(char *s1, char *s2)
{
    int s1_size, s2_size, i, j;
    char *new_string;

    if (s1 == NULL && s2 == NULL)
    {
        return NULL;
    }
    /*set strings lengths*/
    (s1 != NULL) ? (s1_size = strlen(s1)) : (s1_size = 0);
    (s2 != NULL) ? (s2_size = strlen(s2)) : (s2_size = 0);
    new_string = (char *)malloc((s1_size + s2_size + 1));

    for (i = 0; i < s1_size; i++) /*append first string*/
    {                             /*Increase memmory size for new string by 1 and append the next char*/
        new_string[i] = s1[i];
    }
    j = i;
    for (i = 0; i < s2_size; i++) /*append second string*/
    {                             /*Increase memmory size for new string by 1 and append the next char*/
        new_string[i + j] = s2[i];
    }
    new_string[s1_size + s2_size] = END_OF_STRING;
    return new_string;
}
/*returns a new string with made of the two given strings and frees both the originals*/
char *appendStringAndFreeBoth(char *s1, char *s2)
{
    char *temp;
    temp = appendString(s1, s2);
    free(s1);
    free(s2);
    return temp;
}
/*returns a new string with made of the two given strings and frees the first one*/
char *appendStringAndFreeFirst(char *s1, char *s2)
{
    char *temp;
    temp = appendString(s1, s2);
    free(s1);
    return temp;
}
/*returns the trimmed given text in a new string, does not free given text pointer*/
char *trimAll(char *text)
{

    char *trimmed_text, *temp;
    int i, j, text_length;
    if (text == NULL || isOnlyWhiteChars(text))
    {
        return NULL;
    }
    text_length = strlen(text);
    j = text_length - 1;               /*j points to last char in string*/
    while (isspace(text[j]) && j >= 0) /*Iterate through white spaces at the end string*/
        j--;
    j++;
    i = 0;
    while (isspace(text[i])) /*Iterate through white spaces at the start*/
        i++;

    if (i > j)
    {
        trimmed_text = NULL;
    }

    else
    {
        j = text_length - j;
        temp = trimStart(text, i);
        trimmed_text = trimEnd(temp, j);
        free(temp);
    }
    return trimmed_text;
}

/*Trims amount of characters from start of string*/
char *trimStart(char *text, int amount)
{
    char *trimmed_text;
    int txt_len, new_txt_len, i;

    txt_len = strlen(text);
    new_txt_len = txt_len - amount;

    if (new_txt_len < 1) /*null handling*/
        return NULL;

    new_txt_len++; /*+1 for \0 char*/
    trimmed_text = (char *)malloc(new_txt_len);
    for (i = 0; i < new_txt_len; i++) /*copy the trimmed text*/
    {
        trimmed_text[i] = text[i + amount];
    }
    return trimmed_text;
}

/*trims amount of characters from end of string*/
char *trimEnd(char *text, int amount)
{
    char *trimmed_text;
    int txt_len, new_txt_len, i;

    txt_len = strlen(text);
    new_txt_len = txt_len - amount;

    if (new_txt_len <= 0) /*null handling*/
        return NULL;
    trimmed_text = (char *)malloc(new_txt_len + 1); /*+1 for \0 char*/
    for (i = 0; i < new_txt_len; i++)               /*cpoy the trimmed text*/
    {
        trimmed_text[i] = text[i];
    }
    trimmed_text[i] = END_OF_STRING;

    return trimmed_text;
}

/*gets first word from line*/
char *getWordFromLine(char *Line)
{
    char *word = NULL;
    int word_length = 0, i = 0;

    while (isspace(Line[i]) && Line[i] != END_OF_STRING) /*skip through white space chars*/
    {
        i++;
    }
    word = (char *)malloc(1);
    while (!isspace(Line[i]) && Line[i] != END_OF_STRING) /*copy the word itself*/
    {
        word_length++;
        word = realloc(word, word_length);
        word[word_length - 1] = Line[i];
        i++;
    }
    word_length++; /*add the \0 char at the end of string*/
    word = realloc(word, word_length);
    word[word_length - 1] = END_OF_STRING;

    if (word_length <= 1) /*if there is only the \0 in the word String*/
    {
        free(word);
        word = NULL;
    }
    return word;
}

char *getTrimmedWordFromLine(char *Line) /*gets a fully trimmed word from a string*/
{
    char *temp, *word;
    temp = getWordFromLine(Line);
    if (temp == NULL)
        return NULL;
    word = trimAll(temp);
    free(temp);
    if (word == NULL)
    {
        return NULL;
    }
    return word;
}

/*this function returns the given line without the first word, and frees the original line*/
char *extractWordFromStart(char *Line)
{
    char *newLine;
    int newLineSize, i = 0, j;
    while (isspace(Line[i]) && Line[i] != END_OF_STRING) /*skip white chars*/
    {
        i++;
    }
    while (!isspace(Line[i]) && Line[i] != END_OF_STRING)
    {
        i++;
    }
    newLineSize = strlen(Line) - i + 1; /*+1 for \0 char*/
    newLine = (char *)malloc(newLineSize);
    for (j = 0; j < newLineSize; j++)
    {
        newLine[j] = Line[j + i];
    }
    free(Line);
    return newLine;
}

/*creates empty string*/
char *initString()
{
    char *pointer;
    pointer = (char *)malloc(1);
    pointer[0] = END_OF_STRING;
    return pointer;
}
/*appends char at the end of a string*/
void appendCharAtEnd(char *line, char toAppend)
{
    int line_len;
    if (line == NULL)
        return;
    line_len = strlen(line);
    line = (char *)realloc(line, line_len + 2);
    line[line_len] = toAppend;
    line[line_len + 1] = END_OF_STRING;
}

/*compares 2 strings, THIS FUCNION CAN HANDLE NULLS AS WELL!*/
int compareStrings(char *a, char *b)

{
    int result;
    if (a == NULL && b == NULL)
        result = 0;
    if (a == NULL || b == NULL)
        result = 1;
    else
    {
        result = strcmp(a, b);
    }
    return result;
}

/*this function counts the consective commas in the start of the given string and returns it.*/
int countCommas(char *LinePointer)
{
    int i = 0, Commacounter = 0;
    if (LinePointer == NULL)
        return Commacounter;
    while (LinePointer[i] == COMMA_CHAR || isWhiteChar(LinePointer[i])) /*run through white chars and commas*/
    {
        if (LinePointer[i] == COMMA_CHAR) /*count commas*/
            Commacounter++;
        i++;
    }
    return Commacounter;
}

/*This functions is only called after knowing there is a comma to be removed (countcommas()).
it removes 1 comma and also all white chars wrpping it(\n and EOF excluded)*/
void removeComma(char *LinePointer)
{
    int i = 0, j, LineLength;
    LineLength = strlen(LinePointer);
    while (isWhiteChar(LinePointer[i])) /*skip white chars before comma*/
    {
        i++;
    }
    i++;                                /*skip comma*/
    while (isWhiteChar(LinePointer[i])) /*skip white chars after comma*/
    {
        i++;
    }
    /*overwrite the string with the white char after the comma */
    LineLength++; /*to copy the /0 in the end of string*/
    for (j = 0; j < (LineLength - i + 1); j++)
    {
        LinePointer[j] = LinePointer[j + i];
    }
}

/*this function looks for any kind of characters that are not white chars */
/*1 for no residual text, 0 for residual text*/
int checkResidualText(char *LinePointer)
{
    int i = 0, result = 1;
    if (LinePointer == NULL)
        return result;
    while (LinePointer[i] != ENDLINE && LinePointer[i] != EOF && LinePointer[i] != END_OF_STRING)
    {
        if (!isWhiteChar(LinePointer[i]))
            result = 0;
        i++;
    }
    return result;
}

/*this fuction return 1 if the line is all white characters, and 0 if not*/
int isOnlyWhiteChars(char *LinePointer)
{
    int i = 0, Length, allwhitechars = 1;
    if (LinePointer == NULL)
    {
        return allwhitechars;
    }

    Length = strlen(LinePointer);
    for (i = 0; i < Length; i++) /*loop and check for white chars*/
    {
        if (!isspace(LinePointer[i]))
        {
            allwhitechars = 0;
        }
    }
    return allwhitechars;
}

/*This function is like isspace but the new-line char doesnt count as a white character*/
int isWhiteChar(char c)
{
    if (c == ' ' || c == '\f' || c == '\t' || c == '\v' || c == '\r')
        return 1;
    else
        return 0;
}

/*checks if given line is a comment line*/
int isCommentLine(char *line)
{
    int result = 0;
    int i = 0;
    while (isspace(line[i])) /*skip whitespace characters*/
    {
        i++;
    }
    if (line[i] == COMMENT_START)
    {
        result = 1;
    }
    return result;
}

/*checks if string is a preserved word*/
int isKeyWord(char *str)
{
    int result = FALSE;
    if (isInstructionName(str) || isDataLabelDefinition(str) || isStringLabelDefinition(str) || isEntryDefinition(str) || isExternDefinition(str) || isMacroEnd(str) || isMacroStart(str) || isRegisterNameInRange(str))
        result = TRUE;
    return result;
}

/*checks if string is a register index*/
int isRegisterNameInRange(char *str)
{
    int converted;
    int result = 0;

    if (str == NULL)
        return result;
    if (str[0] == 'r') /*first digit is 'r'*/
    {
        if (strlen(str) == 2 && isdigit(str[1])) /*only one number after r*/
        {
            result = 1;
        }
        else
        {
            if (strlen(str) == 3 && isdigit(str[1]) && isdigit(str[2])) /*if two numbers after*/
            {
                converted = atoi((str + 2));
                if (converted <= 5 && str[1] == '1') /*also check first digit to be in range 0-5*/
                    result = 1;
            }
        }
    }
    return result;
}

/*get the number from the start of the text, this function is called knowing there is a well written number to extract*/
int getIntegerFromText(char *str)
{
    char *num_string;
    int i = 0;
    int result;
    num_string = initString();
    while (isWhiteChar(str[i])) /*skip white chars*/
    {
        i++;
    }
    while (str[i] == PLUS_SIGN || str[i] == MINUS_SIGN || isdigit(str[i]))
    {
        appendCharAtEnd(num_string, str[i]);
        i++;
    }
    result = atoi(num_string);
    free(num_string);
    return result;
}

/*checks if there is a number in the start of the text*/
int checkIntegerInText(char *str)
{

    int i = 0;
    int result = FALSE;
    if (str == NULL)
        return FALSE;
    while (isWhiteChar(str[i])) /*skip white chars*/
    {
        i++;
    }

    if (str[i] == PLUS_SIGN || str[i] == MINUS_SIGN) /*check + - signs*/
    {
        i++;
    }
    if (isdigit(str[i]))
        result = TRUE;
    while ((!isWhiteChar(str[i])) && str[i] != END_OF_STRING && str[i] != COMMA_CHAR)
    {
        if (!isdigit(str[i]))
        {
            result = FALSE;
        }
        i++;
    }
    return result;
}

void removeIntegerFromText(char *str) /*replaces all the number digits with space characters, called knowing there is a num at the start*/
{

    int i = 0;
    while (isWhiteChar(str[i]))
    {
        i++;
    }
    while (str[i] == PLUS_SIGN || str[i] == MINUS_SIGN || isdigit(str[i]))
    {
        str[i] = SPACE_CHAR;
        i++;
    }
}

int isIntInRange(int myInt)
{
    if (myInt <= MAX_INT_SIZE && myInt >= MIN_INT_SIZE)
        return TRUE;
    else
        return FALSE;
}
int isExternDefinition(char *str) /*check if it is an extern label*/
{
    char *trimmed_str;
    int result = 1;

    trimmed_str = trimAll(str);
    if (strcmp(trimmed_str, EXTERN_WORD))
    {
        result = 0;
    }
    free(trimmed_str);
    return result;
}
int isEntryDefinition(char *str) /*check if it is an entry definition*/
{
    char *trimmed_str;
    int result = 1;
    trimmed_str = trimAll(str);
    if (strcmp(trimmed_str, ENTRY_WORD))
        result = 0;
    free(trimmed_str);

    return result;
}

/*checks whether is it a .data def*/
int isDataLabelDefinition(char *str)
{
    int result = TRUE;
    if (str == NULL)
        return FALSE;
    if (strcmp(str, ".data") != 0)
        result = FALSE;
    return result;
}

/*checks whether is it a .string def*/
int isStringLabelDefinition(char *str)
{
    int result = TRUE;
    if (str == NULL)
        return FALSE;
    if (strcmp(str, ".string") != 0)
        result = FALSE;
    return result;
}

int isMacroStart(char *text)
{
    int result = 0;
    char *temp = NULL;
    temp = trimAll(text);

    if (temp != NULL)
    {
        if (!strcmp(temp, MACRO_START))
            result = 1;
        free(temp);
    }
    return result;
}

/*checks if text has the "endm" word at the start of it*/
int isMacroEnd(char *text)
{
    int result = 0;
    char *temp = NULL;
    temp = trimAll(text);
    if (temp != NULL)
    {
        if (!strcmp(temp, MACRO_END))
            result = 1;
        free(temp);
    }
    return result;
}

/*this function returns whether or not a label name is legal*/
int isGoodLabelName(char *str)
{
    char *trimmed_str;
    int result = 1;
    int char_counter = 0; /*label name length is max 31 chars*/

    if (str == NULL)
    {
        return 0;
    }
    trimmed_str = trimAll(str);
    /*make sure that first letter is alphanumeric*/
    if (!isalpha(trimmed_str[char_counter]))
    {
        result = 0;
    }
    else
    {
        char_counter++;
        /*check that all chars are alphanumeric*/
        while (trimmed_str[char_counter] != END_OF_STRING)
        {
            if (!isalnum(trimmed_str[char_counter]))
                result = 0;
            char_counter++;
        }
        if (char_counter > LABEL_NAME_MAX_LENGTH)
        {
            result = 0;
        }

        if (result)
        {
            result = !isKeyWord(str);
        }

        free(trimmed_str);
    }

    return result;
}
/*this function returned a trimmed version of the first param in line*/

/*this function returns the first parameter in line, if there isnt one then it returns NULL*/
char *getParam(char *Line)
{
    char *temp_param = NULL;
    char *returned_parm = NULL;
    int i = 0, j = 0;
    if (Line != NULL && !isOnlyWhiteChars(Line))
    {
        while (isWhiteChar(Line[i])) /*loop through white chars*/
        {
            i++;
        }
        while (!isWhiteChar(Line[i]) && Line[i] != COMMA_CHAR && Line[i] != END_OF_STRING)
        {
            i++;
        }

        temp_param = (char *)malloc(i + 1); /*include NULL terminator*/

        temp_param[i] = END_OF_STRING;

        for (j = 0; j < i; j++)
        {
            temp_param[j] = Line[j];
        }

        returned_parm = trimAll(temp_param);

        free(temp_param);
    }
    return returned_parm;
}

/*this function removes the first parameter,frees the original string and returns a new one without the param*/
char *extractParam(char *str)
{
    int i = 0, j = 0;
    char *new_str;
    while (isWhiteChar(str[i])) /*loop through white chars*/
    {
        i++;
    }
    while (!isWhiteChar(str[i]) && str[i] != COMMA_CHAR && str[i] != END_OF_STRING)
    {
        i++;
    }

    new_str = (char *)malloc(strlen(str) - i + 1);
    new_str[strlen(str) - i] = END_OF_STRING;
    for (j = 0; j < (strlen(str) - i); j++)
    {
        new_str[j] = str[i + j];
    } 
    free(str);
    return new_str;
}
/*checks if the recieved param is an immediate indexed param*/

int binStringToInt(char *bin_num)
{
    int result = 0, i;
    for (i = 0; i < 4; i++)
    {
        if (bin_num[i] == CHAR_ONE)
            result += pow(2.0, (double)(3 - i));
    }
    return result;
}