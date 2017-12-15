/*
* Program which reads from a file and asks user to enter age
* to compare in a list
* @author: Christian McGovern
* @assignment: ICS 211 Assignment #17
* @date : 3/13/15
*
* */
import javax.swing.JOptionPane;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class McGovernChristian17 {
  /**
	 * Start of the main method
	 * 
	 * @param args is the name and age inputed 
	 */
   public static void main(String[] args){
      if(args.length == 0){
         System.out.println("Please enter the file name.");
         System.exit(0);
      }
      else{
         File file = new File(args[0]);
      
         Scanner scanFile = null;
         
         try {
            scanFile = new Scanner(file);
         } 
         
         catch (FileNotFoundException exception) {
                
            System.out.print("ERROR: File not found for " + file);
               
            System.exit(1);
         }        
          
         String firstLineInFile = scanFile.nextLine();
      
      
         LinkedList list = new LinkedList();
      
         while (scanFile.hasNextLine()) {
         
            String line = scanFile.nextLine();
         
         
         
            Scanner tokenInput = new Scanner(line).useDelimiter(",");
            String name = new String();
            name = tokenInput.next();
            Integer age = new Integer(0);
            age = tokenInput.nextInt();
         
         
         
         
            list.add(name, age);
         
         
         
         }
         //User input stuff
         JOptionPane.showMessageDialog(null, list.toString());
         String inputStuff = new String("");
         while (true) {
            inputStuff = JOptionPane.showInputDialog("Enter a age");
            try {
               String outputStuff = list.displayPeopleWithSameAge(Integer.parseInt(inputStuff));
               
               if (!outputStuff.equals("") || !!outputStuff.equals("-1")){
               JOptionPane.showMessageDialog(null, list.displayPeopleWithSameAge(Integer.parseInt(inputStuff)) );
               }
               
               else if (inputStuff.equals("-1")) {
                  JOptionPane.showMessageDialog(null, "goodbye");
                  System.exit(1);
               
               }
               
               else if (outputStuff.equals("")) {
                  JOptionPane.showMessageDialog(null, "There are no matching ages for " + inputStuff);
               }
                                  
            }
            catch (NumberFormatException exception1) {
               JOptionPane.showMessageDialog(null, "Please enter a age");
            }
                  
         
         }
      }    
   
   }//end of main

}
    /**
	 * A list of linked nodes
	 * 
	 *
	 */
 
class LinkedList {
   
   private PersonNode head = null;
   
   /**
	 * Adds an item to the list
	 * 
	 * @param item is the object that is added to the list
	 *            
	 */
   public void add(String name, Integer age) {
   	
      if (head == null) {
      	
         head = new PersonNode(name, age, null);
      }
      
      else {
      	
         PersonNode previous = head;
         PersonNode current = head.getNext();
      	
         while (current != null) {
         	
            previous = current;
            current = current.getNext();
         }
         PersonNode node = new PersonNode(name, age, null);
      	
         previous.setNext(node);
      }
   	
   }
   /**
	 * method which compares two things and determines if they match
	 * @parem input is what is inputed
	 * @return a String of the list 
	 */

   public String displayPeopleWithSameAge(Integer input) {
      String output = new String();
      for(PersonNode current = head; current != null; current = current.getNext()) {
      
         if (input.equals(current.getAge())) {
            output += current.toString() + "\n";
         }
      }
      return output;   
   
   }
   /**
	 * toString method which returns a CSV format
	 * 
	 * @return a String of the list in CSV format
	 */
   public String toString() {
   	
      String csvFormat = new String();
   	
      Integer position = new Integer(1);
   
      for (PersonNode current = head; current != null; current = current.getNext()) {
         csvFormat = csvFormat + current.toString() + "\n";
      
         position++;
      }
      return csvFormat;
   }

   
}
 
  /**
	 * node method which stores a reference to name and age, as well
    * as the next node
	 * 
	 * @param name2 initilizes the name reference variable
	 * @parem age2  initilizes the age reference variable       
	 * @param next2 initilizes the next reference variable
	 * 
    */

class PersonNode {
     
   private String name = new String();
   private Integer age = new Integer(1);
   private PersonNode next;
   
   /**
	 * A contructor, used to initialize and create data fields
	 * 
	 * @param name2 initilizes the name reference variable
	 * @parem age2  initilizes the age reference variable       
	 * @param next2 initilizes the next reference variable
	 * 
    */
      
   public PersonNode(String name2, Integer age2, PersonNode next2 ) {
      
      name = name2;
      age = age2;
      next = next2;
   }
  /**
	 * Used to display the name and age in each node
	 * 
	 * @return a String for the data
	 */
   public String toString() {
      String printFormat = name + " is " + age + " years old. ";
      return printFormat;
   }
   /**
	 * Used To Get A Next Field.
	 * 
	 * @return the next
	 */

   public PersonNode getNext() {
      return next;
   }
   /**
	 *  Used To Set A Data Field.
	 * 
	 * @param next2 is a pointer to the next node.
	 */

   public void setNext(PersonNode next2) {
      next = next2;
   }
  	/**
	 *  Used To Get A Data Field.
	 * 
	 * @return the age of person
	 */
   public Integer getAge() {
      return age;
   }

} 
  
