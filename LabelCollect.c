#include "LabelCollect.h"

/*returns a list of all labels and if they are normal, extern or entry*/
node *collectAllLabels(FILE *src)
{
    node *label_table;
    label_table = initList();
    collectExternAndNormalLabels(src, label_table);
    collectEntryLabels(src, label_table);
    printLables(label_table);
    return label_table;
}

void collectExternAndNormalLabels(FILE *src, node *label_table)
{
    char *current_line, *current_word;

    printf("********LABEL TEST***********\n");
    fseek(src, 0, SEEK_SET); /*make sure the file stream is at the start*/
    current_line = getLine(src);
    while (current_line != NULL) /*loop through all lines of file and collect entry, data and instruction labels*/
    {
        if (!isCommentLine(current_line) && !isOnlyWhiteChars(current_line))
        {
            printf("\n***PARSING LINE\n->%s\n", current_line);
            current_word = getWordFromLine(current_line); /*get first word in line*/

            if (isLabelDefinition(current_word) || isExternDefinition(current_word)) /*if found a label definition*/
            {
                if (isExternDefinition(current_word)) /*check for .extern labels*/
                {
                    printf("FOUND  .extern-> %s\n", current_word);
                    current_line = extractWordFromStart(current_line);
                    if (current_line != NULL)
                    {
                        free(current_word);
                        current_word = getWordFromLine(current_line); /*get the label name*/
                        printf("label name ->%s<-\n", current_word);
                        if (isGoodLabelName(current_word)) /*if name is good then try store it*/
                        {
                            if (NULL == findNode(label_table, current_word))
                            {
                                printf("SAVING LABEL ->%s\n", current_word);
                                storeLable(label_table, current_word, TRUE, FALSE, UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED);
                            }
                        }
                    }
                }
                else
                {

                    if (isLabelDefinition(current_word)) /*check for normal labels*/
                    {
                        printf("FOUND label %s\n", current_word);
                        current_word[strlen(current_word) - 1] = END_OF_STRING; /*remove the ':' char and check name*/
                        if (isGoodLabelName(current_word))                      /*if name is good then try to store it*/
                        {
                            printf("GOOD Label name\n");
                            if (NULL == findNode(label_table, current_word))
                            {
                                printf("SAVING LABEL ->%s\n", current_word);
                                storeLable(label_table, current_word, FALSE, UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED);
                            }
                        }
                    }

                    else
                    {
                        free(current_word);
                    }
                }
            }
        }
        free(current_line);
        current_line = getLine(src);
    }
    printf("********LABEL TEST END***********\n");
}
void collectEntryLabels(FILE *src, node *label_table)
{
    char *current_line, *current_word;
    fseek(src, 0, SEEK_SET); /*make sure the file stream is at the start*/
    current_line = getLine(src);
    printf("**********collecting entries***********");
    while (current_line != NULL)
    {
        if (!isCommentLine(current_line) && !isOnlyWhiteChars(current_line))
        {
            printf("\n***PARSING LINE\n->%s\n", current_line);
            current_word = getWordFromLine(current_line); /*get first word in line*/
            if (isEntryDefinition(current_word))
            {

                free(current_word);
                current_line = extractWordFromStart(current_line);
                current_word = getWordFromLine(current_line);      /*get the name of entry label*/
                printf("found entry label->%s<-\n", current_word); /*DEBUG*/
                setToEntry(label_table, current_word);
                free(current_word);
            }
            else
            {
                free(current_word);
            }
        }
        free(current_line);
        current_line = getLine(src);
    }
    printf("**********FINSHED COLLECTING ENTRY LABELS**********\n");
}

int isGoodLabelName(char *str)
{
    char *trimmed_str;
    int result = 1;
    int char_counter = 0; /*label name length is max 31 chars*/

    if (str == NULL)
    {
        return 0;
    }
    printf("checking label name->%s<-\n", str);
    trimmed_str = trimAll(str);
    /*make sure that first letter is alphanumeric*/
    if (!isalpha(trimmed_str[char_counter]))
    {
        result = 0;
        printf("bad first letter\n");
    }
    else
    {
        char_counter++;
        /*check that all chars are alphanumeric*/
        while (trimmed_str[char_counter] != END_OF_STRING)
        {
            if (!isalnum(trimmed_str[char_counter]))
                result = 0;
            char_counter++;
        }
        if (char_counter > LABEL_NAME_MAX_LENGTH)
        {
            result = 0;
        }

        if (result)
        {
            result = !isKeyWord(str);
        }

        free(trimmed_str);
    }
    if (result == 0)
        printf("shitty label name\n");
    return result;
}

