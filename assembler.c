#include "assembler.h"

/*starting point*/
int main(int argc, char **argv)
{

    handleFiles(argc, argv); /*handle all files given in argument list*/

    return 0;
}

/*handles different files in argument list*/
void handleFiles(int argc, char **argv)
{
    int i;
    FILE *mfile;
    char *current_file_path;
    char *as_path;
    for (i = 1; i < argc; i++)
    {
        current_file_path = argv[i];
        as_path = appendString(current_file_path, FILE_ENDING_AS);
        mfile = fopen(as_path, "r");
        if (mfile != NULL)
        {
            runAssembler(mfile, current_file_path);
            fclose(mfile);
        }
        else
        {
            printf("the file --> %s doesnt exist\n", current_file_path);
        }
        free(as_path);
    }
}

/*handle file */
void runAssembler(FILE *file, char *path)
{

    Assembler_mem *mem;
    FILE *macro_file;
    deleteOutputFiles(path);
    fseek(file, 0, SEEK_SET);
    macro_file = macroStage(file, path);

    mem = InitAssemblerMem();
    mem->file_name = path;
    assemblerFirstPass(macro_file, mem); /*first pass collects all label data and seraches for all possible errors*/

    if (mem->no_Errors == TRUE) /*if first pass is succesful and there are no errors then start second phase for translating*/
    {
        assemblerSecondPass(macro_file, mem);
        finalStage(mem);
    }

    printf("\n\n\n translated to->\n%s\n\n<-", mem->String_Image);
    extLabelsDebug(mem->ext_file_table);
    printLables(mem->label_Table);

    freeAssemblerMem(mem);
}

/*deletes output file of previous assembling if exists*/
void deleteOutputFiles(char *path)
{
    char *new_file_name;

    new_file_name = appendString(path, FILE_ENDING_AM); /*delete the old .am file*/
    deleteFileIfExists(new_file_name);
    free(new_file_name);

    new_file_name = appendString(path, FILE_ENDING_ENT); /*delete the old .ent file*/
    deleteFileIfExists(new_file_name);
    free(new_file_name);

    new_file_name = appendString(path, FILE_ENDING_EXT); /*delete the old .ext file*/
    deleteFileIfExists(new_file_name);
    free(new_file_name);

    new_file_name = appendString(path, FILE_ENDING_OB); /*delete the old .ob file*/
    deleteFileIfExists(new_file_name);
    free(new_file_name);
}
