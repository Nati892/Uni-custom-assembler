#ifndef File_utils_h
#define File_utils_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



/*These functions DO NOT handle opening and closing the given file parameter*/
int goToLine(FILE *file, int line_num); /*returns 1 if there is such line and 0 if not*/
int addTextToLine(FILE *file, char *filename, int Line_num, int offset, char *text);
char *getLine(FILE *file);              /*returns NULL if line only holds EOF or holds nothing*/
char *getWord(FILE *file);              /*get word including pre-word white chars, returns null for only white chars*/


/*macro definitions*/
#define TEMP_FILE_NAME "temp"

#ifndef parsing_macros
#define ENDLINE '\n'
#define END_OF_STRING '\0'
#define COMMENT_START ';'
#define SPACE_CHAR ' '
#endif

#endif