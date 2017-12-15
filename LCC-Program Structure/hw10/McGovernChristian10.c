/*
 * A rock-paper-scissors program demonstrating my own fuctions
 * @author: Christian McGovern
 * @assignment: ICS 212 #10
 * @date: 9/30/15
 *
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>

void ask();//1st funtion
void game();//2nd function
int main(void){
   
   ask();
   printf("This is a Rock-Paper-Scissors game!\n");
   
   printf("Please enter 'r', 'p', 's', for rock, paper, or scissor. To quit use command ^d \n"); 
   game();
  
   return 0;
 
}//end of main
int addrand(int, int);//third funtion
void game(){
 
 
   int rock = 'r';
   int paper = 'p';
   int scissor = 's';
  
   int i;
   
   int num1 = 3;
   int num2 = 1;
  
   int compScore = 0;
   int userScore = 0;
   int choice;
   srand(time(NULL));
  
   
   while(i != EOF){
      choice = getchar();
      
      int computer = addrand(num1, num2);   //addrand();
   //1 is rock, 2 is paper, 3 is scissors
      if(choice == 'r') {
         if(computer == 1){
            printf("rock and a rock is a draw!\n");
         }
         if(computer == 2){
            printf("paper beats rock! Computer wins!\n");
            compScore = compScore + 1;
         
         }
         if(computer == 3){
            printf("Rock beats scissors! You win!\n");
            userScore = userScore + 1;
         
         }
      getchar();
      }//end of rock choice
      
      else if(choice == 'p'){
         if(computer == 1){
            printf("paper beats Rock! you win!\n");
            userScore = userScore + 1;
         }
         if(computer == 2){
            printf("paper and paper! It's a draw!\n");
         
         }
         if(computer == 3){
            printf("scissors beats paper! You lose!\n");
            compScore = compScore + 1;
         
         }
      
      getchar();
      }//end of paper choice
      
      else if(choice == 's'){
         if(computer == 1){
            printf("rock beats scissor! you lose!\n");
            compScore = compScore + 1;
         }
         if(computer == 2){
            printf("scissor beats paper! you win!\n");
            userScore = userScore + 1;
         
         }
         if(computer == 3){
            printf("scissors and scissors! It's a draw!\n");
         
         }
      
      getchar();
      }//end of scissor choice 
      
      
      else if(choice == EOF){
         getchar();
         if(compScore > userScore ){
            printf("Computer wins %d to %d\n",compScore,userScore);
            
            exit(0);
         }
         else if(compScore < userScore ){
            printf("Player wins %d to %d\n",userScore,compScore);
           
            exit(0);
         }
         else if(compScore = userScore ){
            printf("No winner it is a draw!\n");
           
            exit(0);
         }
      
      }//end of EOF if
      
        else{
         getchar();
         printf("ERROR: Enter either 'r', 'p', or 's'.\n");
         
      }
   
   
   }//end of while loop
 
    
   return;
} //end of game

int addrand(int x, int y){
   int z = 0;
   z = rand()%x + y;
   return z;
}

void ask(){
   int choice; 
  
   printf("Do you wanna play Rock-Paper-Scissors? (y/n)\n");
  
   choice = getchar();
  
   if(choice == 'y'){
      printf("great!\n");
    
   }
   else if(choice == 'n'){
      exit(0);
   }
   getchar();
}//end of ask
