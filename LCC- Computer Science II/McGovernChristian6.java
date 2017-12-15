/*
* application which executes 5 recursive methods 
*  
*
* @author: Christian McGovern
* @assignment: ICS 211 Assignment #6
* @date : 1/30/15
*
* */
 
   public class McGovernChristian6 {
   
/*
 * main() method which starts the program
 *
 * @parem commandlineArgument is the number inputed to test the recursive methods
 *
 **/

   public static void main(String[] commandlineArguments) {
    if (commandlineArguments.length == 0) {
        System.out.println("Please enter a least one commandline!");
       } 
    else {
        Integer number = new Integer(0); // initializes the number
        try {
            number = Integer.parseInt(commandlineArguments[0]);
        } catch (NumberFormatException exception) { // NumberFormatException
            System.out.println(exception + " is not a integer.");
            System.exit(1); // ends the program
        }
        String asterisk = asterisks(number); // return address for asterisks
        System.out.println(asterisk);
        
        String reverse = reverses(number); // return address for reverses method
        System.out.println(reverse);
        
        String counting = count(number); // return address for count method
        System.out.println(counting);
        
        int sums = sum(number); // return address for sum method
        System.out.println(sums);
        
        int thePower = powerOf2(number); // return address for powerOf2 method
        System.out.println(thePower);
         
     }
   
   }
   
/*
 * method which returns the amount of asterisks from an inputed arg
 *
 * @param number is the number of asterisks
 * @return amount of asterisks based on users commandline argument
 **/

   public static String asterisks (Integer number) {
    if (number == 0) {
        return "";
    } else {
        return "*" + asterisks(number - 1);
    }
  }
  
/*
 * method which returns a String from X to zero
 *
 * @param number is the numbers returned from counting backwards to zero
 * @return the numbers from x to zero
 **/
   public static String reverses (Integer number) {
    if (number == 0) {
        return "0";
      }
      return number + " " + reverses(number - 1);
   } 
   
/*
 * method which returns a String from zero to X
 *
 * @param number is the numbers returned from incrementing 0 to X
 * @return the numbers incrementing from 0 to X 
 **/
   public static String count (Integer number) {
    if (number == 0) {
        return "0";
      }
     return count(number - 1) + " " + number;  
  }  
       
/*
 * method which returns the sum of the numbers from 0 to X incrementing 
 *
 * @param number is the number returned from the sum of the incrementing numbers 
 * @return the sum of numbers incrementing from 0 to X
 **/
   public static int sum (Integer number) {
    if (number == 0) {
       return 0;  
      }
     return number + sum(number - 1);           
            
   }
   
 /*
  * method which returns the sum of the powers of 2 up to the Xth power of 2
  *
  * @param number is the number returned from the xth power of 2 sum
  * @return the sum of powers of 2 up to the Xth power of 2
  **/
   public static int powerOf2 (Integer number) {
     if( number == 0 ) {
     return 1;
   }
     return (1 << number) + powerOf2( number - 1 );
  }
   
  
}   
    