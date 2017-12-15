/*
* application which executes 5 recursive methods 
*  
*
* @author: Christian McGovern
* @assignment: ICS 211 Assignment #7
* @date : 2/3/15
*
* */

   public class McGovernChristian7 {
   
 /*
 * main() method which starts the program
 *
 * @parem commandlineArgument is the number inputed to test the recursive methods
 *
 **/
    public static void main(String[] commandlineArguments) {
      if (commandlineArguments.length <= 1) {
        System.out.println("Please enter a least two commandlines!");
       } 
      else {
            int number = new Integer(0);
            String text = commandlineArguments[1];
      //error checking to see if first Integer is an integer
      try {
        
        number = Integer.parseInt(commandlineArguments[0]);
      }
      catch (NumberFormatException exception1) {
        System.out.print(exception1);
        System.out.println(" is not an integer.");
        System.exit(1); // ends the program
      }
      //error-checking for a negative number
       int negative = 0;
       negative = McGovernChristian7.iterative(number);
            
        if (negative < 0) {
        System.out.println("do not enter a negative number!");
        System.exit(1); // ends the program
      }
     
     String method1 = repeat(number, text);// return address for repeat
     System.out.println(method1);   
     
     String method2 = firstLetter(number, text);//return address for firstLetter
     System.out.println(method2);
     
     String method3 = twoLetter(text);//return address for twoLetter
     System.out.println(method3);
     
     String method4 = backward(text);//return address for backward
     System.out.println(method4);
     
     String method5 = countdown(number, text);//return address for countdown
     System.out.println(method5);
   
       
  }
   
 }
 /*
 * fibonacci method for the sole use of error checking for a negative number
 *
 * @parem number is the number entered into args
 * @return -1 for the error 
 **/
 
  public static int iterative(int number) {
    // error condition for a negative first argument
    if (number < 0) {
      return -1;
    }
    return 0;
   }
   
   
 /*
 * method which returns a String a number of times based on a commandline Argument
 *
 * @param number is the amount of times the string will repeat itself
 * @param text is the text that will be repeated based on commandline Argument
 * @return amount of Strings repeated based on args
 **/

     public static String repeat(int number, String text) {
       if (number == 0) {
           return "";
      } 
      else {
            return text + repeat(number - 1, text); //recurisve method for method1
           }
      }
      
 /*
 * method which returns the first letter of a String, depending on the amount entered in args
 *
 * @param number is the amount of times the string will repeat itself
 * @param text is the text that will be repeated based on commandline Argument
 * @return the first letter in the string 
 **/
 
     public static String firstLetter(int number, String text) {
       if (number == 0) {
           return "";
       }
        else {
              return text.charAt(0) + firstLetter(number - 1,text); //recursive method for method2
             } 

        }
  
 /*
 * method which returns two letters of each letter in a String, 
 * depending on the amount entered in args
 *
 * @param text is the text that will be repeated based on commandline Argument
 * @return amount of Strings repeated based on args
 **/
      public static String twoLetter(String text) {
      int length = text.length();
        if (length == 0){
            return "";
      }
     String last = text.substring(length-1, length);
    
     return twoLetter(text.substring(0, length-1)) + last + last;//recursive method for method3
  }


   /*
 * method which returns two letters of each letter in a String, 
 * depending on the amount entered in args
 *
 * @param text is the text that will be repeated based on commandline Argument
 * @return amount of Strings repeated based on args
 **/
     public static String backward(String text) {
      int length = text.length();
        if (length == 0){
            return "";
      }
      String last = text.substring(length-1, length);
    
      return  last + last + last +  backward(text.substring(0, length-1));//recurisive method for method4
    
  }

   /*
 * method which returns two letters of each letter in a String, 
 * depending on the amount entered in args
 *
 * @param number is the amount of times the string will repeat itself
 * @param text is the text that will be repeated based on commandline Argument
 * @return amount of Strings repeated based on args
 **/
     public static String countdown(int number, String text) {
       if (number <= 0 || text.length() == 0) {
           return "";
       }
        else {
              return number + " " + text + ", " + countdown(number - 1, text.substring(1));//recursive method for method5
             } 

        }

}