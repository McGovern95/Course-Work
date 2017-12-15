/*
* application which takes a String, an Integer, a String, 
* and an Integer using ADT 
*  
* @author: Christian McGovern
* @assignment: ICS 211 Assignment #8
* @date : 2/7/15
*
* */

import javax.swing.JOptionPane;

 public class McGovernChristian8 {
 
  /**
   * main method which begins the program
   * 
   * @param args is the people and age inputed
   */

   public static void main(String[] args){
      Integer age1 = Integer.parseInt(args[1]);
      Integer age2 = Integer.parseInt(args[3]);

   // Creates two person objects
      Person person1 = new Person(args[0], age1);
      Person person2 = new Person(args[2], age2);

   // toString() method 
      String firstOutput = person1.toString();
      String secondOutput = person2.toString();
      JOptionPane.showMessageDialog(null, firstOutput);
      JOptionPane.showMessageDialog(null, secondOutput);
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
