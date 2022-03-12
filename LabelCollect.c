#include "LabelCollect.h"



int isLabelDefinition(char *str) /*checks if it is a 'label:' definition*/
{
    char *trimmed_str;
    int result = 1;

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

void printLables(node *labelTable) /*DEBUG*/
{
    Label *my_label;
    printf("*****printing labels******\n");
    while (labelTable != NULL)
    {
        if (labelTable->key != NULL)
            printf("\nkey ->%s<-\n", labelTable->key);
        my_label = (Label *)labelTable->data;
        if (my_label != NULL)
        {
            printf("isEntry->%d<-\n", my_label->_attrib_entry);
            printf("isExtern->%d<-\n", my_label->_attrib_extern);
            printf("value->%d<-\n", my_label->_value);
            printf("base ->%d<-\n", my_label->_base_address);
            printf("offset->%d<-\n", my_label->_offset);
            printf("labelType->%d<-\n", my_label->_label_type);
        }
        labelTable = labelTable->next;
    }
    printf("***** FINISHED printing labels******");
}

int calcBaseAddress(int line_num)
{
    return ((line_num / 16) * 16);
}

int calcOffsetAddress(int line_num)
{
    return line_num % 16;
}