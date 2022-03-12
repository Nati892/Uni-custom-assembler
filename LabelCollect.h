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
    UNDEF= -3,
    INSTRUCTION = -2,
    DATA = -1
};


typedef struct
{
    /* symbol store in node->key */ 
    int _value;
    int _base_address;
    int _offset;
    int _attrib_extern;
    int _attrib_entry;
    int _label_type; /*data or instruction*/
} Label;


node *LabelConstructor(char *label_name, int is_extern, int attrib_entry, int label_type, int value, int base_address, int offset);
void storeLable(node *label_table, char *label_name, int is_extern, int attrib_entry, int label_type, int value, int base_address, int offset);

/*label related parsing functions*/
int isLabelDefinition(char *str);       /*checks if it is a 'label:' definition*/
int calcBaseAddress(int line_num);
int calcOffsetAddress(int line_num);
void printLables(node *labelTable); /*DEBUG*/

#endif
