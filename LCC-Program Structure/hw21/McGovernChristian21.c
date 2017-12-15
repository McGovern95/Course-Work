/*
 * Program which demonstrates a linked list
 * @author: Christian McGovern
 * @date: 11/9/15
 * @assignment: ICS 212 #21
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

struct node{
       int data;
       struct node * next;
};

//type definition for "new" data types
typedef struct node Node;
typedef Node * NodePointer;

//prototypes 
void insert(NodePointer *, int);
void printList(NodePointer);
void allSumCountAverage(NodePointer);

int main(void){

   //initialize varaibles 
    NodePointer head = NULL; 
    int item; 
    int i;
    int tNum = 0;

   srand (time(NULL));//generate random seed
   //for having a number of 25 - 75 objects in Linked list
   tNum = (25 + (rand() % 50)); 
     
    for(i = 0;i < tNum;i++){
    item = rand() % 100;
    insert(&head,item);
    }
    printList(head);
    printf("\n");
    allSumCountAverage(head); 
    
    return 0;
}//end of main

void insert(NodePointer *sPtr,int value){

     NodePointer newNode;
     NodePointer previous;
     NodePointer current;
     
     newNode = (NodePointer)malloc(sizeof(Node));
     
     if(newNode != NULL){
        newNode->data = value;
        newNode->next = NULL;


        previous = NULL;
        current =* sPtr;

     while(current != NULL && value > current->data){
             previous = current;
             current = current->next;
        }//end of while
        if(previous == NULL){
             newNode->next =* sPtr;
             *sPtr = newNode;
            }
          else{
           previous->next = newNode;
           newNode->next = current;
          }
   }//end of if(newNode != NULL)
                   
          
}//end of insert();

void printList(NodePointer i){

  printf("The List is:\n");
  while(i != NULL){
       printf("%d, ",i->data);
          i = i->next;
 }//end of while 
 
                                                       
}//end of printList();


void allSumCountAverage(NodePointer i){
  //variables
  double average = 0.0;
  int length = 0;
  int sum = 0;
  
  while(i != NULL){
    
    length++;//counts how many nodes
    sum += i->data;//adds each node 
    i = i->next;//makes i equal to the next node 
    
  }//end of while
  average = sum / (double)length;//calculates average
  
  printf("sum = %d\n", sum);
  printf("count = %d\n", length);
  printf("average = %.2f\n", average);
  
  
}//end of allSumCountAverage();
