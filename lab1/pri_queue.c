#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;

void PQ_insert(int priority, char * data){
    /*Define placeholder variables to be used in the insert process.
     Node takes the same structure as Node_ptr_t and is dynamically allocated
     memory in the size of Node_t.
     Temp is a mirror copy of the head node and will be used to insert and swap
     nodes.*/
    Node_ptr_t node, temp;
    node = (Node_ptr_t)malloc(sizeof(Node_t));
    node->data = data;
    node->priority = priority;
    temp = head;
    
    /*First check to see if the head value is null*/
    if(head == NULL){
        node->next = NULL;
        head = node;
    }
    /*Second check to see if the priority of node is greater than the existing
     head priority. If so they are swapped*/
    else if(priority > head->priority){
        node->next = head;
        head = node;
    }
    /*Third and final check to find a suitable position for the node to be
     inserted. Scans through the priority queue using a while loop until
     it finds a position and performs a insertion.*/
    else{
        while(temp->next != NULL && priority < temp->next->priority){
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
    
}

Node_ptr_t PQ_delete(){
    /*Defines placeholder nodes to be used in the deletion process. Sets the
     placeholder variable the head, then shifts the head value to its next value.
     Finally, the placeholder variable returns the deleted head value.*/
    Node_ptr_t temp = head;
    head = head->next;
    return temp;
}

Node_ptr_t PQ_get_head(){
    return head;
}

int PQ_get_size(){
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}