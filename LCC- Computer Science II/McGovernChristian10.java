/*
* application which takes a String, an Integer, a String, 
* and an Integer using ADT 
*  
* @author: Christian McGovern
* @assignment: ICS 211 Assignment #10
* @date : 2/15/15
*
* */

import javax.swing.JOptionPane;

 public class McGovernChristian10 {
 
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

     Integer age = Integer.parseInt(args[2]);
     
      
   // Creates a person object
      Earthling familyname1 = new Earthling(args[0],args[1], age);
      
     //put here first so it displays without the Dr.
      String firstOutput = familyname1.toString();
   
     
     //calls the phd and birthday methods
      familyname1.phd();
      familyname1.birthday();
     
      
      String secondOutput = familyname1.toString();

    
    JOptionPane.showMessageDialog(null, firstOutput);
    JOptionPane.showMessageDialog(null, secondOutput);
  }
   
 }
 
  /* Stores the first name and age for a person */
  
   class Person {
   
      protected String name;
      protected Integer age;

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
   * @return The Persons name, and age
   */

      public String toString(){
         String output = name + " is " + age + " years old.";
         return output;
      }
   }

   /* extends from person and stores the familyName */
    class Earthling extends Person{
        
       protected String familyName;
       
 /**
   * The Constructer, used for creating objects and initializing data
   * 
   * @param name1 is the Persons first name
   * @param age1 is the Persons age
   * @parem fn1 is the Family name
   */
       public Earthling(String name1, String fn1, int age1){
       
       super(name1, age1);
       familyName = fn1;
       
        
       }
 /**
   * displays the data in each objects data field
   * 
   * @return The Persons name, family name and age
   */
	    public String toString() {
         String output = name + " " + familyName + " is " + age + " years old.";
         return output;
       }
   }