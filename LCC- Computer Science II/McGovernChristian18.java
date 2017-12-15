   /*
    * Program which uses a bubblesort method and sorts a linked list.
    * 
    * @author: Christian McGovern
    * @assignment: ICS 211 Assignment #18
    * @date : 3/17/15
    *
    * */
import javax.swing.JOptionPane;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

  public class McGovernChristian18 {
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
         JOptionPane.showMessageDialog(null, list.toString());
         list.bubbleSort();
         JOptionPane.showMessageDialog(null, list.toString());
        
 
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
   *  bubble sort
   * 
   *  	
   */
  public void bubbleSort(){

     PersonNode previous = head;
     PersonNode current = head.getNext();
     boolean swap = true;

    while(swap) {
    
     swap = false;
     previous = head;
     while(previous != null) {
                
        if(previous.getNext() != null && previous.getAge() > previous.getNext().getAge())
        {
           String tempName = previous.getName();
           Integer tempAge = previous.getAge();
           current = previous.getNext();
           previous.setName(current.getName());
           previous.setAge(current.getAge());
           current.setName(tempName);
           current.setAge(tempAge);
           swap = true;
        }
     previous = previous.getNext();
     }

  }   
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
	 * @return the name of person
	 */
   public String getName() {
      return name;
   }

  /**
	 *  Used To Set A Data Field.
	 * 
	 * @param name2 is a pointer to the next name.
	 */

   public void setName(String name2) {
      name = name2;
   }
  

  	/**
	 *  Used To Get A Data Field.
	 * 
	 * @return the age of person
	 */
   public Integer getAge() {
      return age;
   }

     /**
	 *  Used To Set A Data Field.
	 * 
	 * @param age2 is a pointer to the next age.
	 */

   public void setAge(Integer age2) {
      age = age2;
   }
} 
  
