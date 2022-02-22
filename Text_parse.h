#ifndef TEXT_PARSE_h
#define TEXT_PARSE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*appends s2 to s1 and returns new char of appended string, DOES NOT free(s2)*/
char *appendString(char *s1, char *s2);

char *trimAll(char *text);               /*trims text and returns NULL if all of text is white spaces*/
char *trimStart(char *text, int amount); /*trims amount of characters from start of string*/
char *trimEnd(char *text, int amount);   /*trims amount of characters from end of string*/

char *getWordFromLine(char *Line);      /*extract word from start including white spaces at start of word*/
char *extractWordFromStart(char *Line); /*removes the first word from line and returns the corrected line*/
void appendEndLineChar(char *line);
int compareStrings(char *a, char *b);

#ifndef parsing_macros

#define ENDLINE '\n'
#define END_OF_STRING '\0'
#define COMMENT_START ';'
#define SPACE_CHAR ' '
#endif

#endif