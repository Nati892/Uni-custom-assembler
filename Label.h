#ifndef LABEL_H
#define LABEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Text_parse.h"

enum definition_status
{
    UNDEFINED = -3,
    CODE = -2,
    DATA = -1
};

typedef struct
{
    /* symbol store in node->key */
    int value;
    int base_address;
    int offset;
    int attrib_external;
    int attrib_entry;
    int label_type; /*data or instruction*/
} Label;

#endif

void makeEntry(char *label_name, node *label_table);
int isExtern(char *label_name, node *label_table);
int isEntry(char *label_name, node *label_table);
int isDataLabel(char *label_name, node *label_table);
node *LabelNodeConstructor(char *label_name, int is_extern, int label_type);
void storeLable(node * LL,node *label); 
void freeLabel(node *label);
/*
create label table with linked list
collect extern and normal label first
and then go for entry labels

add files to makefile
check syntax errors
check label errors


*/