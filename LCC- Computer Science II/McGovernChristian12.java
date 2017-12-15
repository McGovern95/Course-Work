/*
*  A program that stores each word in the input file
*  in an array of Strings and prints it out.
*
* @author: Christian McGovern
* @assignment: ICS 211 Assignment #12
* @date : 2/21/15
*
* */

import java.util.Scanner;
import java.util.InputMismatchException;
import java.io.File;
import java.io.FileNotFoundException;


  public class McGovernChristian12 {	
   	
      
    /**
   * main method which begins the program
   * 
   * @param commandlineArguments is the file inputed 
   */
   
     public static void main(String [ ] commandlineArguments){
        //Error message when arg is blank
        if(commandlineArguments.length == 0) {
        System.err.println("You did not enter anything");
        System.exit(0);
        }
        
         final Integer MAX_SIZE = new Integer(1000);
         String array[] = new String[MAX_SIZE];   //the array
     
         Integer size = new Integer(0); 
         
         try{
            size = McGovernChristian12.readFromTheFile(commandlineArguments[0], array, size);
         }
         catch(ArrayIndexOutOfBoundsException exception){
            System.out.print("Too many items my friend ");
            System.out.println("only " + MAX_SIZE + " items!");
            System.exit(1);
         }
		
        sortAndPrintTheArray(array, commandlineArguments[0], size); //for the sortAndPrintTheArray method  
               	     
      }
  /**
   * loops through the file, pulling everything
   * 
   * @param inputFile is the name of file inputed into the argument
   * @parem array is the array of words
   * @parem size is the size of the array
   * @return the size of the array
   * 
   */
     public static Integer readFromTheFile(String inputFile, String [] array, 
     Integer size) {

      File file = new File(inputFile);
      Scanner scanFile = null;
      try {
         scanFile = new Scanner(file);
      } 
      catch (FileNotFoundException exception) {
            //Prints error message.        
         System.out.print("ERROR: File not found for \"");
         System.out.println(inputFile+"\"");
      }        
      //connects to file
      if(scanFile != null){
     
         while (scanFile.hasNext()) {
          
            String line = scanFile.next();
            
            array[size]=line;
         	//increments size
            ++size;
         }
     			
        
      }
   	
      return size;
   }

   /**
   * sorts and prints the array
   * 
   * @param inputFile is the name of file inputed into the argument
   * @parem array is the array of words
   * @parem size is the size of the array
   * 
   * 
   */
  public static void sortAndPrintTheArray(String [] array, String inputFile, Integer size){
       Sorting.display = false;
       Sorting.quickSort(array, 0, size-1);//size - 1 is to get around the null thingy
         
      System.out.println("ASCII listing of words in file: \"" + inputFile + "\" = " + size);   
      for (int i = 0; i < size; i++) {
      System.out.println("index = " + i + "," + " element = " + array[i]);

      }   
   }	
 }										
