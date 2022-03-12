#ifndef TEXT_PARSE_h
#define TEXT_PARSE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum instructions
{
    MOV = 2,
    CMP,
    ADD,
    SUB,
    LEA,
    CLR,
    NOT,
    INC,
    DEC,
    JMP,
    BNE,
    JSR,
    RED,
    PRN,
    RTS,
    STOP
};
int isInstructionName(char *str);
char *getLine(FILE *file);                       /*returns NULL if line only holds EOF or holds nothing*/
char *initString();                              /*creates an empty string - only containing NULL terminator,returns a pointer to that string*/
char *appendString(char *s1, char *s2);          /*appends s2 to s1 and returns new char of appended string, DOES NOT free(s2)*/
char *trimAll(char *text);                       /*trims text and returns NULL if all of text is white spaces*/
char *trimStart(char *text, int amount);         /*trims amount of characters from start of string*/
char *trimEnd(char *text, int amount);           /*trims amount of characters from end of string*/
char *getWordFromLine(char *Line);               /*extract word from start including white spaces at start of word*/
char *getTrimmedWordFromLine(char *Line);        /*gets a fully trimmed word from a string*/
char *extractWordFromStart(char *Line);          /*removes the first word from line and returns the corrected line*/
void appendEndLineChar(char *line);              /*appends \n to given string*/
void appendCharAtEnd(char *line, char toAppend); /*appends char at end of string*/
int compareStrings(char *a, char *b);            /*compares two strings*/
int countCommas(char *);                         /*counts the commas at the start of string*/
void removeComma(char *);                        /*removes first comma in the start of string*/
int checkResidualText(char *);                   /*1 for no resdiual text, 0 for more text*/
int isLastEOF(char *);                           /*checks if line ends with EOF, 1-true \ 0-false*/
int isOnlyWhiteChars(char *);                    /*checks if line is only full of white chars*/
int isOnlyEOF(char *);                           /*checsk if line only holds white chars and EOF*/
int isWhiteChar(char);                           /*checks if char is white space except for \n*/
int isCommentLine(char *line);                   /*returns 1 if its a comment line and 0 if not*/
int isKeyWord(char *str);                        /*checks if string is a preserved word*/
int isRegisterNameInRange(char *str);            /*checks if string is of the expression 'r'+0-15 */

int isGoodLabelName(char *str);
int getIntegerFromText(char *str);      /*get the number from the start of the text*/
int checkIntegerInText(char *str);      /*checks if there is a number in the start of the text*/
void removeIntegerFromText(char *str);  /*replaces all the number digits with space characters*/
int isIntInRange(int myInt);            /*checks if int is a 16-bit number*/
int isExternDefinition(char *str);      /*check if it is an extern label*/
int isEntryDefinition(char *str);       /*check if it is an entry definition*/
int isDataLabelDefinition(char *str);   /*checks whether is it a .data def*/
int isStringLabelDefinition(char *str); /*checks whether is it a .string def*/
int isMacroStart(char *text);           /*checks if word is macro start*/
int isMacroEnd(char *text);             /*checks if word is macro end*/

/*to be tested*/
char *getParam(char *Line);        /*this function returned a trimmed version of the first param in line*/
int isImmediateParam(char *Param); /*checks if recieved param is a of immediate indexing method*/
char *extractParam(char *str);
int isDiractParam(char *Param);
int isIndexParam(char *Param);
int isRegisterDirectParam(char *Param);

/*int isImmediate(char* str){} 
int isDirect(char* str){}
int isIndex(char* str){}
int isRegisterDirect(char* str){}*/

#define TRUE 1
#define FALSE 0
#define PLUS_SIGN '+'
#define MINUS_SIGN '-'
#define QUOTATION_MARK 34
#define DOT_CHAR '.'
#define COMMA_CHAR ','
#define ENDLINE '\n'
#define END_OF_STRING '\0'
#define COMMENT_START ';'
#define SPACE_CHAR ' '
#define NUM_OF_KEYWORDS 22
#define KEY_WORD_MAX_LENGTH 8
#define LABEL_DECLARATION_END ':'
#define LABEL_NAME_MAX_LENGTH 31
#define MACRO_START "macro"
#define MACRO_END "endm"
#define ENTRY_WORD ".entry"
#define EXTERN_WORD ".extern"
#define MAX_INT_SIZE 32767  /*max 16 bit number*/
#define MIN_INT_SIZE -32768 /*min 16 bit number*/

#endif