/*
* application which takes a String, an Integer, a String, 
* and an Integer using ADT 
*  
* @author: Christian McGovern
* @assignment: ICS 211 Assignment #9
* @date : 2/10/15
*
* */

import javax.swing.JOptionPane;

 public class McGovernChristian9 {
 
  /**
   * main method which begins the program
   * 
   * @param args is the people and age inputed
   */

   public static void main(String[] args){
     if (args.length <= 1) {
         System.out.println("Please enter a viable argument");
         System.exit(1); // ends the program
      } 

          
        

      Integer age1 = new Integer(0);
      Integer age2 = new Integer(0);

      age1 = Integer.parseInt(args[1]);
      age2 = Integer.parseInt(args[3]);
      
   // Creates two person objects
      Person person1 = new Person(args[0], age1);
      Person person2 = new Person(args[2], age2);
      String[] outputs = new String[4];
      
     //put here first so it displays without the Dr.
     outputs[0] = person1.toString();
     outputs[1] = person2.toString();
     
     //calls the phd and birthday methods
      person1.phd();
      person1.birthday();
      person2.phd();
      person2.birthday();
      
     outputs[2] = person1.toString();
     outputs[3] = person2.toString();
      
   // toString() method 
      String firstOutput = person1.toString();
      String secondOutput = person2.toString();

    //for loop which displays the message panel
    for (String output : outputs) {  
      JOptionPane.showMessageDialog(null, output);
      }
  }
   
 }
 
  /* Stores the first name and age for a person */
  
   class Person{
   
      private String name;
      private Integer age;

   /**
   * The Constructer, used for creating objects and initializing data
   * 
   * @param n1 is the Persons first name
   * @param a1 is the Persons age
   * 
   */
      public Person(String n1, int a1){
         name = n1;
         age = a1;
      }
      /* adds Dr. to the name */
      
      public void phd() {
      name = "Dr. " + name;
      }
      
      /* adds 1 to the age */
      public void birthday() {
      age = age + 1;
      }
      
  /**
   * displays the data in each objects data field
   * 
   * @return The Persons name and age
   */

      public String toString(){
         String output = name + " is " + age + " years old.";
         return output;
      }
   }
