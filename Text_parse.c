#include "Text_parse.h"


/*returns s1+s2, DOES NOT free(s2)*/
char *appendString(char *s1, char *s2)
{
    int s1_size, s2_size, i, j;
    char *new_string;
    
    if (s1 == NULL && s2 == NULL)
    {
        return NULL;
    }
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
    if (new_txt_len < 1)
        return NULL;
    new_txt_len++; /*+1 for \0 char*/
    trimmed_text = (char *)malloc(new_txt_len);
    for (i = 0; i < new_txt_len; i++)
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

    if (new_txt_len <= 0)
        return NULL;

    trimmed_text = (char *)malloc(new_txt_len + 1); /*+1 for \0 char*/
    for (i = 0; i < new_txt_len; i++)
    {
        trimmed_text[i] = text[i];
    }
    trimmed_text[i] = END_OF_STRING;
    return trimmed_text;
}


char *getWordFromLine(char *Line)
{
    char *word=NULL;
    int word_length = 0, i = 0;

    while (isspace(Line[i]) && Line[i] != END_OF_STRING)
    {
        i++;
    }
    word = (char *)malloc(1);
    while (!isspace(Line[i]) && Line[i] != END_OF_STRING)
    {
        word_length++;
        word = realloc(word, word_length);
        word[word_length - 1] = Line[i];
        i++;
    }
    word_length++;
    word = realloc(word, word_length);
    word[word_length - 1] = END_OF_STRING;
    
    if (word_length <= 1) /*if there is only the \0 in the word String*/
    {
        free(word);
        word = NULL;
    }
    return word;
}

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



char *getTrimmedWord(FILE *file)
{
    char *temp1, *temp2 = NULL;
    temp1 = getWord(file);
    temp2 = trimAll(temp1);
    free(temp1);

    return temp2;
}

void appendEndLineChar(char *line)
{
    int length = strlen(line);
    line = realloc(line, length + 2);
    line[length] = ENDLINE;
    line[length + 1] = END_OF_STRING;
}

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