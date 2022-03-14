#include "cmd_handler.h"

void MOVcountLines(char *str, Assembler_mem *mem)
{
    int isGoodLine = TRUE;
    int lineCounter = 2; /*minmum lines for command with params*/
    char *trimmed_str = NULL;
    char *param = NULL;

    if (mem->no_Errors == TRUE && str != NULL && !isOnlyWhiteChars(str))
    {

        isGoodLine = TRUE;
        trimmed_str = trimAll(str);

        if (checkResidualText(trimmed_str)) /**/
        {
            isGoodLine = FALSE;
            announceSyntaxError("missing parameter", mem);
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("comma after Instruction name", mem);
        }
        if (isGoodLine) /*get first param*/
        {
            param = getParam(trimmed_str);
            trimmed_str = extractParam(trimmed_str);
            if (isIndextype0(param))
            {
                lineCounter += INDEX_TYPE_0_NUM_LINES;
            }
            else
            {
                if (isIndextype1(param, mem))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, mem))
                    {
                        lineCounter += INDEX_TYPE_2_NUM_LINES;
                    }
                    else
                    {
                        if (isIndextype3(param))
                        {
                            lineCounter += INDEX_TYPE_3_NUM_LINES;
                        }
                        else
                        {
                            isGoodLine = FALSE;
                            announceSyntaxError("Bad parameter", mem);
                        }
                    }
                }
            }
        }

        free(param);
        if (isGoodLine && countCommas(trimmed_str) == 1) /*cehck comma and second param*/
        {
            removeComma(trimmed_str);
            if (checkResidualText(trimmed_str)) /*check if there is a second param after comma*/
            {
                isGoodLine = FALSE;
                announceSyntaxError("missing second parameter", mem);
            }
            else
            {
                param = getParam(trimmed_str);
                trimmed_str = extractParam(trimmed_str);
                if (isIndextype1(param, mem))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, mem))
                    {
                        lineCounter += INDEX_TYPE_2_NUM_LINES;
                    }
                    else
                    {
                        if (isIndextype3(param))
                        {
                            lineCounter += INDEX_TYPE_3_NUM_LINES;
                        }
                        else
                        {
                            isGoodLine = FALSE;
                            announceSyntaxError("Bad paramter", mem);
                        }
                    }
                }
            }
            free(param);
        }
        else
        {
            isGoodLine = FALSE;
            if (countCommas(str) > 1)
            {
                announceSyntaxError("too many commas", mem);
            }
            else
            {
                if (countCommas(str) == 0)
                    announceSyntaxError("missing comma", mem);
            }
        }

        if (!checkResidualText(trimmed_str)) /*extraneous text*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Extraneous text after command", mem);
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    if (!isGoodLine)
        mem->no_Errors = FALSE;
}
void CMPcountLines(char *str, Assembler_mem *mem)
{
    int isGoodLine = TRUE;
    int lineCounter = 2; /*minmum lines for command with params*/
    char *trimmed_str = NULL;
    char *param = NULL;

    if (mem->no_Errors == TRUE && str != NULL && !isOnlyWhiteChars(str))
    {

        isGoodLine = TRUE;
        trimmed_str = trimAll(str);

        if (checkResidualText(trimmed_str)) /*if empty line*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("missing first parameter", mem);
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("comma right after instruction name", mem);
        }
        if (isGoodLine) /*get first param*/
        {
            param = getParam(trimmed_str);
            trimmed_str = extractParam(trimmed_str);
            if (isIndextype0(param))
            {
                lineCounter += INDEX_TYPE_0_NUM_LINES;
            }
            else
            {
                if (isIndextype1(param, mem))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, mem))
                    {
                        lineCounter += INDEX_TYPE_2_NUM_LINES;
                    }
                    else
                    {
                        if (isIndextype3(param))
                        {
                            lineCounter += INDEX_TYPE_3_NUM_LINES;
                        }
                        else
                        {
                            isGoodLine = FALSE;
                            announceSyntaxError("Bad parameter", mem);
                        }
                    }
                }
            }
        }

        free(param);
        if (isGoodLine && countCommas(trimmed_str) == 1) /*cehck comma and second param*/
        {
            removeComma(trimmed_str);
            if (checkResidualText(trimmed_str)) /*check there is a second param after comma*/
            {
                isGoodLine = FALSE;
                announceSyntaxError("Missing second parameter", mem);
            }
            else
            {
                param = getParam(trimmed_str);
                trimmed_str = extractParam(trimmed_str);
                if (isIndextype0(param))
                {
                    lineCounter += INDEX_TYPE_0_NUM_LINES;
                }
                else
                {
                    if (isIndextype1(param, mem))
                    {
                        lineCounter += INDEX_TYPE_1_NUM_LINES;
                    }
                    else
                    {
                        if (isIndextype2(param, mem))
                        {
                            lineCounter += INDEX_TYPE_2_NUM_LINES;
                        }
                        else
                        {
                            if (isIndextype3(param))
                            {
                                lineCounter += INDEX_TYPE_3_NUM_LINES;
                            }
                            else
                            {
                                isGoodLine = FALSE;
                                announceSyntaxError("Bad parameter", mem);
                            }
                        }
                    }
                }
            }
            free(param);
        }
        else
        {
            isGoodLine = FALSE;
            if (countCommas(str) > 1)
            {
                announceSyntaxError("too many commas", mem);
            }
            else
            {
                if (countCommas(str) == 0)
                    announceSyntaxError("missing comma", mem);
            }
        }

        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Extraneous text after command", mem);
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    if (!isGoodLine)
        mem->no_Errors = FALSE;
}
void ADDcountLines(char *str, Assembler_mem *mem)
{
    MOVcountLines(str, mem); /*exactly the same sytax as move*/
}
void SUBcountLines(char *str, Assembler_mem *mem)
{
    MOVcountLines(str, mem); /*exactly the same sytax as move*/
}
void LEAcountLines(char *str, Assembler_mem *mem)
{
    int isGoodLine = TRUE;
    int lineCounter = 2; /*minmum lines for command with params*/
    char *trimmed_str = NULL;
    char *param = NULL;

    if (mem->no_Errors == TRUE && str != NULL && !isOnlyWhiteChars(str))
    {

        isGoodLine = TRUE;
        trimmed_str = trimAll(str);

        if (checkResidualText(trimmed_str)) /**/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Missing first parameter", mem);
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Comma right after Instruction name", mem);
        }
        if (isGoodLine) /*get first param*/
        {
            param = getParam(trimmed_str);
            trimmed_str = extractParam(trimmed_str);
            if (isIndextype1(param, mem))
            {
                lineCounter += INDEX_TYPE_1_NUM_LINES;
            }
            else
            {
                if (isIndextype2(param, mem))
                {
                    lineCounter += INDEX_TYPE_2_NUM_LINES;
                }
                else
                {
                    isGoodLine = FALSE;
                    announceSyntaxError("Bad parameter", mem);
                }
            }
        }

        free(param);
        if (isGoodLine && countCommas(trimmed_str) == 1) /*cehck comma and second param*/
        {
            removeComma(trimmed_str);
            if (checkResidualText(trimmed_str)) /*check there is a second param after comma*/
            {
                isGoodLine = FALSE;
                announceSyntaxError("missing second parameter", mem);
            }
            else
            {
                param = getParam(trimmed_str);
                trimmed_str = extractParam(trimmed_str);
                if (isIndextype1(param, mem))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, mem))
                    {
                        lineCounter += INDEX_TYPE_2_NUM_LINES;
                    }
                    else
                    {
                        if (isIndextype3(param))
                        {
                            lineCounter += INDEX_TYPE_3_NUM_LINES;
                        }
                        else
                        {
                            isGoodLine = FALSE;
                            announceSyntaxError("Bad command", mem);
                        }
                    }
                }
            }
            free(param);
        }
        else
        {
            isGoodLine = FALSE;
            if (countCommas(str) > 1)
            {
                announceSyntaxError("too many commas", mem);
            }
            else
            {
                if (countCommas(str) == 0)
                    announceSyntaxError("missing comma", mem);
            }
        }

        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Extraneous text after command", mem);
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    if (!isGoodLine)
        mem->no_Errors = FALSE;
}
void CLRcountLines(char *str, Assembler_mem *mem)
{
    int isGoodLine = TRUE;
    int lineCounter = 2; /*minmum lines for command with params*/
    char *trimmed_str = NULL;
    char *param = NULL;

    if (mem->no_Errors == TRUE && str != NULL && !isOnlyWhiteChars(str))
    {

        isGoodLine = TRUE;
        trimmed_str = trimAll(str);

        if (checkResidualText(trimmed_str)) /**/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Missing first parameter", mem);
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Comma right after Instruction name", mem);
        }
        if (isGoodLine) /*get first param*/
        {
            param = getParam(trimmed_str);
            trimmed_str = extractParam(trimmed_str);
            if (isIndextype0(param))
            {
                lineCounter += INDEX_TYPE_0_NUM_LINES;
            }
            else
            {
                if (isIndextype1(param, mem))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, mem))
                    {
                        lineCounter += INDEX_TYPE_2_NUM_LINES;
                    }
                    else
                    {
                        if (isIndextype3(param))
                        {
                            lineCounter += INDEX_TYPE_3_NUM_LINES;
                        }
                        else
                        {
                            isGoodLine = FALSE;
                            announceSyntaxError("Bad parameter", mem);
                        }
                    }
                }
            }
        }

        free(param);
        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("extraneous text at end of command", mem);
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    if (!isGoodLine)
        mem->no_Errors = FALSE;
}
void NOTcountLines(char *str, Assembler_mem *mem)
{
    CLRcountLines(str, mem); /*command as the same syntax as CLR*/
}
void INCcountLines(char *str, Assembler_mem *mem)
{
    CLRcountLines(str, mem); /*command as the same syntax as CLR*/
}
void DECcountLines(char *str, Assembler_mem *mem)
{
    CLRcountLines(str, mem); /*command as the same syntax as CLR*/
}
void JMPcountLines(char *str, Assembler_mem *mem)
{
    int isGoodLine = TRUE;
    int lineCounter = 2; /*minmum lines for command with params*/
    char *trimmed_str = NULL;
    char *param = NULL;

    if (mem->no_Errors == TRUE && str != NULL && !isOnlyWhiteChars(str))
    {

        isGoodLine = TRUE;
        trimmed_str = trimAll(str);

        if (checkResidualText(trimmed_str)) /**/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Missing first parameter", mem);
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Comma right after Instruction name", mem);
        }
        if (isGoodLine) /*get first param*/
        {
            param = getParam(trimmed_str);
            trimmed_str = extractParam(trimmed_str);
            if (isIndextype1(param, mem))
            {
                lineCounter += INDEX_TYPE_1_NUM_LINES;
            }
            else
            {
                if (isIndextype2(param, mem))
                {
                    lineCounter += INDEX_TYPE_2_NUM_LINES;
                }
                else
                {
                    isGoodLine = FALSE;
                    announceSyntaxError("Bad parameter", mem);
                }
            }
        }

        free(param);
        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Extraneous text at end of Line", mem);
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    if (!isGoodLine)
        mem->no_Errors = FALSE;
}
void BNEcountLines(char *str, Assembler_mem *mem)
{
    JMPcountLines(str, mem);
}
void JSRcountLines(char *str, Assembler_mem *mem)
{
    JMPcountLines(str, mem);
}
void REDcountLines(char *str, Assembler_mem *mem)
{
    int isGoodLine = TRUE;
    int lineCounter = 2; /*minmum lines for command with params*/
    char *trimmed_str = NULL;
    char *param = NULL;

    if (mem->no_Errors == TRUE && str != NULL && !isOnlyWhiteChars(str))
    {

        isGoodLine = TRUE;
        trimmed_str = trimAll(str);

        if (checkResidualText(trimmed_str)) /*make sure there is a first param*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Missing first param", mem);
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Comma right after Instruction name", mem);
        }
        if (isGoodLine) /*get first param*/
        {
            param = getParam(trimmed_str);
            trimmed_str = extractParam(trimmed_str);
            if (isIndextype1(param, mem))
            {
                lineCounter += INDEX_TYPE_1_NUM_LINES;
            }
            else
            {
                if (isIndextype2(param, mem))
                {
                    lineCounter += INDEX_TYPE_2_NUM_LINES;
                }
                else
                {
                    if (isIndextype3(param))
                    {
                        lineCounter += INDEX_TYPE_3_NUM_LINES;
                    }
                    else
                    {
                        isGoodLine = FALSE;
                        announceSyntaxError("Bad parameter", mem);
                    }
                }
            }
        }

        free(param);
        if (!checkResidualText(trimmed_str)) /*extraneous text*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Extraneous text in end of line", mem);
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    if (!isGoodLine)
        mem->no_Errors = FALSE;
}
void PRNcountLines(char *str, Assembler_mem *mem)
{
    int isGoodLine = TRUE;
    int lineCounter = 2; /*minmum lines for command with params*/
    char *trimmed_str = NULL;
    char *param = NULL;

    if (mem->no_Errors == TRUE && str != NULL && !isOnlyWhiteChars(str))
    {
        isGoodLine = TRUE;
        trimmed_str = trimAll(str);

        if (checkResidualText(trimmed_str)) /*check existence of first param*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Missing first param", mem);
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Commad right after instruction name", mem);
        }
        if (isGoodLine) /*get first param*/
        {
            param = getParam(trimmed_str);
            trimmed_str = extractParam(trimmed_str);
            if (isIndextype0(param))
            {
                lineCounter += INDEX_TYPE_0_NUM_LINES;
            }
            else
            {

                if (isIndextype1(param, mem))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, mem))
                    {
                        lineCounter += INDEX_TYPE_2_NUM_LINES;
                    }
                    else
                    {
                        if (isIndextype3(param))
                        {
                            lineCounter += INDEX_TYPE_3_NUM_LINES;
                        }
                        else
                        {
                            isGoodLine = FALSE;
                            announceSyntaxError("Bad command", mem);
                        }
                    }
                }
            }
        }

        free(param);
        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
            announceSyntaxError("Extraneous text at end of line", mem);
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    if (!isGoodLine)
        mem->no_Errors = FALSE;
}
void RTScountLines(char *str, Assembler_mem *mem)
{
    if (checkResidualText(str))
        mem->IC++;
    else
    {
        announceSyntaxError("Extraneous text at end of line", mem);
    }
}
void STOPcountLines(char *str, Assembler_mem *mem)
{
    RTScountLines(str, mem);
}