int isLabelDefinition(char *str) /*checks if it is a 'label:' definition*/
{
    char *trimmed_str;
    int result = 1;
    int char_counter = 0; /*label name length is max 31 chars*/

    if (str == NULL)
    {
        return 0;
    }

    trimmed_str = trimAll(str);
    if (trimmed_str[strlen(trimmed_str) - 1] != LABEL_DECLARATION_END)
    {
        result = 0;
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
            result = returned_label->_attrib_extern;
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
            result = returned_label->_attrib_entry;
        }
    }
    return result;
}

int setToEntry(node *label_table, char *label_name)
{
    node *returned_node;
    Label *returned_label;
    int result = SUCCES;
    printf("***GOTCHA!!!! FOUND ONE!!!!!***");

    returned_node = findNode(label_table, label_name);
    if (returned_node == NULL) /*in case label doesnt exist*/
    {
        result = NO_SUCH_LABEL;
    }
    else
    {

        returned_label = (Label *)returned_node->data;
        if (returned_label->_attrib_entry == TRUE) /*in case the label is extern*/
        {
            result = ALREADY_EXTERN;
        }
        else
        { /*cant be extern and entry*/
            if (returned_label->_attrib_extern != TRUE)
            {
                returned_label->_attrib_entry = TRUE;
            }
            else
            {
                result = ALREADY_EXTERN;
            }
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
        if (returned_label->_attrib_extern != TRUE && returned_label->_label_type == DATA)
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
        if (returned_label->_attrib_extern != TRUE && returned_label->_label_type == INSTRUCTION)
        {
            result = TRUE;
        }
    }
    return result;
}

node *LabelConstructor(char *label_name, int is_extern, int attrib_entry, int label_type, int value, int base_address, int offset)
{
    node *new_node = NULL;
    Label *new_label = NULL;
    if (label_name != NULL)
    {
        new_label = (Label *)malloc(sizeof(Label));
        new_label->_attrib_extern = is_extern;
        new_label->_label_type = label_type;
        new_label->_attrib_entry = attrib_entry;
        new_label->_value = value;
        new_label->_base_address = base_address;
        new_label->_attrib_entry = attrib_entry;
        new_label->_offset = offset;

        new_node = createNode(label_name, new_label);
    }
    return new_node;
}

void storeLable(node *label_table, char *label_name, int is_extern, int attrib_entry, int label_type, int value, int base_address, int offset)
{
    Label *new_label = NULL;
    node *new_node = NULL;
    if (label_table->key == NULL) /*if first in list*/
    {
        if (label_name != NULL) /*if valid name for label*/
        {
            label_table->key = label_name;
            new_label = (Label *)malloc(sizeof(Label));
            new_label->_attrib_extern = is_extern;
            new_label->_label_type = label_type;
            new_label->_attrib_entry = attrib_entry;
            new_label->_value = value;
            new_label->_base_address = base_address;
            new_label->_attrib_entry = attrib_entry;
            new_label->_offset = offset;
            label_table->data = new_label;
        }
    }
    else
    {
        new_node = LabelConstructor(label_name, is_extern, attrib_entry, label_type, value, base_address, offset);
        insertnode(label_table, new_node);
    }
}

void printLables(node *labelTable)
{
    Label *my_label;
    printf("*****printing labels******\n");
    while (labelTable != NULL)
    {
        printf("key ->%s<-\n", labelTable->key);
        my_label = (Label *)labelTable->data;
        printf("isEntry->%d<-\n", my_label->_attrib_entry);
        printf("isExtern->%d<-\n", my_label->_attrib_extern);
        labelTable = labelTable->next;
    }
    printf("***** FINISHED printing labels******");
}

/*checks whether is it a .data def*/
int isDataLabelDefinition(char *str) 
{



}

/*checks whether is it a .string def*/
int isStringLabelDefinition(char *str) {}