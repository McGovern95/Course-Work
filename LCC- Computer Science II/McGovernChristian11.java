/*
* application which takes 5 strings and 5 intergers in an array and lists 
* them from least to greatest 
* @author: Christian McGovern
* @assignment: ICS 211 Assignment #11
* @date : 2/17/15
*
* Reason for choosing selectionSort, int i = start; i < end; i++, is the applicable  
* sorting algorithm for finding least to greatest
*
* */
import javax.swing.JOptionPane;
// used to compare two objects.
import java.lang.Comparable; 

  public class McGovernChristian11{
  
    /**
   * main method which begins the program
   * 
   * @param args is the people and age inputed
   */
   public static void main(String[] args){
      if (args.length != 10){
         System.out.println("Please enter 5 name and age pairs " +
            "on the commandline");
      }
      else{
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
            System.out.println("Commandline arguments must have a postive integer as ag.");
            System.exit(0); // end program
         }
         Sorting.display = false;
         //start of the array
         Person[] array = new Person[5];
         array[0] = new Person(args[0], age1);
         array[1] = new Person(args[2], age2);
         array[2] = new Person(args[4], age3);
         array[3] = new Person(args[6], age4);
         array[4] = new Person(args[8], age5);
         
         JOptionPane.showMessageDialog(null, array[0]+ "\n" +array[1]+ "\n"+array[2]+ "\n"+
            array[3] + "\n" + array[4]);
         
         Sorting.selectionSort(array);//selectionSort
         
         JOptionPane.showMessageDialog(null, array[0]+ "\n" +array[1]+ "\n"+array[2]+ "\n"+
            array[3] + "\n" + array[4]);
       
      }
   }
}
    /* Stores the first name and age for a person */
   class Person implements Comparable{
   // Data Fields
   protected String name;
   protected int age;
  
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
   * @return The Persons name, and age
   */
   
   public String toString(){
      String output = name + " is " + age + " years old.";
      return output;
   }

   /**
   * method used to get the age of the person
   * 
   * @return the persons age
   */
   
   public int getAge(){
      return age;
   }

    /**
   * compareTo() method
   * @parem the object to be compared
   * @return the age subtracted from the person object 
   */ 
   public int compareTo(Object object) throws ClassCastException{    
     return age - ((Person)object).age;
     
   }

}