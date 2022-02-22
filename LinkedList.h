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

void insertnewnode(node *list, char *key, void *data);
void insertnode(node *list, node *newnode);
node *createNode(char *key, void *data);
node *findNode(node *list, char *keyToFind);
/*The use of the delete functions function is only allowed if the data field hold only non-pointer fields*/
/*for lists that have data that hold pointer fields, implement your own delete function to free all memory*/
node *deleteNode(node *list, char *);
void killList(node *list);
 


#endif