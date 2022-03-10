#ifndef LABELCOLLECT_H
#define LABELCOLLECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Text_parse.h"
#include "File_utils.h"

enum definition_status
{
    UNDEFINED = -3,
    INSTRUCTION = -2,
    DATA = -1
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
    int _value;
    int _base_address;
    int _offset;
    int _attrib_extern;
    int _attrib_entry;
    int _label_type; /*data or instruction*/
} Label;

/*returns a label-table (linked list of lables), saying which label is entry/extern and/or normal*/
node *collectAllLabels(FILE *src);
void collectExternAndNormalLabels(FILE *src, node *label_table);
void collectEntryLabels(FILE *src, node *label_table);
int setToEntry(node *label_table, char *label_name);         /*the function returns error_code as result*/
int isExtern(node *label_table, char *label_name);           /**/
int isEntry(node *label_table, char *label_name);            /**/
int isDataLabel(node *label_table, char *label_name);        /**/
int isInstructionLabel(node *label_table, char *label_name); /**/
node *LabelConstructor(char *label_name, int is_extern, int attrib_entry, int label_type, int value, int base_address, int offset);
void storeLable(node *label_table, char *label_name, int is_extern, int attrib_entry, int label_type, int value, int base_address, int offset);

/*label related parsing functions*/
int isGoodLabelName(char *str);
int isLabelDefinition(char *str);       /*checks if it is a 'label:' definition*/
int isExternDefinition(char *str);      /*check if it is an extern label*/
int isEntryDefinition(char *str);       /*check if it is an entry definition*/
int isDataLabelDefinition(char *str);   /*checks whether is it a .data def*/
int isStringLabelDefinition(char *str); /*checks whether is it a .string def*/
int calcBaseAddress(int line_num);
int calcOffsetAddress(int line_num);
void printLables(node *labelTable); /*DEBUG*/

#endif
