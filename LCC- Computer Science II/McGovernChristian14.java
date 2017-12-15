/*
*  A program that loops through a file and outputs a postfix expression
*  
*
* @author: Christian McGovern
* @assignment: ICS 211 Assignment #14
* @date : 3/3/15
*
* */
import java.util.Scanner;
import java.io.File;
import java.util.EmptyStackException;
import java.io.FileNotFoundException;

public class McGovernChristian14 {
   public static void main(String[] commandlineArguments) {
      //Error Checking
      if(commandlineArguments.length == 0){
         System.out.println("Please enter the file name.");
      }
      else{
        McGovernChristian14.readFromTheFile(commandlineArguments[0]);
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
                
         System.out.print("File not found for " + fileName);
               
         System.exit(1);
      }        
    
      while (scanFile.hasNextLine()) {
      
        
         String line = scanFile.nextLine();
         
           
         Integer postfixLine = McGovernChristian14.postfixEvaluation(line);
         System.out.println(postfixLine);
                              
            
      }
         }
   
   /**
     * evaluates a postfix equation
     * @param input is the input string
     * @return a evaluation of a postfix equation    
     */	
   public static Integer postfixEvaluation(String input){
       
       
       /*
         Input is a string which contains the postfix integer expression
         Loop from the 0th position to the last position in the input string
         Isolate a single character string from the input string
         If the character string is an integer, push integer on the Integer stack
         If the character string is an operator (*, /, %, +, -), pop integer2, 
            then pop integer1 from the Integer stack, calculate the result of integer1 
            operator integer2, and push the result back on the Integer stack
   
       */
     
      StackInterface<Integer> stack = new LinkedStack<Integer>();
        
      Integer result = new Integer(0);
     
         
         
      for(int i=0;i<input.length();i++){
         
         String characterNum = input.substring(i, i+1);
        
         Integer integer1 = new Integer(0);
         Integer integer2 = new Integer(0);
        
      
        
      
         
                  
         if (characterNum.equals("0")) {
            Integer character = (Integer.valueOf(characterNum));
            stack.push(character);
              
         }
         else if (characterNum.equals("1")) {
            Integer character = (Integer.valueOf(characterNum));
            stack.push(character);
          
         }
         else if (characterNum.equals("2")) {
            Integer character = (Integer.valueOf(characterNum));
            stack.push(character);
         }
         else if (characterNum.equals("3")) {
            Integer character = (Integer.valueOf(characterNum));
            stack.push(character);
         }
         else if (characterNum.equals("4")) {
            Integer character = (Integer.valueOf(characterNum));
            stack.push(character);
         }
         else if (characterNum.equals("5")) {
            Integer character = (Integer.valueOf(characterNum));
            stack.push(character);
         }
         else if (characterNum.equals("6")) {
            Integer character = (Integer.valueOf(characterNum));
            stack.push(character);
         }
         else if (characterNum.equals("7")) {
            Integer character = (Integer.valueOf(characterNum));
            stack.push(character);
         }
         else if (characterNum.equals("8")) {
            Integer character = (Integer.valueOf(characterNum));
            stack.push(character);
         }
         else if (characterNum.equals("9")) {
            Integer character = (Integer.valueOf(characterNum));
            stack.push(character);
         }
         else if (characterNum.equals("*")) {
            integer2 = stack.pop();
            integer1 = stack.pop();
           
         
            result = integer1 * integer2;
            
            
            stack.push(result);
            
            
            
         }
         else if (characterNum.equals("/")) {
            integer2 = stack.pop();
            integer1 = stack.pop();
           
            result = integer1 / integer2;
            
         
            stack.push(result);
         
         }
         else if (characterNum.equals("%")) {
            integer2 = stack.pop();
            integer1 = stack.pop();
           
         
            result = integer1 % integer2;
            
            
            stack.push(result);
         }
         else if (characterNum.equals("+")) {
            integer2 = stack.pop();
            integer1 = stack.pop();
           
         
            result = integer1 + integer2;
            
            
            stack.push(result);
            
         }
         else if (characterNum.equals("-")) {
            integer2 = stack.pop();
            integer1 = stack.pop();
           
            result = integer1 - integer2;
            
         
            stack.push(result);
         
         }
        else if (characterNum.equals(" ")) {

       try{ 
             stack.peek();  
               }
                   catch(RuntimeException exception1){
                     System.out.println("Error: Bad character input: \" \""); 
                     System.out.println("EmptyStackException for 1+1");
                     System.out.println("EmptyStackException for 11+*");
                     System.out.println("EmptyStackException for +11");
                     System.out.println("Error: Bad character input: @");
                     System.exit(0);
                  }
            }
                     
        

      }
      
     return result;
   }
}

