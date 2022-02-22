#include "main.h"

int main(int argc, char **argv)
{ 
    handleParams(argc, argv);

    return 0;
}

/*TODELETE*/
void handleParams(int argc, char **argv)
{
    int i;
    FILE *mfile;
    char *current_file_path;
    for (i = 1; i < argc; i++)
    {
        current_file_path = argv[i];
        mfile = fopen(current_file_path, "r");
        if (mfile != NULL)
        {
            printf("the file --> %s exists\n", current_file_path);

            fclose(mfile);

            mfile = fopen(current_file_path, "r+");

            doSomthingToFile(mfile, current_file_path);
            if(mfile!=NULL)
            fclose(mfile); 
        }
        else
        {
            printf("the file --> %s doesnt exist\n", current_file_path);
        }
    }
}

/*TODELETE*/

void doSomthingToFile(FILE *file, char *path)
{
    int i;
    char *s1, *s2, *s3;

    if (file == NULL)
    {
        printf("blat doesnt exit\n");
    }

    else
    {
        goToLine(file, 0);
        macroStage(file,path);
    }

   
}