void MOVtranslate(char *str, Assembler_mem *mem)
{
    printf("MOVtranslate started with ->%s<-\n", str);
    char firstline[20];
    char secondline[20];
    char *command_image, *ParamLines, *trimmed_str, *param;
    int i;
    for (i = 0; i < 20; i++) /*set both lines to all '0' chars*/
    {
        firstline[i] = '0';
        secondline[i] = '0';
    }
    ParamLines = initString();
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, MOV_OPCODE);
    setField_Funct(secondline, NO_FUNCT);
    trimmed_str = trimAll(str);

    param = getParam(trimmed_str); /*handle first param*/
    if (isIndextype0(param))
    {
        translateForIndex0(param, ParamLines, secondline, SRC, mem);
    }
    else
    {
        if (isIndextype1(param, mem))
        {
            translateForIndex1(param, ParamLines, secondline, SRC, mem);
        }
        else
        {
            if (isIndextype2(param, mem))
            {
                translateForIndex2(param, ParamLines, secondline, SRC, mem);
            }
            else
            {
                if (isIndextype3(param))
                {
                    translateForIndex3(param, ParamLines, secondline, SRC, mem);
                }
            }
        }
    }

    free(param);

    trimmed_str = extractParam(trimmed_str); /*remove comma in middle*/
    removeComma(trimmed_str);

    param = getParam(trimmed_str); /*handle second param*/
    if (isIndextype1(param, mem))
    {
        translateForIndex0(param, ParamLines, secondline, DST, mem);
    }
    else
    {
        if (isIndextype2(param, mem))
        {
            translateForIndex1(param, ParamLines, secondline, DST, mem);
        }
        else
        {
            if (isIndextype3(param))
            {
                translateForIndex2(param, ParamLines, secondline, DST, mem);
            }
        }
    }
    /*check param*/
    free(param);
    free(trimmed_str);
    if (mem->no_Errors)
    {
        command_image = initString();
        strcat(command_image, firstline);
        strcat(command_image, ENDLINE);
        strcat(command_image, secondline);
        strcat(command_image, ENDLINE);
        strcat(command_image, ParamLines);
        strcat(command_image, ENDLINE);
        strcat(mem->String_Image, command_image);
        strcat(mem->String_Image, ENDLINE);
        free(command_image);
    }
    printf("MOVtranslate done\n");
}
void CMPtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, CMP_OPCODE);
    setField_Funct(secondline, NO_FUNCT);
}
void ADDtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, ADD_OPCODE);
    setField_Funct(secondline, ADD_FUNCT);
}
void SUBtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, SUB_OPCODE);
    setField_Funct(secondline, SUB_FUNCT);
}
void LEAtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, LEA_OPCODE);
    setField_Funct(secondline, NO_FUNCT);
}
void CLRtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, CLR_OPCODE);
    setField_Funct(secondline, CLR_FUNCT);
}
void NOTtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, NOT_OPCODE);
    setField_Funct(secondline, NOT_FUNCT);
}
void INCtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, INC_OPCODE);
    setField_Funct(secondline, INC_FUNCT);
}
void DECtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, DEC_OPCODE);
    setField_Funct(secondline, DEC_FUNCT);
}
void JMPtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, JMP_OPCODE);
    setField_Funct(secondline, JMP_FUNCT);
}
void BNEtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, BNE_OPCODE);
    setField_Funct(secondline, BNE_FUNCT);
}
void JSRtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, JSR_OPCODE);
    setField_Funct(secondline, JSR_FUNCT);
}
void REDtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, RED_OPCODE);
    setField_Funct(secondline, NO_FUNCT);
}
void PRNtranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char secondline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setARE(secondline, ARE_A);
    setField_Opcode(firstline, PRN_OPCODE);
    setField_Funct(secondline, NO_FUNCT);
}
void RTStranslate(char *str, Assembler_mem *mem)
{
    char firstline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setField_Opcode(firstline, RTS_OPCODE);
}
void STOPtranslate(char *str, Assembler_mem *mem)

{
    char firstline[20];
    char *command_image;
    setARE(firstline, ARE_A);
    setField_Opcode(firstline, STOP_OPCODE);
}

void translateForIndex0(char *param, char *ParamLines, char *secondline, int reg, Assembler_mem *mem)
{
}
void translateForIndex1(char *param, char *ParamLines, char *secondline, int reg, Assembler_mem *mem) {}
void translateForIndex2(char *param, char *ParamLines, char *secondline, int reg, Assembler_mem *mem) {}
void translateForIndex3(char *param, char *ParamLines, char *secondline, int reg, Assembler_mem *mem) {}