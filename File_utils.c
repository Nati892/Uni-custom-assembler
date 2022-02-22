#include "File_utils.h"

int goToLine(FILE *file, int line_num)
{
    int Line_Pos = 1;
    int exit_status;
    char inputChar = 0;
    fpos_t temp;

    fgetpos(file, &temp);                            /*save position incase of failure*/
    fseek(file, 0, SEEK_SET);                        /*go to start*/
    while (Line_Pos != line_num && inputChar != EOF) /*loop through file and count lines*/
    {
        inputChar = fgetc(file);
        if (inputChar == '\n')
            Line_Pos++;
    }

    if (Line_Pos == line_num)
    {
        exit_status = 1;
    }
    else
    {
        exit_status = 0;
        fsetpos(file, &temp); /*in case of failure restore file to original position*/
    }
    return exit_status; /*exit*/
}

int addTextToLine(FILE *file, char *filename, int Line_num, int offset, char *text)
{
    int exit_status = 1;
    int i;
    fpos_t pos1, pos2;
    char inputChar = 0;
    FILE *temp;
    if (!goToLine(file, Line_num))
        exit_status = 0;
    else
    {
        temp = fopen(TEMP_FILE_NAME, "w+");

        fgetpos(file, &pos1);
        fseek(file, 0, SEEK_SET);
        for (i = 0; inputChar != EOF; i++) /*copy all contents to tmp.tmp*/
        {
            inputChar = fgetc(file);
            if (inputChar != EOF)
            {
                fputc(inputChar, temp);
            }
        }
        fsetpos(file, &pos1);
        fsetpos(temp, &pos1);

        for (i = 0; i < offset; i++) /*make sure offset is ok*/
        {
            inputChar = fgetc(file);
            if (inputChar == EOF || inputChar == '\n')
            {
                exit_status = 0;
            }
        }

        if (exit_status == 0) /*if offset not ok then exit*/
        {
            fsetpos(file, &pos1);
            remove(TEMP_FILE_NAME);
            return exit_status;
        }

        fgetpos(file, &pos2);
        fsetpos(temp, &pos2);
        /*text to file*/
        i = 0;
        while (text[i] != 0)
        {
            fputc(text[i], temp);
            i++;
        }

        inputChar = 0;
        while (inputChar != EOF)
        {
            inputChar = fgetc(file);
            if (inputChar != EOF)
            {
                fputc(inputChar, temp);
            }
        }
        remove(filename);
        rename(TEMP_FILE_NAME, filename);
        return exit_status;
    }
    return exit_status;
}

/*This function returns the next line NOT including the \n character,
the function returns NULL if line only holds EOF or holds nothing.
*/
char *getLine(FILE *file)
{
    char *myString;
    int string_size = 0;
    char current_char = 0;
    myString = (char *)malloc(1);
    while (current_char != ENDLINE && current_char != EOF)
    {
        current_char = getc(file);
        if (current_char != ENDLINE && current_char != EOF)
        {
            string_size++;
            myString = (char *)realloc(myString, string_size);
            myString[string_size - 1] = current_char;
        }
    }
    if (current_char == ENDLINE)
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
    string_size++;
    myString = (char *)realloc(myString, string_size);
    myString[string_size - 1] = END_OF_STRING;
    return myString;
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

/*returns s1+s2, DOES NOT free(s2)*/
char *appendString(char *s1, char *s2)
{
    int s1_size, s2_size, i, j;
    char *new_string;
    printf("starting appendString with ->%s<- and ->%s<-\n", s1, s2);
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

char *getWord(FILE *file)
{
    char *new_string;
    int new_size = 0;
    char current_char = SPACE_CHAR;
    new_string = (char *)malloc(1 * sizeof(char));
    while (isspace(current_char) && current_char != EOF) /*add pre-word white spaces to string*/
    {
        current_char = getc(file);
        if (isspace(current_char) && current_char != EOF)
        {
            new_size++;
            new_string = realloc(new_string, new_size);
            new_string[new_size - 1] = current_char;
        }
    }

    if (current_char != EOF) /*add that first non-space char*/
    {
        new_size++;
        new_string = realloc(new_string, new_size);
        new_string[new_size - 1] = current_char;
    }

    while (!isspace(current_char) && current_char != EOF) /*add the word itself - non white space characters*/
    {
        current_char = getc(file);
        if (!isspace(current_char))
        {
            new_size++;
            new_string = realloc(new_string, new_size);
            new_string[new_size - 1] = current_char;
        }
    }
    /*add \0 at the end of string*/
    if (new_string != NULL)
    {
        new_size++;
        new_string = realloc(new_string, new_size);
        new_string[new_size - 1] = END_OF_STRING;
    }
    fseek(file, -1, SEEK_CUR); /*go back one char*/

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