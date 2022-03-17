#ifndef ASM_UTILS_H
#define ASM_UTILS_H

#include "LinkedList.h"
#include "Text_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*this struct represents all the memory needed for the assembler to operate*/
typedef struct
{
    int no_Errors;
    int DC;
    int IC;
    int line_counter;
    int *Data_Image; /*int array, both numbers and characters are converted to numbers in the end, so its beter*/
    int Data_Image_Length;
    char *String_Image;
    char *file_name;
    node *label_Table;
    node *ext_labels;
    node *ext_file_table; /*used in second pass*/
} Assembler_mem;

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

enum definition_status
{
    UNDEF = -3,
    INSTRUCTION = -2,
    DATA = -1
};

enum ARE_FIELD
{
    ARE_A,
    ARE_R,
    ARE_E
};

enum REG_TYPE
{
    SRC,
    DST
};

Assembler_mem *InitAssemblerMem();                                             /*starts asm-mem with initial values before first pass*/
void freeAssemblerMem(Assembler_mem *mem);                                     /*frees asm-mem*/
void announceSyntaxError(char *ERR, Assembler_mem *mem);                       /*prints error to screen*/
void announceSyntaxErrorAtLine(char *str, int lineNumber, Assembler_mem *mem); /*prints error to screen with a specific line*/

char *convertIntToBitSizedUnsignedBinary(int num, int BitSize);       /*converts an int to a binary string of a pocked size*/
void setSubStringToBinary(char *str, int num, int start, int finish); /*sets field inside text to a binary num*/
void setField_ARE(char *word, int ARE);                               /*sets ARE value of a given value*/
void setField_Funct(char *line, int num);                             /*sets fucnt field of given string*/
void setField_Opcode(char *line, int num);                            /*sets opcode field of given string*/
void setField_srcReg(char *line, int num);                            /*sets source register field of given string*/
void setField_srcIndexMethod(char *line, int num);                    /*sets source register Index method field of given string*/
void setField_dstReg(char *line, int num);                            /*sets destination register field of given string*/
void setField_dstIndexMethod(char *line, int num);                    /*sets destination register Index method field of given string*/
void setField_16bitNum(char *line, int num);                          /*sets a field with a 16 bit number*/
char *initDataLine();                                                 /*intializes data line with a \n in the end*/

void saveExternUsedInLine(char *label_name, Assembler_mem *mem); /*whe seeing extern label used then saves it to the mem->_extern_file_table*/

int isIndextype0(char *Param);                     /*checks if recieved param is a of immediate indexing method*/
int isIndextype1(char *Param, Assembler_mem *mem); /*checks if the recieved param is an direct indexed param*/
int isIndextype2(char *Param, Assembler_mem *mem); /*checks if the recieved param is an 'Index' indexed param*/
int isIndextype3(char *Param);                     /*checks if the recieved param is an register direct indexed param*/

node *LabelConstructor(char *label_name, int is_extern, int attrib_entry, int label_type, int value, int base_address, int offset);
void storeLable(node *label_table, char *label_name, int is_extern, int attrib_entry, int label_type, int value, int base_address, int offset);

/*label related parsing functions*/
int isLabelDefinition(char *str); /*checks if it is a 'label:' definition*/
int calcBaseAddress(int line_num);
int calcOffsetAddress(int line_num);

#define DATA_WORD_LENGTH 20

#endif