#ifndef LinkedList_h
#define LinkedList_h

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
 
typedef struct node
{
    char *key;
    void *data;
    struct node *next;
} node;

void insertnewnode(node *list, char *key, void *data);/*insert new node to list, only with data*/
void insertnode(node *list, node *newnode);/*insert node to list*/
node *createNode(char *key, void *data);/*create new node struct object*/
node *findNode(node *list, char *keyToFind);/*find node by key value in list*/
node *deleteNode(node *list, char *);/*delete node in list with only key value*/
void killList(node *list);/*free the entire list*/

/*The use of the delete functions function is only allowed if the data field hold only non-pointer fields*/
/*for lists that have data that hold pointer fields, implement your own delete function to free all memory*/
 
#endif