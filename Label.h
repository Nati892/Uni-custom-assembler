#ifndef LABEL_H
#define LABEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"

enum definition_status
{
    TO_BE_DEFINED = -3,
    EMPTY = -2,
    UNDEFINED = -1
};

typedef struct
{
    char *symbol;
    int value;
    int base_address;
    int offset;
    int attrib_external;
    int attrib_entry;
    int attrib_code; /*change to type and add enum -4,-5*/
    int attrib_data;
} Label;

#endif

/*
create label table with linked list
collect extern and normal label first
and then go for entry labels

add files to makefile
check syntax errors
check label errors


*/