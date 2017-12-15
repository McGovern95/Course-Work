/*
*  Program which gets 5 pairs of name and age and uses nodes to output the next
* 
*
* @author: Christian McGovern
* @assignment: ICS 211 Assignment #15
* @date : 3/6/15
*
* */

import javax.swing.JOptionPane;
  
   
public class McGovernChristian15 {
    /**
	 * Start of the main method
	 * 
	 * @param args is the name and age inputed 
	 */

   public static void main(String[] args){
      if (args.length != 10){
         System.out.println("Please enter 5 name and age pairs " +
            "on the commandline");
      }
      else {
         int age1 = new Integer(0);
         int age2 = new Integer(0);
         int age3 = new Integer(0);
         int age4 = new Integer(0);
         int age5 = new Integer(0);
           
         try{
            age1 = Integer.parseInt(args[1]);
            age2 = Integer.parseInt(args[3]);
            age3 = Integer.parseInt(args[5]);
            age4 = Integer.parseInt(args[7]);
            age5 = Integer.parseInt(args[9]); 
         }
         catch (NumberFormatException exception) {
            System.out.println("Commandline arguments must have a postive integer as a age.");
            System.exit(0); // end program
         }
      
      }
      String person1 = args[0];
      String person2 = args[2];
      String person3 = args[4];
      String person4 = args[6];
      String person5 = args[8];
   
      PersonNode Personnode1 = new PersonNode(args[0], args[1], null);
      PersonNode Personnode2 = new PersonNode(args[2], args[3], null);
      PersonNode Personnode3 = new PersonNode(args[4], args[5], null);
      PersonNode Personnode4 = new PersonNode(args[6], args[7], null);
      PersonNode Personnode5 = new PersonNode(args[8], args[9], null);
      
      
      Personnode1.setNext(Personnode2);
      Personnode2.setNext(Personnode3);
      Personnode3.setNext(Personnode4);
      Personnode4.setNext(Personnode5);
      Personnode5.setNext(null);
   
   
      String output = new String();
      for (PersonNode i = Personnode1; i != null; i = i.getNext()) {
      output = output + i.toString();
          
      }
   
    JOptionPane.showMessageDialog(null, output);
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
   private String age = new String();
   private PersonNode next;
   
   /**
	 * A contructor, used to initialize and create data fields
	 * 
	 * @param name2 initilizes the name reference variable
	 * @parem age2  initilizes the age reference variable       
	 * @param next2 initilizes the next reference variable
	 * 
    */
      
   public PersonNode(String name2, String age2, PersonNode next2 ) {
      
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

}

