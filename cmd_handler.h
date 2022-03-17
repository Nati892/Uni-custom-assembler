#ifndef CMD_HANDLER_H
#define CMD_HANDLER_H

#include <stdio.h>
#include "Text_parse.h"
#include "asm_utils.h"

void MOVcountLines(char *str, Assembler_mem *mem);  /*count lines for mov Instruction*/
void CMPcountLines(char *str, Assembler_mem *mem);  /*count lines for cmp Instruction*/
void ADDcountLines(char *str, Assembler_mem *mem);  /*count lines for add Instruction*/
void SUBcountLines(char *str, Assembler_mem *mem);  /*count lines for sub Instruction*/
void LEAcountLines(char *str, Assembler_mem *mem);  /*count lines for lea Instruction*/
void CLRcountLines(char *str, Assembler_mem *mem);  /*count lines for clr Instruction*/
void NOTcountLines(char *str, Assembler_mem *mem);  /*count lines for not Instruction*/
void INCcountLines(char *str, Assembler_mem *mem);  /*count lines for inc Instruction*/
void DECcountLines(char *str, Assembler_mem *mem);  /*count lines for dec Instruction*/
void JMPcountLines(char *str, Assembler_mem *mem);  /*count lines for jmp Instruction*/
void BNEcountLines(char *str, Assembler_mem *mem);  /*count lines for bne Instruction*/
void JSRcountLines(char *str, Assembler_mem *mem);  /*count lines for jsr Instruction*/
void REDcountLines(char *str, Assembler_mem *mem);  /*count lines for red Instruction*/
void PRNcountLines(char *str, Assembler_mem *mem);  /*count lines for prn Instruction*/
void RTScountLines(char *str, Assembler_mem *mem);  /*count lines for rts Instruction*/
void STOPcountLines(char *str, Assembler_mem *mem); /*count lines for stop Instruction*/

/*get param and data and translate line param to binary data lines*/
char *translateForIndex0(char *param, char *secondline, int reg);
/*get param and data and translate line param to binary data lines*/
char *translateForIndex1(char *param, char *secondline, int reg, Assembler_mem *mem);
/*get param and data and translate line param to binary data lines*/
char *translateForIndex2(char *param, char *secondline, int reg, Assembler_mem *mem);
/*get param and data and and add that data to the instruction fields*/
void translateForIndex3(char *param, char *secondline, int reg);

/*translate comand to binary and add data to mem->String_image*/
void translateCommand(int command, char *str, Assembler_mem *mem);
/*returns funct field num for specific command*/
int getFunct(int command);
/*returns opcode field num for specific command*/
int getOpcode(int command);

#define INDEX_TYPE_0_NUM_LINES 1
#define INDEX_TYPE_1_NUM_LINES 2
#define INDEX_TYPE_2_NUM_LINES 2
#define INDEX_TYPE_3_NUM_LINES 0

#define MOV_OPCODE 0
#define CMP_OPCODE 1
#define ADD_OPCODE 2
#define SUB_OPCODE 2
#define LEA_OPCODE 4
#define CLR_OPCODE 5
#define NOT_OPCODE 5
#define INC_OPCODE 5
#define DEC_OPCODE 5
#define JMP_OPCODE 9
#define BNE_OPCODE 9
#define JSR_OPCODE 9
#define RED_OPCODE 12
#define PRN_OPCODE 13
#define RTS_OPCODE 14
#define STOP_OPCODE 15

#define ADD_FUNCT 10
#define SUB_FUNCT 11
#define CLR_FUNCT 10
#define NOT_FUNCT 11
#define INC_FUNCT 12
#define DEC_FUNCT 13
#define JMP_FUNCT 10
#define BNE_FUNCT 11
#define JSR_FUNCT 12
#define NO_FUNCT 0

#endif