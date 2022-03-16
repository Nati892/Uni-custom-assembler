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
                if (isIndextype1(param, NULL))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, NULL))
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
                if (isIndextype1(param, NULL))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, NULL))
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
            if (isGoodLine)
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
        }

        if (!checkResidualText(trimmed_str) && isGoodLine) /*extraneous text*/
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
                if (isIndextype1(param, NULL))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, NULL))
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
                    if (isIndextype1(param, NULL))
                    {
                        lineCounter += INDEX_TYPE_1_NUM_LINES;
                    }
                    else
                    {
                        if (isIndextype2(param, NULL))
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
            if (isIndextype1(param, NULL))
            {
                lineCounter += INDEX_TYPE_1_NUM_LINES;
            }
            else
            {
                if (isIndextype2(param, NULL))
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
                if (isIndextype1(param, NULL))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, NULL))
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
                if (isIndextype1(param, NULL))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, NULL))
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
            if (isIndextype1(param, NULL))
            {
                lineCounter += INDEX_TYPE_1_NUM_LINES;
            }
            else
            {
                if (isIndextype2(param, NULL))
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
            if (isIndextype1(param, NULL))
            {
                lineCounter += INDEX_TYPE_1_NUM_LINES;
            }
            else
            {
                if (isIndextype2(param, NULL))
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

                if (isIndextype1(param, NULL))
                {
                    lineCounter += INDEX_TYPE_1_NUM_LINES;
                }
                else
                {
                    if (isIndextype2(param, NULL))
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
    char firstline[21];
    char secondline[21];
    char *command_image,   /*end command image*/
        *firstParamLines,  /*lines added by first param*/
        *secondParamLines, /*lines added by second param*/
        *trimmed_str,
        *param;
    int i;
    mem->IC += 2;
    for (i = 0; i < 20; i++) /*set both lines to all '0' chars*/
    {
        firstline[i] = '0';
        secondline[i] = '0';
    }
    firstline[20] = END_OF_STRING;
    secondline[20] = END_OF_STRING;

    firstParamLines = initString();
    secondParamLines = initString();

    setField_ARE(firstline, ARE_A); /*EDIT*/
    setField_ARE(secondline, ARE_A);
    setField_Opcode(firstline, MOV_OPCODE);
    setField_Funct(secondline, NO_FUNCT);
    trimmed_str = trimAll(str);

    param = getParam(trimmed_str); /*handle first param*/
    if (isIndextype0(param))
    {
        firstParamLines = translateForIndex0(param, secondline, SRC);
        mem->IC++;
    }
    else
    {
        if (isIndextype1(param, mem))
        {
            firstParamLines = translateForIndex1(param, secondline, SRC, mem);
            mem->IC += 2;
        }
        else
        {
            if (isIndextype2(param, mem))
            {

                firstParamLines = translateForIndex2(param, secondline, SRC, mem);
                mem->IC += 2;
            }
            else
            {
                if (isIndextype3(param))
                {

                    translateForIndex3(param, secondline, SRC);
                    free(firstParamLines);
                    firstParamLines = NULL;
                }
            }
        }
    }

    free(param);

    trimmed_str = extractParam(trimmed_str); /*remove comma in middle*/
    removeComma(trimmed_str);

    param = getParam(trimmed_str); /*handle second param*/
    printf("start second param handling with ->%s<-\n", param);

    if (isIndextype1(param, mem))
    {
        secondParamLines = translateForIndex1(param, secondline, DST, mem);
        mem->IC += 2;
    }
    else
    {
        if (isIndextype2(param, mem))
        {
            secondParamLines = translateForIndex2(param, secondline, DST, mem);
            mem->IC += 2;
        }
        else
        {
            if (isIndextype3(param))
            {
                translateForIndex3(param, secondline, DST);
                free(secondParamLines);
                secondParamLines = NULL;
            }
        }
    }
    printf("end second param handling\n");

    /*check param*/
    free(param);
    free(trimmed_str);
    command_image = initString();
    command_image = appendStringAndFreeFirst(command_image, firstline);
    command_image = appendStringAndFreeFirst(command_image, "\n");
    command_image = appendStringAndFreeFirst(command_image, secondline);
    command_image = appendStringAndFreeFirst(command_image, "\n");
    if (firstParamLines != NULL)
    {
        command_image = appendStringAndFreeBoth(command_image, firstParamLines);
    }
    if (secondParamLines != NULL)
    {
        command_image = appendStringAndFreeBoth(command_image, secondParamLines);
    }
    mem->String_Image = appendStringAndFreeBoth(mem->String_Image, command_image);

    printf("MOVtranslate done\n");
}

void CMPtranslate(char *str, Assembler_mem *mem)
{
    printf("CMPtranslate started with ->%s<-\n", str);
    char firstline[21];
    char secondline[21];
    char *command_image,   /*end command image*/
        *firstParamLines,  /*lines added by first param*/
        *secondParamLines, /*lines added by second param*/
        *trimmed_str,
        *param;
    int i;
    mem->IC += 2;
    for (i = 0; i < 20; i++) /*set both lines to all '0' chars*/
    {
        firstline[i] = '0';
        secondline[i] = '0';
    }
    firstline[20] = END_OF_STRING;
    secondline[20] = END_OF_STRING;

    firstParamLines = initString();
    secondParamLines = initString();

    setField_ARE(firstline, ARE_A);
    setField_ARE(secondline, ARE_A);
    setField_Opcode(firstline, CMP_OPCODE); /*EDIT*/
    setField_Funct(secondline, NO_FUNCT);
    trimmed_str = trimAll(str);

    param = getParam(trimmed_str); /*handle first param*/
    if (isIndextype0(param))
    {
        firstParamLines = translateForIndex0(param, secondline, SRC);
        mem->IC++;
    }
    else
    {
        if (isIndextype1(param, mem))
        {
            firstParamLines = translateForIndex1(param, secondline, SRC, mem);
            mem->IC += 2;
        }
        else
        {
            if (isIndextype2(param, mem))
            {

                firstParamLines = translateForIndex2(param, secondline, SRC, mem);
                mem->IC += 2;
            }
            else
            {
                if (isIndextype3(param))
                {

                    translateForIndex3(param, secondline, SRC);
                    free(firstParamLines);
                    firstParamLines = NULL;
                }
            }
        }
    }

    free(param);

    trimmed_str = extractParam(trimmed_str); /*remove comma in middle*/
    removeComma(trimmed_str);

    param = getParam(trimmed_str); /*handle second param*/
    printf("start second param handling with ->%s<-\n", param);
    if (isIndextype0(param))
    {
        secondParamLines = translateForIndex0(param, secondline, DST);
        mem->IC++;
    }
    else
    {
        if (isIndextype1(param, mem))
        {
            secondParamLines = translateForIndex1(param, secondline, DST, mem);
            mem->IC += 2;
        }
        else
        {
            if (isIndextype2(param, mem))
            {
                secondParamLines = translateForIndex2(param, secondline, DST, mem);
                mem->IC += 2;
            }
            else
            {
                if (isIndextype3(param))
                {
                    translateForIndex3(param, secondline, DST);
                    free(secondParamLines);
                    secondParamLines = NULL;
                }
            }
        }
    }
    printf("end second param handling\n");

    /*check param*/
    free(param);
    free(trimmed_str);
    command_image = initString();
    command_image = appendStringAndFreeFirst(command_image, firstline);
    command_image = appendStringAndFreeFirst(command_image, "\n");
    command_image = appendStringAndFreeFirst(command_image, secondline);
    command_image = appendStringAndFreeFirst(command_image, "\n");
    if (firstParamLines != NULL)
    {
        command_image = appendStringAndFreeBoth(command_image, firstParamLines);
    }
    if (secondParamLines != NULL)
    {
        command_image = appendStringAndFreeBoth(command_image, secondParamLines);
    }
    mem->String_Image = appendStringAndFreeBoth(mem->String_Image, command_image);

    printf("CMPtranslate done\n");
}
void ADDtranslate(char *str, Assembler_mem *mem)
{
    printf("ADDtranslate started with ->%s<-\n", str);
    char firstline[21];
    char secondline[21];
    char *command_image,   /*end command image*/
        *firstParamLines,  /*lines added by first param*/
        *secondParamLines, /*lines added by second param*/
        *trimmed_str,
        *param;
    int i;
    mem->IC += 2;
    for (i = 0; i < 20; i++) /*set both lines to all '0' chars*/
    {
        firstline[i] = '0';
        secondline[i] = '0';
    }
    firstline[20] = END_OF_STRING;
    secondline[20] = END_OF_STRING;

    firstParamLines = initString();
    secondParamLines = initString();

    setField_ARE(firstline, ARE_A); /*EDIT*/
    setField_ARE(secondline, ARE_A);
    setField_Opcode(firstline, ADD_OPCODE);
    setField_Funct(secondline, ADD_FUNCT);
    trimmed_str = trimAll(str);

    param = getParam(trimmed_str); /*handle first param*/
    if (isIndextype0(param))
    {
        firstParamLines = translateForIndex0(param, secondline, SRC);
        mem->IC++;
    }
    else
    {
        if (isIndextype1(param, mem))
        {
            firstParamLines = translateForIndex1(param, secondline, SRC, mem);
            mem->IC += 2;
        }
        else
        {
            if (isIndextype2(param, mem))
            {

                firstParamLines = translateForIndex2(param, secondline, SRC, mem);
                mem->IC += 2;
            }
            else
            {
                if (isIndextype3(param))
                {

                    translateForIndex3(param, secondline, SRC);
                    free(firstParamLines);
                    firstParamLines = NULL;
                }
            }
        }
    }

    free(param);

    trimmed_str = extractParam(trimmed_str); /*remove comma in middle*/
    removeComma(trimmed_str);

    param = getParam(trimmed_str); /*handle second param*/
    printf("start second param handling with ->%s<-\n", param);

    if (isIndextype1(param, mem))
    {
        secondParamLines = translateForIndex1(param, secondline, DST, mem);
        mem->IC += 2;
    }
    else
    {
        if (isIndextype2(param, mem))
        {
            secondParamLines = translateForIndex2(param, secondline, DST, mem);
            mem->IC += 2;
        }
        else
        {
            if (isIndextype3(param))
            {
                translateForIndex3(param, secondline, DST);
                free(secondParamLines);
                secondParamLines = NULL;
            }
        }
    }
    printf("end second param handling\n");

    /*check param*/
    free(param);
    free(trimmed_str);
    command_image = initString();
    command_image = appendStringAndFreeFirst(command_image, firstline);
    command_image = appendStringAndFreeFirst(command_image, "\n");
    command_image = appendStringAndFreeFirst(command_image, secondline);
    command_image = appendStringAndFreeFirst(command_image, "\n");
    if (firstParamLines != NULL)
    {
        command_image = appendStringAndFreeBoth(command_image, firstParamLines);
    }
    if (secondParamLines != NULL)
    {
        command_image = appendStringAndFreeBoth(command_image, secondParamLines);
    }
    mem->String_Image = appendStringAndFreeBoth(mem->String_Image, command_image);

    printf("ADDtranslate done\n");
}
void SUBtranslate(char *str, Assembler_mem *mem)
{
    printf("SUBtranslate started with ->%s<-\n", str);
    char firstline[21];
    char secondline[21];
    char *command_image,   /*end command image*/
        *firstParamLines,  /*lines added by first param*/
        *secondParamLines, /*lines added by second param*/
        *trimmed_str,
        *param;
    int i;
    mem->IC += 2;
    for (i = 0; i < 20; i++) /*set both lines to all '0' chars*/
    {
        firstline[i] = '0';
        secondline[i] = '0';
    }
    firstline[20] = END_OF_STRING;
    secondline[20] = END_OF_STRING;

    firstParamLines = initString();
    secondParamLines = initString();

    setField_ARE(firstline, ARE_A); /*EDIT*/
    setField_ARE(secondline, ARE_A);
    setField_Opcode(firstline, SUB_OPCODE);
    setField_Funct(secondline, SUB_FUNCT);
    trimmed_str = trimAll(str);

    param = getParam(trimmed_str); /*handle first param*/
    if (isIndextype0(param))
    {
        firstParamLines = translateForIndex0(param, secondline, SRC);
        mem->IC++;
    }
    else
    {
        if (isIndextype1(param, mem))
        {
            firstParamLines = translateForIndex1(param, secondline, SRC, mem);
            mem->IC += 2;
        }
        else
        {
            if (isIndextype2(param, mem))
            {

                firstParamLines = translateForIndex2(param, secondline, SRC, mem);
                mem->IC += 2;
            }
            else
            {
                if (isIndextype3(param))
                {

                    translateForIndex3(param, secondline, SRC);
                    free(firstParamLines);
                    firstParamLines = NULL;
                }
            }
        }
    }

    free(param);

    trimmed_str = extractParam(trimmed_str); /*remove comma in middle*/
    removeComma(trimmed_str);

    param = getParam(trimmed_str); /*handle second param*/
    printf("start second param handling with ->%s<-\n", param);

    if (isIndextype1(param, mem))
    {
        secondParamLines = translateForIndex1(param, secondline, DST, mem);
        mem->IC += 2;
    }
    else
    {
        if (isIndextype2(param, mem))
        {
            secondParamLines = translateForIndex2(param, secondline, DST, mem);
            mem->IC += 2;
        }
        else
        {
            if (isIndextype3(param))
            {
                translateForIndex3(param, secondline, DST);
                free(secondParamLines);
                secondParamLines = NULL;
            }
        }
    }
    printf("end second param handling\n");

    /*check param*/
    free(param);
    free(trimmed_str);
    command_image = initString();
    command_image = appendStringAndFreeFirst(command_image, firstline);
    command_image = appendStringAndFreeFirst(command_image, "\n");
    command_image = appendStringAndFreeFirst(command_image, secondline);
    command_image = appendStringAndFreeFirst(command_image, "\n");
    if (firstParamLines != NULL)
    {
        command_image = appendStringAndFreeBoth(command_image, firstParamLines);
    }
    if (secondParamLines != NULL)
    {
        command_image = appendStringAndFreeBoth(command_image, secondParamLines);
    }
    mem->String_Image = appendStringAndFreeBoth(mem->String_Image, command_image);

    printf("SUBtranslate done\n");
}
void LEAtranslate(char *str, Assembler_mem *mem)
{
}

char *translateForIndex0(char *param, char *secondline, int reg)
{
    char *newline, *trimmedParam;
    int convertedparam;
    printf("translateForIndex0 started with ->%s<-\n", param);
    if (reg == SRC)
    {
        setField_srcReg(secondline, 0);
        setField_srcIndexMethod(secondline, 0);
    }
    else
    {
        setField_dstReg(secondline, 0);
        setField_dstIndexMethod(secondline, 0);
    }
    newline = initDataLine();
    setField_ARE(newline, ARE_A);

    trimmedParam = trimAll(param);
    trimmedParam[0] = SPACE_CHAR;
    convertedparam = atoi(trimmedParam);
    setField_16bitNum(newline, convertedparam);

    free(trimmedParam);
    printf("translateForIndex0 ends\n");
    return (newline);
}
char *translateForIndex1(char *param, char *secondline, int reg, Assembler_mem *mem)
{
    char *newline1, *newline2, *trimmedParam;
    char *ParamLines;
    Label *tempLabel;
    printf("translateForIndex1 started with ->%s<-\n", param);
    ParamLines = initString();
    if (reg == SRC)
    {
        setField_srcReg(secondline, 0);
        setField_srcIndexMethod(secondline, 1);
    }
    else
    {
        setField_dstReg(secondline, 0);
        setField_dstIndexMethod(secondline, 1);
    }
    trimmedParam = trimAll(param);

    newline1 = initDataLine();
    newline2 = initDataLine();

    tempLabel = (Label *)(((node *)findNode(mem->label_Table, trimmedParam))->data); /*set field value*/

    setField_16bitNum(newline1, tempLabel->_base_address);
    setField_16bitNum(newline2, tempLabel->_offset);
    if (tempLabel->_attrib_extern)
    {
        setField_ARE(newline1, ARE_E);
        setField_ARE(newline2, ARE_E);
        saveExternUsedInLine(param, mem);
        /*save extern label usage for the ext file*/
    }
    else
    {
        setField_ARE(newline1, ARE_R);
        setField_ARE(newline2, ARE_R);
    }

    free(trimmedParam);
    newline1 = appendStringAndFreeBoth(newline1, newline2);
    ParamLines = appendStringAndFreeBoth(ParamLines, newline1);

    printf("translateForIndex1 ends\n");
    return (ParamLines);
}
char *translateForIndex2(char *param, char *secondline, int reg, Assembler_mem *mem)
{
    char *newline1, *newline2, *trimmedParam, *label_name, *register_num;
    char *ParamLines;
    Label *tempLabel;
    node *label_node;
    int index = 0, len, i, converted_reg_num;
    printf("translateForIndex2 started with ->%s<-\n", param);

    ParamLines = initString();
    trimmedParam = trimAll(param);
    len = strlen(trimmedParam);
    while (trimmedParam[index] != SQUARE_BRACKET_LEFT) /*find the label before [rXX]*/
    {
        index++;
    }
    label_name = (char *)malloc((index + 1) * sizeof(char));
    label_name[index] = END_OF_STRING;
    for (i = 0; i < index; i++) /*get label name*/
    {
        label_name[i] = trimmedParam[i];
    }
    label_node = findNode(mem->label_Table, label_name);
    tempLabel = (Label *)label_node;

    newline1 = initDataLine();
    newline2 = initDataLine();

    if (tempLabel->_attrib_extern)
    {
        setField_ARE(newline1, ARE_E);
        setField_ARE(newline2, ARE_E);
        saveExternUsedInLine(param, mem);
        /*save extern label usage for the ext file*/
    }
    else
    {
        setField_ARE(newline1, ARE_R);
        setField_ARE(newline2, ARE_R);
    }

    setField_16bitNum(newline1, tempLabel->_base_address);
    setField_16bitNum(newline2, tempLabel->_offset);
    /*Done setting label lines*/
    /*now editing the data first lines*/
    register_num = (char *)malloc(3);
    register_num[2] = END_OF_STRING;
    register_num[1] = trimmedParam[strlen(trimmedParam) - 2];
    register_num[0] = trimmedParam[strlen(trimmedParam) - 3];
    free(trimmedParam);
    converted_reg_num = atoi(register_num);

    if (reg == SRC)
    {

        setField_srcReg(secondline, converted_reg_num);
        setField_srcIndexMethod(secondline, 2);
    }
    else
    {
        setField_dstReg(secondline, converted_reg_num);
        setField_dstIndexMethod(secondline, 2);
    }
    printf("src reg num %d\n", converted_reg_num);
    newline1 = appendStringAndFreeBoth(newline1, newline2);
    ParamLines = appendStringAndFreeBoth(ParamLines, newline1);

    printf("translateForIndex2 ends\n");
    return (ParamLines);
}
void translateForIndex3(char *param, char *secondline, int reg)
{

    char *String_num, *trimmed_param;
    int int_num;
    printf("translateForIndex3 started with ->%s<-\n", param);

    trimmed_param = trimAll(param);

    String_num = (char *)malloc(strlen(trimmed_param) + 1);
    String_num[strlen(trimmed_param)] = END_OF_STRING;

    String_num[0] = trimmed_param[1];

    if (strlen(trimmed_param) == 3) /*in case of two digit reg num*/
    {
        String_num[1] = trimmed_param[2];
    }
    int_num = atoi(String_num);
    if (reg == SRC)
    {
        setField_srcReg(secondline, int_num);
        setField_srcIndexMethod(secondline, 3);
    }
    else
    {
        setField_dstReg(secondline, int_num);
        setField_dstIndexMethod(secondline, 3);
    }

    printf("translateForIndex3 ends\n");
}

void translateCommand(int command, char *str, Assembler_mem *mem)
{

    char firstline[21];
    char secondline[21];
    char *command_image,              /*end command image*/
        *firstParamLines = NULL,      /*lines added by first param*/
            *secondParamLines = NULL, /*lines added by second param*/
                *trimmed_str = NULL,
        *param;
    int i;
    printf("translateCommand starts with command %d, and string ->%s<-\n", command, str);

    for (i = 0; i < 20; i++) /*set both lines to all '0' chars*/
    {
        firstline[i] = '0';
        secondline[i] = '0';
    }
    firstline[20] = END_OF_STRING;
    secondline[20] = END_OF_STRING;

    setField_ARE(firstline, ARE_A); /*set ARE fields of both lines*/
    setField_ARE(secondline, ARE_A);

    setField_ARE(firstline, ARE_A); /*set ARE to A*/
    setField_ARE(secondline, ARE_A);

    mem->IC += 2;
    setField_Opcode(firstline, getOpcode(command)); /*set funct and opcode */

    setField_Funct(secondline, getFunct(command));
    trimmed_str = trimAll(str);
    printf("try\n");
    printf("!@!@#@#!@#@#@ ->%s<-\n", trimmed_str);
    printf("!!!!!!! command %d\n", command);
    if (command == MOV || command == CMP || command == ADD || command == SUB || command == LEA) /*mov,cmp,add,sub,lea*/
    {
        printf("!!!!!!! command %d\n", command);
        printf("translateCommand working on first param\n");
        param = getParam(trimmed_str);
        printf("parm->%s\n", param);
        if (command == MOV || command == CMP || command == ADD || command == SUB)
        {
            if (isIndextype3(param))
            {
                translateForIndex3(param, secondline, SRC);
            }
            else
            {
                if (isIndextype0(param))
                {
                    firstParamLines = initString();
                    firstParamLines = translateForIndex0(param, secondline, SRC);
                    mem->IC++;
                }
            }
        }

        if (isIndextype1(param, mem))
        {
            firstParamLines = initString();
            firstParamLines = translateForIndex1(param, secondline, SRC, mem);
            mem->IC += 2;
        }
        else
        {
            if (isIndextype2(param, mem))
            {
                firstParamLines = initString();
                firstParamLines = translateForIndex2(param, secondline, SRC, mem);
                mem->IC += 2;
            }
        }
        free(param);

        trimmed_str = extractParam(trimmed_str); /*remove comma in middle*/
        removeComma(trimmed_str);
        printf("translateCommand finished working on first param\n");
    } /*done with src operand*/

    printf("translateCommand working on second parammmm->%s<-\n", trimmed_str);
    param = getParam(trimmed_str); /*handle second param*/
    printf("start second param handling with ->%s<-\n", param);
    if (command == CMP || command == PRN) /*for instructions that have index 0 at dst operands*/
    {
        if (isIndextype0(param))
        {
            secondParamLines = initString();
            secondParamLines = translateForIndex0(param, secondline, DST);
            mem->IC++;
        }
    }

    if (command != RTS && command != STOP) /*for instructions that have index type 1,2 for the second operand*/
    {
        if (isIndextype1(param, mem))
        {
            secondParamLines = initString();
            secondParamLines = translateForIndex1(param, secondline, DST, mem);
            mem->IC += 2;
        }
        else
        {
            if (isIndextype2(param, mem))
            {
                secondParamLines = initString();
                secondParamLines = translateForIndex2(param, secondline, DST, mem);
                mem->IC += 2;
            }
        }
    }

    if (command != RTS && command != STOP && command != JMP && command != BNE && command != JSR)
    {

        if (isIndextype3(param))
        {
            translateForIndex3(param, secondline, DST);
        }
    }
    printf("end second param handling\n");
    free(param);

    printf("blat\n");

    printf("double blat\n");
    if (trimmed_str != NULL)
        free(trimmed_str);
    command_image = initString();
    command_image = appendStringAndFreeFirst(command_image, firstline);
    command_image = appendStringAndFreeFirst(command_image, "\n");
    if (command != STOP && command != RTS)
    {
        command_image = appendStringAndFreeFirst(command_image, secondline);
        command_image = appendStringAndFreeFirst(command_image, "\n");
    }
    if (firstParamLines != NULL)
    {
        command_image = appendStringAndFreeBoth(command_image, firstParamLines);
    }
    if (secondParamLines != NULL)
    {
        command_image = appendStringAndFreeBoth(command_image, secondParamLines);
    }
    mem->String_Image = appendStringAndFreeBoth(mem->String_Image, command_image);
    printf("translateCommand ends");
}

int getFunct(int command)
{
    int result;
    switch (command)
    {
    case MOV:
        result = NO_FUNCT;
        break;
    case CMP:
        result = NO_FUNCT;
        break;
    case ADD:
        result = ADD_FUNCT;
        break;
    case SUB:
        result = SUB_FUNCT;
        break;
    case LEA:
        result = NO_FUNCT;
        break;
    case CLR:
        result = CLR_FUNCT;
        break;
    case NOT:
        result = NOT_FUNCT;
        break;
    case INC:
        result = INC_FUNCT;
        break;
    case DEC:
        result = DEC_FUNCT;
        break;
    case JMP:
        result = JMP_FUNCT;
        break;
    case BNE:
        result = BNE_FUNCT;
        break;
    case JSR:
        result = JSR_FUNCT;
        break;
    case RED:
        result = NO_FUNCT;
        break;
    case PRN:
        result = NO_FUNCT;
        break;
    case RTS:
        result = NO_FUNCT;
        break;
    case STOP:
        result = NO_FUNCT;
        break;
    }
    return result;
}
int getOpcode(int command)
{

    int result = 0;
    printf("started get opcode with %d\n", command);
    switch (command)
    {
    case MOV:
        result = MOV_OPCODE;
        break;
    case CMP:
        result = CMP_OPCODE;
        break;
    case ADD:
        result = ADD_OPCODE;
        break;
    case SUB:
        result = SUB_OPCODE;
        break;
    case LEA:
        result = LEA_OPCODE;
        break;
    case CLR:
        result = CLR_OPCODE;
        break;
    case NOT:
        result = NOT_OPCODE;
        break;
    case INC:
        result = INC_OPCODE;
        break;
    case DEC:
        result = DEC_OPCODE;
        break;
    case JMP:
        result = JMP_OPCODE;
        break;
    case BNE:
        result = BNE_OPCODE;
        break;
    case JSR:
        result = JSR_OPCODE;
        break;
    case RED:
        result = RED_OPCODE;
        break;
    case PRN:
        result = PRN_OPCODE;
        break;
    case RTS:
        result = RTS_OPCODE;
        break;
    case STOP:
        result = STOP_OPCODE;
        break;
    }
    printf("finished get opcode\n");
    return result;
}