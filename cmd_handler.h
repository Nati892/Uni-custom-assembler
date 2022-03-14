#ifndef CMD_HANDLER_H
#define CMD_HANDLER_H

#include <stdio.h>
#include "Text_parse.h"
#include "asm_utils.h"

void MOVcountLines(char *str, Assembler_mem *mem);
void CMPcountLines(char *str, Assembler_mem *mem);
void ADDcountLines(char *str, Assembler_mem *mem);
void SUBcountLines(char *str, Assembler_mem *mem);
void LEAcountLines(char *str, Assembler_mem *mem);
void CLRcountLines(char *str, Assembler_mem *mem);
void NOTcountLines(char *str, Assembler_mem *mem);
void INCcountLines(char *str, Assembler_mem *mem);
void DECcountLines(char *str, Assembler_mem *mem);
void JMPcountLines(char *str, Assembler_mem *mem);
void BNEcountLines(char *str, Assembler_mem *mem);
void JSRcountLines(char *str, Assembler_mem *mem);
void REDcountLines(char *str, Assembler_mem *mem);
void PRNcountLines(char *str, Assembler_mem *mem);
void RTScountLines(char *str, Assembler_mem *mem);
void STOPcountLines(char *str, Assembler_mem *mem);

void MOVtranslate(char *str, Assembler_mem *mem);
void CMPtranslate(char *str, Assembler_mem *mem);
void ADDtranslate(char *str, Assembler_mem *mem);
void SUBtranslate(char *str, Assembler_mem *mem);
void LEAtranslate(char *str, Assembler_mem *mem);
void CLRtranslate(char *str, Assembler_mem *mem);
void NOTtranslate(char *str, Assembler_mem *mem);
void INCtranslate(char *str, Assembler_mem *mem);
void DECtranslate(char *str, Assembler_mem *mem);
void JMPtranslate(char *str, Assembler_mem *mem);
void BNEtranslate(char *str, Assembler_mem *mem);
void JSRtranslate(char *str, Assembler_mem *mem);
void REDtranslate(char *str, Assembler_mem *mem);
void PRNtranslate(char *str, Assembler_mem *mem);
void RTStranslate(char *str, Assembler_mem *mem);
void STOPtranslate(char *str, Assembler_mem *mem);

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