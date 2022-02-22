#include "LinkedList.h"

/*Gets a node struct as a parameter and inserts it to the given list*/
void insertnode(node *list, node *newnode)
{
while (list->next!=NULL)
{
    list=list->next;
}
list->next=newnode;
}

/*gets node field parameters, creates new node and inserts it to the given list*/
void insertnewnode(node *list, char *key, void *data)
{
    insertnode(list, createNode(key, data));
}


/*creates new node from given data fields*/
node *createNode(char *key, void *data)
{
    node *newNode;
    newNode = (node *)malloc(sizeof(node));
    newNode->key = key;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/*returns node by key value, NULL if there is no match*/
node *findNode(node *LL, char *key)
{
    if (key == NULL)
        return NULL;
    while (LL != NULL)
    {
        if (LL->key != NULL)
        {
            if (!strcmp(LL->key, key))
            {
                return LL;
            }
            else
            {
                LL = LL->next;
            }
        }
        else
        {
            LL = NULL;
        }
    }
    return NULL;
}

/*given a key, the function deletes the node if exists in given list, returns the list's head pointer*/
node *deleteNode(node *list, char *keyToDelete)
{
    node *current; 
    node* prev;
    if (!strcmp(list->key, keyToDelete)) /*case head is to be deleted*/
    {
        current = list->next;
        free(list->key);
        free(list->data);
        free(list);
        return (current);
    }
    current = list->next;
    prev = list;
 

    while (current != NULL)/*search the key in the rest of the list*/
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

/*iterates through the list and frees each node*/
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