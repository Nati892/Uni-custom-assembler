#include "File_utils.h"

/*NOT USED YET*/
/*given a line number the program jumps to the start of the line*/
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
/*NOT USED YET*/
/*adds text in given line and in-line offset*/
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

    myString = (char *)malloc(1);/*initialize string */
    while (current_char != ENDLINE && current_char != EOF)
    {
        current_char = getc(file);/*get first char from line*/
        if (current_char != ENDLINE && current_char != EOF)/*copy chars to string*/
        {
            string_size++;
            myString = (char *)realloc(myString, string_size);
            myString[string_size - 1] = current_char;
        }
    }

    if (current_char == ENDLINE)/*if reached end of line*/
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

/*get word from file line*/
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
