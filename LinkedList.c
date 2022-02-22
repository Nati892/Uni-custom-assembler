#include "LinkedList.h"

void insertnode(node *list, node *newnode)
{
while (list->next!=NULL)
{
    list=list->next;
}
list->next=newnode;

 
}

void insertnewnode(node *list, char *key, void *data)
{
    insertnode(list, createNode(key, data));
}

node *createNode(char *key, void *data)
{
    node *newNode;
    newNode = (node *)malloc(sizeof(node));
    newNode->key = key;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

node *find(node *list, char *keyToFind)
{
    node *current = list;
    while (current != NULL)
    {
        if (!strcmp(current->key, keyToFind))
        {
            return current;
        }
        else
        {
            current = current->next;
        }
        
    }
    return NULL;
}

node *deleteNode(node *list, char *keyToDelete)
{
    node *current; 
    node* prev;
    if (!strcmp(list->key, keyToDelete)) /*case head is it*/
    {
        current = list->next;
        free(list->key);
        free(list->data);
        free(list);
        return (current);
    }
    current = list->next;
    prev = list;
 
    while (current != NULL)
    {
        if (!strcmp(list->key, keyToDelete))
        {
            prev->next = current->next;
            free(current->key);
            free(current->data);
            free(current);
            return list;
        }

        prev = prev->next;
        current = current->next;
    } 
    return list;
}

void killList(node *list)
{
    node *temp;
    node *current=list;
    while (current != NULL)
    {
        temp=current->next;
        free(current->key);
        free(current->data);
        free(current);
        current=temp;
    }
}