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
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
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
                        }
                    }
                }
            }
            free(param);
        }
        else
        {
            isGoodLine = FALSE;
        }

        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    printf("is Good command syntax:%d\n", isGoodLine);
    if (!isGoodLine)
        mem->no_Errors = FALSE;
}

void CMPcountLines(char *str, Assembler_mem *mem)
{
    int isGoodLine = TRUE;
    int lineCounter = 2; /*minmum lines for command with params*/
    char *trimmed_str = NULL;
    char *param = NULL;
    printf("CMPountLines string->%s<-\n", str);

    if (mem->no_Errors == TRUE && str != NULL && !isOnlyWhiteChars(str))
    {

        isGoodLine = TRUE;
        trimmed_str = trimAll(str);

        if (checkResidualText(trimmed_str)) /**/
        {
            isGoodLine = FALSE;
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
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
        }

        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    printf("is Good command syntax:%d\n", isGoodLine);
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
    printf("LEAcountLines string->%s<-\n", str);

    if (mem->no_Errors == TRUE && str != NULL && !isOnlyWhiteChars(str))
    {

        isGoodLine = TRUE;
        trimmed_str = trimAll(str);

        if (checkResidualText(trimmed_str)) /**/
        {
            isGoodLine = FALSE;
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
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
                        }
                    }
                }
            }
            free(param);
        }
        else
        {
            isGoodLine = FALSE;
        }

        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    printf("is Good command syntax:%d\n", isGoodLine);
    if (!isGoodLine)
        mem->no_Errors = FALSE;
}
void CLRcountLines(char *str, Assembler_mem *mem)
{
    int isGoodLine = TRUE;
    int lineCounter = 2; /*minmum lines for command with params*/
    char *trimmed_str = NULL;
    char *param = NULL;
    printf("CMPountLines string->%s<-\n", str);

    if (mem->no_Errors == TRUE && str != NULL && !isOnlyWhiteChars(str))
    {

        isGoodLine = TRUE;
        trimmed_str = trimAll(str);

        if (checkResidualText(trimmed_str)) /**/
        {
            isGoodLine = FALSE;
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
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
                        }
                    }
                }
            }
        }

        free(param);
        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    printf("is Good command syntax:%d\n", isGoodLine);
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
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
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
                }
            }
        }

        free(param);
        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    printf("is Good command syntax:%d\n", isGoodLine);
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

        if (checkResidualText(trimmed_str)) /**/
        {
            isGoodLine = FALSE;
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
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
                    }
                }
            }
        }

        free(param);
        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    printf("is Good command syntax:%d\n", isGoodLine);
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

        if (checkResidualText(trimmed_str)) /**/
        {
            isGoodLine = FALSE;
        }
        if (countCommas(str) != 0 && isGoodLine) /*make sure there arent any commas at start*/
        {
            isGoodLine = FALSE;
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
                        }
                    }
                }
            }
        }

        free(param);
        if (!checkResidualText(trimmed_str)) /*extranious text*/
        {
            isGoodLine = FALSE;
        }

        if (isGoodLine && mem->no_Errors)
            mem->IC += lineCounter;
    }
    printf("is Good command syntax:%d\n", isGoodLine);
    if (!isGoodLine)
        mem->no_Errors = FALSE;
}
void RTScountLines(char *str, Assembler_mem *mem)
{
    if (checkResidualText(str))
        mem->IC++;
}
void STOPcountLines(char *str, Assembler_mem *mem)
{
    RTScountLines(str, mem);
}
