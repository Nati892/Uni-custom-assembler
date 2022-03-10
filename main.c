#include "main.h"

int main(int argc, char **argv)
{

    /*handleParams(argc, argv);*/

    /*
    int noErrors = 1;
    char *str;
    char c;
    int temp_int;
    int i = 0;
    str = (char *)malloc(400);
    str[399] = END_OF_STRING;
    c = getchar();
    while (c != '\n' && c != EOF)
    {
        str[i] = c;
        i++;
        c = getchar();
    }
    str[i] = END_OF_STRING;

    printf("got line->%s<-\n", str);*/



    /*
    if (checkIntegerInText(str))
    {
        temp_int = getIntegerFromText(str);
        printf("num:%d  ,base:%d,   offset: %d\n", temp_int, calcBaseAddress(temp_int), calcOffsetAddress(temp_int));
    }*/



    /* if (isOnlyWhiteChars(str))
     {
         printf("blat empty line\n");
         noErrors = FALSE;
     }

     if (checkIntegerInText(str) && noErrors)
     {
         temp_int = getIntegerFromText(str);
         if (!isIntInRange(temp_int))
         {
             printf("BAD NUMBER!\n");
             noErrors = FALSE;
         }
         printf("first num:%d\n", temp_int);
         removeIntegerFromText(str);
         printf("text after removed INT->%s<-\n", str);
     }
     while (!isOnlyWhiteChars(str) && noErrors)
     {
         if (countCommas(str) == 1)
         {
             removeComma(str);
             printf("text after removed commas->%s<-\n", str);
             if (checkIntegerInText(str))
             {
                 temp_int = getIntegerFromText(str);
                 if (!isIntInRange(temp_int))
                 {
                     printf("BAD NUMBER!\n");
                     noErrors = FALSE;
                 }
                 printf("got a char ->%d<-\n", temp_int);
                 removeIntegerFromText(str);
                 printf("text after removed INT->%s<-\n", str);
             }
             else
             {
                 printf("no int after comma\n");
                 noErrors = FALSE;
             }
         }
         else
         {
             if (countCommas(str) == 0)
             {
                 if (!isOnlyWhiteChars(str))
                 {

                     printf("missing comma or extermanious text after .data statement\n");
                     noErrors = FALSE;
                 }
             }
             else
             {

                 printf("too many commas\n");
                 noErrors = FALSE;
             }
         }
     }

     if (noErrors)
         printf("NO ERRORS!\n");
     else
         printf("CRAP ERRORS!\n");*/


         
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
            LabelTester(mfile);
            if (mfile != NULL)
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
    if (file == NULL)
    {
        printf("blat doesnt exit\n");
    }

    else
    {
        goToLine(file, 0);
        macroStage(file, path);
    }
}

void LabelTester(FILE *file)
{
    if (file == NULL)
    {
        printf("Lable Test: blat doesnt exit\n");
    }
    else
    {
        fseek(file, 0, SEEK_SET);
        collectAllLabels(file);
    }
}
