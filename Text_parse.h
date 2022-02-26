#ifndef TEXT_PARSE_h
#define TEXT_PARSE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *appendString(char *s1, char *s2);  /*appends s2 to s1 and returns new char of appended string, DOES NOT free(s2)*/
char *trimAll(char *text);               /*trims text and returns NULL if all of text is white spaces*/
char *trimStart(char *text, int amount); /*trims amount of characters from start of string*/
char *trimEnd(char *text, int amount);   /*trims amount of characters from end of string*/
char *getWordFromLine(char *Line);       /*extract word from start including white spaces at start of word*/
char *extractWordFromStart(char *Line);  /*removes the first word from line and returns the corrected line*/
void appendEndLineChar(char *line);      /*appends \n to given string*/
int compareStrings(char *a, char *b);    /*compares two strings*/
int countCommas(char *);                 /*counts the commas at the start of string*/
void removeComma(char *);                /*removes first comma in the start of string*/
int checkResidualText(char *);           /*1 for no resdiual text, 0 for more text*/
int isLastEOF(char *);                   /*checks if line ends with EOF, 1-true \ 0-false*/
int isOnlyWhiteChars(char *);            /*checks if line is only full of white chars*/
int isOnlyEOF(char *);                   /*checsk if line only holds white chars and EOF*/
int isWhiteChar(char);                   /*checks if char is white space except for \n*/

int isLabelDefinition(char *str);/*checks if it is .extern or a 'label:' definition*/
int checkLabelName(char *str);/*make sure label name is valid*/
int checkLabelType(char *str);/*if it is a Data or instruction*/
int isExternLabel(char *str);/*check if it is an extern label*/
int isEntryDefinition(char *str);/*check if it is an entr definition*/


#ifndef parsing_macros

#define COMMA_CHAR ','
#define ENDLINE '\n'
#define END_OF_STRING '\0'
#define COMMENT_START ';'
#define SPACE_CHAR ' '

#endif

#endif