#include "LabelCollect.h"

node *collectAllLabels(FILE *src)
{
    node *label_table;
    label_table = initList();
    fseek(src, 0, SEEK_SET); /*make sure the file stream is at the start*/
    collectExternAndNormalLabels(src, label_table);

    return label_table;
}

void collectExternAndNormalLabels(FILE *src, node *label_table)
{
    int label_type, is_extern;
    char *current_line, *current_word, *temp;

    printf("********LABEL TEST***********");
    current_line = getLine(src);
    while (current_line != NULL && !isCommentLine(current_line) && !isOnlyWhiteChars(current_line)) /*loop through all lines of file*/
    {
        printf("parsing line");
        current_word = getWordFromLine(current_line); /*get first word in line*/

        if (isLabelDefinition(current_word) || isExternDefinition(current_word))
        {
            /*DEBUG*/
            if (isLabelDefinition(current_word))
            {
                printf("label:%s\n", current_word);
            }
            if (isExternDefinition(current_word))
            {
                printf(".extern: %s\n", current_word);
            }
        }
        free(current_line);
        current_line = getLine(src);
    }
}

int isLabelDefinition(char *str) /*checks if it is a 'label:' definition*/
{
    char *trimmed_str;
    int result = 1;
    int char_counter = 0; /*label name length is max 31 chars*/

    trimmed_str = trimAll(str);
    /*make sure that first letter is alphanumeric*/
    if (!isalpha(trimmed_str[char_counter]))
    {
        result = 0;
    }
    else
    {
        char_counter++;
        /*check that all chars are alphanumeric*/
        while (trimmed_str[char_counter] != END_OF_STRING && trimmed_str[char_counter] != LABEL_DECLARATION_END)
        {
            if (!isalnum(trimmed_str[char_counter]))
                result = 0;
            char_counter++;
        }
        /*check that label name doesnt exceed max length and that it ends with ':' */
        if (trimmed_str[char_counter] != LABEL_DECLARATION_END || char_counter > LABEL_NAME_MAX_LENGTH)
        {
            result = 0;
        }
        else /*check that there arent any more characters after the ':' definition*/
        {
            char_counter++;
            if (trimmed_str[char_counter] != END_OF_STRING)
            {
                result = 0;
            }
        }
    }
    if (result)
    {
        result = !isKeyWord(str);
    }

    free(trimmed_str);

    return result;
}
int isExternDefinition(char *str) /*check if it is an extern label*/
{
    char *trimmed_str;
    int result = 1;

    trimmed_str = trimAll(str);
    if (strcmp(trimmed_str, EXTERN_WORD))
        result = 0;
    free(trimmed_str);
    return result;
}
int isEntryDefinition(char *str) /*check if it is an entry definition*/
{
    char *trimmed_str;
    int result = 1;

    trimmed_str = trimAll(str);
    if (strcmp(trimmed_str, ENTRY_WORD))
        result = 0;
    free(trimmed_str);
    return result;
}

int isExtern(node *label_table, char *label_name)
{
    node *returned_node;
    Label *returned_label;
    int result = FALSE;

    returned_node = findNode(label_table, label_name);
    if (returned_node != NULL)
    {
        returned_label = (Label *)returned_node->data;
        if (returned_label != NULL)
        {
            result = returned_label->attrib_extern;
        }
    }
    return result;
}

int isEntry(node *label_table, char *label_name)
{

    node *returned_node;
    Label *returned_label;
    int result = FALSE;

    returned_node = findNode(label_table, label_name);
    if (returned_node != NULL)
    {
        returned_label = (Label *)returned_node->data;
        if (returned_label != NULL)
        {
            result = returned_label->attrib_entry;
        }
    }
    return result;
}

int setToEntry(node *label_table, char *label_name)
{
    node *returned_node;
    Label *returned_label;
    int result = SUCCES;

    returned_node = findNode(label_table, label_name);
    if (returned_node == NULL) /*in case label doesnt exist*/
    {
        result = NO_SUCH_LABEL;
    }
    else
    {
        returned_label = (Label *)returned_node->data;
        if (returned_label->attrib_extern) /*in case the label is extern*/
        {
            result = ALREADY_EXTERN;
        }
        else
        {
            returned_label->attrib_extern = TRUE;
        }
    }
    return result;
}

int isDataLabel(node *label_table, char *label_name)
{
    node *returned_node;
    Label *returned_label;
    int result = FALSE;

    returned_node = findNode(label_table, label_name);
    if (returned_node != NULL)
    {
        returned_label = (Label *)returned_node->data;
        if (returned_label->attrib_extern != TRUE && returned_label->label_type == DATA)
        {
            result = TRUE;
        }
    }
    return result;
}

int isInstructionLabel(node *label_table, char *label_name)
{
    node *returned_node;
    Label *returned_label;
    int result = FALSE;

    returned_node = findNode(label_table, label_name);
    if (returned_node != NULL)
    {
        returned_label = (Label *)returned_node->data;
        if (returned_label->attrib_extern != TRUE && returned_label->label_type == INSTRUCTION)
        {
            result = TRUE;
        }
    }
    return result;
}

node *LabelConstructor(char *label_name, int is_extern, int label_type)
{
    node *new_node = NULL;
    Label *new_label = NULL;
    if (label_name != NULL)
    {
        new_label = (Label *)malloc(sizeof(Label));
        new_label->attrib_extern = is_extern;
        new_label->label_type = label_type;
        new_label->attrib_entry = FALSE;
        new_node = createNode(label_name, new_label);
    }
    return new_node;
}

void storeLable(node *label_table, char *label_name, int is_extern, int label_type)
{
    Label *new_label = NULL;
    node *new_node = NULL;
    if (label_table->key == NULL) /*if first in list*/
    {
        if (label_name != NULL) /*if valid name for label*/
        {
            new_label = (Label *)malloc(sizeof(Label));
            new_label->attrib_extern = is_extern;
            new_label->label_type = label_type;
            new_label->attrib_entry = FALSE;
            label_table->data = new_label;
        }
    }
    else
    {
        new_node = LabelConstructor(label_name, is_extern, label_type);
        insertnode(label_table, new_node);
    }
}