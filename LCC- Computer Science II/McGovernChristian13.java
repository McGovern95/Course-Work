/*
*  A program that loops through a file and outputs a postfix expression
*  
*
* @author: Christian McGovern
* @assignment: ICS 211 Assignment #13
* @date : 2/23/15
*
* */
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class McGovernChristian13 {
   public static void main(String[] commandlineArguments) {
      //Error Checking
      if(commandlineArguments.length == 0){
         System.out.println("Please enter the file name.");
      }
      else{
         McGovernChristian13.readFromTheFile(commandlineArguments[0]);
      }
         
   }		
   
   /**
     * Reads from the file
     * 
     * @param fileName is the name of file    
     */
   public static void readFromTheFile(String fileName) {
         //connect to file 
      File file = new File(fileName);
      Scanner scanFile = null;
      try {
         scanFile = new Scanner(file);
      } 
      catch (FileNotFoundException exception) {
                
         System.out.print("ERROR: File not found for " + fileName);
               
         System.exit(1);
      }        
    
      while (scanFile.hasNextLine()) {
        
         String line = scanFile.nextLine();
        
         String infixLine = McGovernChristian13.infix(line);
         System.out.println(infixLine);
           
            
            
      }
   }
   
   /**
     * makes a infix equation into a postfix equation
     * @param equation is the input string
     * @return a postfix equation     
     */	
   public static String infix(String input){
       
       
       /*
         Input is a string which contains the infix integer expression
         Loop from the 0th position to the last position in the input string
         Isolate a single character string from the input string
         If the character string is a left parenthesis "(", push it on the stack 
         If the character string is a digit (integer), add it to the end of the output string
         If the character string is an operator (*, /, %, +, -), push it on the stack
         If the character string is a right parenthesis ")", pop each operator off the stack,
          and add each operator to the end of the output string, until you pop a left parenthesis "(" off the stack 
         After looping, the output string is the postfix expression
   
   
       */
     
      StackInterface<String> stack = new ArrayStack<String>();
        
      String output = new String();
         
         
      for(int i=0;i<input.length();i++){
         
         String character = input.substring(i, i+1);
          
          
         	
         if (character.equals("("))  {
            stack.push(character);
             
         }
         
         if (character.equals("0")) {
            output = output + "0";
              
         }
         else if (character.equals("1")) {
            output = output + "1";
          
         }
         else if (character.equals("2")) {
            output = output + "2";
          
         }
         else if (character.equals("3")) {
            output = output + "3";
          
         }
         else if (character.equals("4")) {
            output = output + "4";
          
         }
         else if (character.equals("5")) {
            output = output + "5";
          
         }
         else if (character.equals("6")) {
            output = output + "6";
          
         }
         else if (character.equals("7")) {
            output = output + "7";
          
         }
         else if (character.equals("8")) {
            output = output + "8";
          
         }
         else if (character.equals("9")) {
            output = output + "9";
          
         }
         else if (character.equals("*")) {
            stack.push(character);
         }
         else if (character.equals("/")) {
            stack.push(character);
         }
         else if (character.equals("%")) {
            stack.push(character);
         }
         else if (character.equals("+")) {
            stack.push(character);
         }
         else if (character.equals("-")) {
            stack.push(character);
         }
         else if (character.equals(")")) {
            
            while (!character.equals("(")) {
              
            
            
               output = output + stack.pop();
               
             
                
               
            
               break;
            }
         
         
         }
            
          
      }
         
      return output;
   }  
         
      
        
}   
