#ifndef FILE_UTILS
#define FILE_UTILS

#include <stdio.h>
#include <stdlib.h>
#include "Text_utils.h"

void deleteFileIfExists(char *path);                       /*gets file name, and deletes it if it exists*/
FILE *CreateFileWithEnding(char *file_name, char *Ending); /*creates a file with the given name and ending*/

#define FILE_ENDING_AS ".as"
#define FILE_ENDING_AM ".am"
#define FILE_ENDING_OB ".ob"
#define FILE_ENDING_EXT ".ext"
#define FILE_ENDING_ENT ".ent"
#endif 