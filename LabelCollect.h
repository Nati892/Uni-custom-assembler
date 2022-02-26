#ifndef LABELCOLLECT_H
#define LABELCOLLECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Text_parse.h"

enum definition_status
{
    INSTRUCTION = -2,
    DATA = -1,
    FALSE = 0,
    TRUE = 1
};

enum error_code
{
    DOUBLE_LABEL_DEFINITION = -2,
    ALREADY_EXTERN = -1,
    NO_SUCH_LABEL = 0,
    SUCCES = 1
};

typedef struct
{
    /* symbol store in node->key */
    int value;
    int base_address;
    int offset;
    int attrib_extern;
    int attrib_entry;
    int label_type; /*data or instruction*/
} Label;


node *collectAllLabels(FILE *src);
void labelFirstPass(FILE *src, node *label_table);
void labelSecondPass(FILE *src, node *label_table);
int setToEntry(node *label_table, char *label_name);                     /*the function returns error_code as result*/
int isExtern(node *label_table, char *label_name);                       /**/
int isEntry(node *label_table, char *label_name);                        /**/
int isDataLabel(node *label_table, char *label_name);                    /**/
int isInstructionLabel(node *label_table, char *label_name);             /**/
node *LabelConstructor(char *label_name, int is_extern, int label_type); /**/
void storeLable(node *label_table, char *label_name, int is_extern, int label_type);/**/
#endif
/*
create label table with linked list
collect extern and normal label first
and then go for entry labels

check syntax errors
check label errors
*/