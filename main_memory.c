#include <stdio.h>
#include <stdlib.h>
#include "main.c"
#include "server.c"

#ifndef MEMORY
#define MEMORY

typedef struct Node{
    struct Student student;    
    struct Node* next;
}node;


void insertAtTail(node* head)
{

}

void deleteFromHead(node* head)
{

}

void addNode(struct Student s)
{
    
    /*
     * Load the line from file and allot a node for it.
     */
}

void removeNode()
{
    /*
     * Write to file and free the memory
     */
}
#endif