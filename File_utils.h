#ifndef File_utils_h
#define File_utils_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
enum filePosition
{
    REPLACE_LINE = -2,
    END = -1,
    START = 0
};

/*The functions do not handle opening and closing the given file*/
int goToLine(FILE *file, int line_num); /*returns 1 if there is such line and 0 if not*/
int addTextToLine(FILE *file, char *filename, int Line_num, int offset, char *text);

char *getLine(FILE *file);              /*returns NULL if line only holds EOF or holds nothing*/
char *appendString(char *s1, char *s2); /*appends s2 to s1 and returns new char of appended string, DOES NOT free(s2)*/
char *getWord(FILE *file);              /*get word including pre-word white chars, returns null for only white chars*/
char *trimAll(char *text);                 /*trims text and returns NULL if all of text is white spaces*/
char *trimStart(char *text,int amount);/*trims amount of characters from start of string*/
char *trimEnd(char *text,int amount);/*trims amount of characters from end of string*/
char *getTrimmedWord(FILE *file);       /*gets the next word but trimmed!*/
char *getLine(FILE *file);
char *getWordFromLine(char *Line);/*extract word from start including white spaces at start of word*/
char *extractWordFromStart(char *Line);/*removes the first word from line and returns the corrected line*/
void appendEndLineChar(char* line);
int compareStrings(char *a,char *b);

#define TEMP_FILE_NAME "temp"
#define ENDLINE '\n'
#define END_OF_STRING '\0'
#define COMMENT_START ';'
#define SPACE_CHAR ' '
/*#define MY_FREE(A) if(A!=NULL) free(A);*/

#endif