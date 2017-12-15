/*
Example of a linked list of integers
*/

#include <stdio.h>
#include <stdlib.h> //has functions malloc() and free()
#include "stringinput.h"
#define MAX 20  //maximum characters in the word
#define QUIT "quit" //end the loop

/*
A self-referential structures contains a pointer 
that points to another structure of the same type
and link together to form dynamic data structures.
data: stores a word (string)
next: is a pointer to the next node
*/
struct node{
   char data[MAX];
   struct node *next;
};

//type definition for "new" data types
typedef struct node Node;
typedef struct node* NodePointer;

//function prototypes 
void insertIntoLinkedList(char [], NodePointer *);
void displayLinkedList(NodePointer);
void deleteFromLinkedList(char [], NodePointer *);

/*
main method - asks the user to enter a word,
and inserts the word into a linked list in alphabetical order, 
and deletes words at the user's request.
*/
int main(){
//stores each word
   char word[MAX]={'\0'};
//stores a pointer to the 1st node in the linked list
   NodePointer head = NULL;
   
//keep inserting until user enters "quit"
   while(0 != strcmp(word, QUIT)){
      printf("Enter a word to INSERT into linked list (enter \"%s\" to quit): ", QUIT);
      getline(word, MAX);
      if(0 != strcmp(word, QUIT)){
      //&head: send the address of the pointer to the 1st node in list
         insertIntoLinkedList(word, &head);
         displayLinkedList(head);
      }
   }//end of while
   
//keep deleting until user enters "quit"
   strncpy(word, "don't quit", MAX);
   printf("\n");
   while(0 != strcmp(word, QUIT) && NULL != head){
      printf("Enter a word to DELETE from linked list (enter \"%s\" to quit): ", QUIT);
      getline(word, MAX);
      if(0 != strcmp(word, QUIT)){
         deleteFromLinkedList(word, &head);
         displayLinkedList(head);
      }
   }
   
   return 0;
}//end of main

/*
Inserts a word in alphabetical order into a linked list
word2: is a string
head2: is the a pointer to the 1st node in a linked list 
This parameter is a pointer to a pointer, 
because we are passing the address of the linked list to the function, 
and the linked list itself is a pointer to the 1st node in the list.
*/
void insertIntoLinkedList(char word2[], NodePointer *head2){
//pointer to a new node to be inserted into linked list
   NodePointer newNode = NULL;
//pointer to the previous node in the linked list
   NodePointer previous = NULL;
//pointer to the current node in the linked list
   NodePointer current = *head2;

//create a node on the heap
   newNode = malloc(sizeof(Node));
/*
check to see if space is available
if no space on heap, malloc() will return NULL
*/
   if(NULL != newNode){
   //copy over word to the node
      strcpy(newNode->data, word2);
   //figure out where to insert in linked list
      while(NULL != current && strcmp(word2, current->data)>0){
      //move previous to current
         previous = current;
      //move current to next node
         current = current->next;
      }//end of while
      //insert at beginning of linked list
      if(NULL == previous){
         newNode->next = current;
         //change the address stored in head
         *head2 = newNode; 
      }//end of if
      else{
      //insert between previous and current
         previous->next = newNode;
         newNode->next = current;
      }//end of else
   }//end of if
}//end of function


//displays the linked list
void displayLinkedList(NodePointer current){
   //for empty list
   if(NULL == current){
      printf("The linked list is empty!\n\n");
      return;
   }
   printf("linked list items: ");
   //loop through list
   while(NULL != current){
   //display each node
      printf("%s, ", current->data);
      //go to next node
      current = current->next;
   }
   printf("\n\n");
}//end of function


/*
Deletes a word from a linked list
word3: is a string
head3: is the a pointer to the 1st node in a linked list 
This parameter is a pointer to a pointer, 
because we are passing the address of the linked list to the function, 
and the linked list itself is a pointer to the 1st node in the list.
*/
void deleteFromLinkedList(char word3[], NodePointer *head3){
//pointer to a temp node to be deleted from linked list
   NodePointer tempNode = NULL;
//pointer to the previous node in the linked list
   NodePointer previous = NULL;
//pointer to the current node in the linked list
   NodePointer current = *head3;

//check for empty list
   if(NULL == current){
      printf("Cannot delete from empty list!\n");
      return;
   }

/*
check to see if 1st node can be deleted
*/
   if(0 == strcmp(word3, current->data)){
   //get address of 1st node
      tempNode = current;
   //change head to next node
      *head3 = current->next;
   //delete the node
      printf("deleting \"%s\" . . .\n", tempNode->data);
      free(tempNode);
   }
   else{
   //loop through linked list
      while(NULL != current && 0 != strcmp(word3, current->data)){
         //printf("current = %s\n", current->data);
      //move to next node in linked list
         previous = current;
         current = current->next;   
      }//end of while
      if(NULL != current){
      //get current node's address and store in tempNode
         tempNode = current;
         //printf("tempNode = %s\n", tempNode->data);
      //skip over current node
         previous->next = current->next;
      //delete node at current pointer
         printf("deleting \"%s\" . . .\n", tempNode->data);
         free(tempNode);
      }//end of if
   }//end of else    
}//end of function
   
