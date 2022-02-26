#include "LabelCollect.h"

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