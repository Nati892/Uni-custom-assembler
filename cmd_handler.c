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
                if (isIndextype1(param))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param))
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
                if (isIndextype1(param))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param))
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
                if (isIndextype1(param))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param))
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
                    if (isIndextype1(param))
                    {
                        lineCounter += INDEX_TYPE_1_NUM_LINES;
                    }
                    else
                    {
                        if (isIndextype2(param))
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
            if (isIndextype1(param))
            {
                lineCounter += INDEX_TYPE_1_NUM_LINES;
            }
            else
            {
                if (isIndextype2(param))
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
                if (isIndextype1(param))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param))
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
                if (isIndextype1(param))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param))
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
            if (isIndextype1(param))
            {
                lineCounter += INDEX_TYPE_1_NUM_LINES;
            }
            else
            {
                if (isIndextype2(param))
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
            if (isIndextype1(param))
            {
                lineCounter += INDEX_TYPE_1_NUM_LINES;
            }
            else
            {
                if (isIndextype2(param))
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

                if (isIndextype1(param))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param))
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
    char firstline[20];
    char secondline[20];
    setARE(firstline,ARE_A);
}
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