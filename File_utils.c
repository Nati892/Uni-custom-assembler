#include "File_utils.h"

/*returns a newly created file with the specified filename and ending*/
FILE *CreateFileWithEnding(char *file_name, char *Ending)
{
    FILE *new_file;
    char *new_file_name;
    new_file_name = appendString(file_name, Ending);
    new_file = fopen(new_file_name, "w+"); /*create file with full premission*/
    free(new_file_name);
    return new_file;
}

/*this function deletes a file(name given by param) if it exists*/
void deleteFileIfExists(char *path)
{
    FILE *file_to_del;
    file_to_del = fopen(path, "r"); /*lowest premission just to check existence of file*/
    if (file_to_del != NULL)
    {
        fclose(file_to_del);
        if (remove(path) != 0)
        {
            printf("ERROR: the file %s cannot be deleted, please make sure it is closed in all programs\n", path);
        }
    }
}
