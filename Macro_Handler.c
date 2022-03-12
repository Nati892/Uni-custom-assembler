#include "Macro_Handler.h"

/* - assumptions - 
the macros are well defined, no error check is needed.
a macro call cannot have a label before it!*/

void macroStage(FILE *file, char *file_name)
{
    node *LL;
    FILE *am_file;
    LL = initList();
    fseek(file, 0, SEEK_SET); /*make sure the file stream is at the start*/
    collectMacros(file, LL);/*search and save macros from source file*/
    am_file = createMacroFile(file_name);/*create .am file*/
    if (am_file != NULL)/*if .am file created successfully */
    {
        fseek(file, 0, SEEK_SET);/*set both files to the beginning*/
        fseek(am_file, 0, SEEK_SET);
        spreadMacros(file, am_file, LL);/*copy the file contents to .am file and spread the macros*/
        fclose(am_file);
        killList(LL);/*free the list*/
    }
}


void collectMacros(FILE *file, node *LL)
{
    char *line, *macro_key, *macro_body, *temp, *word;
    fseek(file, 0, SEEK_SET);
    line = getLine(file);/*get first line*/

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
                    {/*appends line to macro body*/
                        temp = appendString(macro_body, line);
                        free(macro_body);
                        macro_body = temp;
                        free(line);
                    }
                    /*iterate, get nect line*/
                    line = getLine(file);
                    temp = (trimAll(line));
                }
                insertnewnode(LL, macro_key, macro_body);/*if finished collecting the current macro then save it*/
            }
        }
        free(line);
        line = getLine(file);
    }
  
}


/*this function spreads the text and macros from the src file to dst file*/
void spreadMacros(FILE *src_file, FILE *dest_file, node *LL)
{
    char *current_line, *word = NULL, *temp = NULL;
    node *curr_macro = NULL;
 
    current_line = getLine(src_file);
    while (current_line != NULL)
    {
        if (isCommentLine(current_line)) /*copy comment lines*/
        {
            fprintf(dest_file, "%s", current_line);
        }
        else/*if not comment line*/
        {
            temp = getWordFromLine(current_line);/*get word and check if its a macro*/
            word = trimAll(temp);
            free(temp);

            if (!compareStrings(word, MACRO_START)) /*this part skips the macro declarations*/
            {
                free(word);
                /*get line and first word from line*/
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
            else /*check for macro name appearance - macro calls*/
            {
                temp = getWordFromLine(current_line);
                word = trimAll(temp);
                free(temp);
                curr_macro = findNode(LL, word);

                if (curr_macro != NULL)/*if it is a macro call then print the macro bodo into the dest file*/
                {
                    if (curr_macro->data != NULL)
                        fprintf(dest_file, "%s", (char *)curr_macro->data);
                }

                else/*incase its just a regulat line the copy it*/
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
   
}


/*creates the macro '.am' file */
FILE *createMacroFile(char *file_name)
{
    char *am_file_name;
    FILE *am_file = NULL;

    am_file_name = (char *)malloc((strlen(file_name) + 4) * sizeof(char)); /*Create .am file name*/
    memcpy(am_file_name, file_name, strlen(file_name));/*copy .am ending*/
    memcpy(am_file_name + strlen(file_name), &AM_FILE_NAME_ENDING, 4);
    am_file = fopen(am_file_name, "w+");/*create the file*/
   
    return am_file;
}

