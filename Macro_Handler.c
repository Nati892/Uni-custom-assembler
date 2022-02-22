#include "Macro_Handler.h"

void macroStage(FILE *file, char *file_name)
{
    node *LL;
    FILE *am_file;
    LL = createNode(NULL, NULL);
    fseek(file, 0, SEEK_SET); /*make sure the file stream is at the start*/
    collectMacros(file, LL);
    printAllMacros(LL);
    am_file = createMacroFile(file_name);
    if (am_file != NULL)
    {
        fseek(file, 0, SEEK_SET);
        fseek(am_file, 0, SEEK_SET);
        spreadMacros(file, am_file, LL);
        fclose(am_file);
        killList(LL);
    }
    printf("FINISHED\n"); /*DEBUG*/
}

void PrintLines(FILE *file) /*DEBUG*/
{
    int i = 0, j;
    char *line = NULL;
    line = getLine(file);
    while (line != NULL)
    {
        for (i = 0; i < 100000000 * 7 / 8; i++)
        {
            /* code */
        }

        printf("current->%s<-  ->", line);
        for (j = 0; j < strlen(line); j++)
        {
            printf("%d,", line[j]);
        }
        free(line);
        line = getLine(file);
    }
}

void collectMacros(FILE *file, node *LL)
{
    int i;
    char *line, *macro_key, *macro_body, *temp, *word;
    fseek(file, 0, SEEK_SET);
    line = getLine(file);

    if (line == NULL) /*empty file*/
        return;

    while (line != NULL)
    {
        if (!isCommentLine(line)) /*skip comment lines*/
        {
            word = getWordFromLine(line);
            if (isMacroStart(word)) /*if start of macro then collect and store the marco*/
            {
                if (word != NULL)
                    free(word);
                macro_body = NULL;
                printf("detected macro\n");
                line = extractWordFromStart(line);

                temp = getWordFromLine(line); /*store macro name*/
                macro_key = trimAll(temp);
                if (temp != NULL)
                    free(temp);
                line = getLine(file);
                temp = trimAll(line);

                while (compareStrings(temp, MACRO_END)) /*adding lines to macro body until endm*/
                {
                    if (temp != NULL)
                        free(temp);
                    if (macro_body == NULL) /*in case of first line in macro body*/
                    {
                        macro_body = line;
                    }
                    else
                    {
                        temp = appendString(macro_body, line);
                        free(macro_body);
                        macro_body = temp;
                        free(line);
                    }
                    line = getLine(file);
                    temp = (trimAll(line));
                }
                storeMacro(LL, macro_key, macro_body);
            }
        }
        free(line);
        line = getLine(file);
    }
    printf("finished collecting macros\n");
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

void spreadMacros(FILE *src_file, FILE *dest_file, node *LL)
{
    char *current_line, *word = NULL, *temp = NULL;
    node *curr_macro = NULL;
    printf("********STARTED SPREADING MACROS***********\n");
    current_line = getLine(src_file);
    while (current_line != NULL)
    {
        if (isCommentLine(current_line)) /*copy comment lines*/
        {
            fprintf(dest_file, "%s", current_line);
        }
        else
        {
            temp = getWordFromLine(current_line);
            word = trimAll(temp);
            free(temp);

            if (!compareStrings(word, MACRO_START)) /*skip macro declarations*/
            {
                free(word);

                free(current_line);
                current_line = NULL;
                current_line = getLine(src_file);
                temp = getWordFromLine(current_line);
                word = trimAll(temp);
                free(temp);
                while (compareStrings(word, MACRO_END)) /*while have not reached endm keep looping*/
                {
                    free(word);
                    free(current_line);
                    current_line = NULL;
                    current_line = getLine(src_file);
                    temp = getWordFromLine(current_line);
                    word = trimAll(temp);
                    free(temp);
                }

                if (word != NULL)
                    free(word);
            }
            else /*check for macro name appearance*/
            {
                temp = getWordFromLine(current_line);
                word = trimAll(temp);
                free(temp);
                curr_macro = searchMacro(LL, word);

                if (curr_macro != NULL)
                {
                    if (curr_macro->data != NULL)
                        fprintf(dest_file, "%s", curr_macro->data);
                }

                else
                {
                    fprintf(dest_file, "%s", current_line);
                }
                free(word);
            }
        }

        if (current_line != NULL)
            free(current_line);

        current_line = getLine(src_file);
    }
    printf("*****FINISHED SPREADNING MACROS*****\n");
}

int ReachedEOF(char *txt)
{

    int i = 0, result = 1;
    if (txt == NULL)
        return 1;
    if (txt[i] == END_OF_STRING)
        result = 0;
    while (txt[i] != END_OF_STRING)
    {
        if ((!isspace(txt[i])) && (txt[i] != EOF))
        {
            result = 0;
        }
        i++;
    }
    return result;
}

void copySubstringToFile(FILE *dest_file, char *mystring, int start, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        putc(mystring[i + start], dest_file);
    }
}

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

FILE *createMacroFile(char *file_name)
{
    char *am_file_name;
    FILE *am_file = NULL;
    am_file_name = (char *)malloc((strlen(file_name) + 4) * sizeof(char)); /*Create .am file name*/
    memcpy(am_file_name, file_name, strlen(file_name));
    memcpy(am_file_name + strlen(file_name), &AM_FILE_NAME_ENDING, 4);
    am_file = fopen(am_file_name, "w+");
    if (am_file != NULL)
    {
        printf("successfully created file-->%s<--\n", am_file_name);
    }
    else
    {
        printf("Failed in creating file-->%s<--\n", am_file_name);
    }
    return am_file;
}

void storeMacro(node *LL, char *macro_name, char *macro_body)
{
    if (LL->key == NULL) /*for the first macro*/
    {
        LL->key = macro_name;
        LL->data = macro_body;
    }
    else
    {
        insertnewnode(LL, macro_name, macro_body);
    }
}

void printMacro(FILE *output_file, node *macro)
{
    if (macro != NULL)
    {
        if (macro->data != NULL)
        {
            fprintf(output_file, "%s", (char *)macro->data);
        }
    }
}

node *searchMacro(node *LL, char *key)
{
    if (key == NULL)
        return NULL;
    while (LL != NULL)
    {
        if (LL->key != NULL)
        {
            if (!strcmp(LL->key, key))
            {
                return LL;
            }
            else
            {
                LL = LL->next;
            }
        }
        else
        {
            LL = NULL;
        }
    }
    return NULL;
}

void printAllMacros(node *LL) /*DEBUG*/
{
    while (LL != NULL)
    {
        if (LL->key != NULL)
        {
            printf("Macro key-->%s\nMacro Body-->\n%s<--END BODY\n", LL->key, (char *)LL->data);
        }
        LL = LL->next;
    }
}
