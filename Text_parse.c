#include "Text_parse.h"

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

/*returns the trimmed given text in a new string, does not free given text pointer*/
char *trimAll(char *text)
{
    /* printf("trimAll started with word-->%s<--\n", text);*/

    char *trimmed_text, *temp;
    int i, j, text_length;
    if (text == NULL)
    {
        return NULL;
        /*printf("trimAll ends with null \n");*/
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
    /*printf("trimAll ended with -->%s<--\n", trimmed_text);*/
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

/*appends a \n in the end of string */
void appendEndLineChar(char *line)
{
    int length = strlen(line);
    line = realloc(line, length + 2);
    line[length] = ENDLINE;
    line[length + 1] = END_OF_STRING;
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
    while (LinePointer[i] != ENDLINE && LinePointer[i] != EOF)
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

/*this function checks if a line only containes white chars and EOF*/
int isOnlyEOF(char *LinePointer)
{
    int i = 0, Length, onlyEOF = 1;
    if (LinePointer == NULL)
    {
        return 0; /*if line is null then there is no EOF char in it*/
    }

    Length = strlen(LinePointer);
    for (i = 0; i < Length - 1; i++)
    {
        if (!isspace(LinePointer[i]))
        {
            onlyEOF = 0;
        }
    }
    if (LinePointer[Length - 1] != EOF)
    {
        onlyEOF = 0;
    }

    return onlyEOF;
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
    int i;
    int result = 0;

    if (str == NULL)
        return result;
    for (i = 0; i < NUM_OF_KEYWORDS; i++) /*check if part of the reserved words */
    {
        if (!strcmp(str, keyWordsArr[i]))
        {
            result = 1;
        }
    }
    if (!result) /*checks if register */
    {
        result = (isRegisterNameInRange(str));
    }

    return result;
}

/*checks if string is a register index*/
int isRegisterNameInRange(char *str)
{
    int converted;
    int result = 0;
    printf("isREgister in range-> %s<-\n", str);
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
    printf("isREgister in range result -> %d<-\n", result);
    return result;
}

/*get the number from the start of the text, this function is called knowing there is a umber to extract*/
int getNumberFromText(char *str)
{
    char *num_string;
    int i = 0;

    while (isWhiteChar(str[i])) /*skip white chars*/
    {
        i++;
    }
}

int checkNumberInText(char *str);    /*checks if there is a number in the start of the text*/
int removeNumberFromText(char *str); /*replaces all the number digits with space characters*/
