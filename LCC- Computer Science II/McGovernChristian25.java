import java.util.Scanner;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.JOptionPane;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.NoSuchElementException;

  /*
   * Program that  allows the user to add a Patient to a priority queue, remove, 
   *  and display the next Patient in the priority queue, and quit the program. 
   * 
   * @author: Christian McGovern
   * @assignment: ICS 211 Assignment #25
   * @date : 4/16/15
   *
   * */
 
public class McGovernChristian25 {

   public static void main(String[] args) {
      if(args.length == 0){
         System.out.println("Please enter the file name.");
         System.exit(0);
      }
      
      PriorityQueue<Patient> pQueue = new PriorityQueue<Patient>();
     
     
      String name;
      String priority;
    //readFromFile method
      try {
         readFromFile(pQueue, args[0]);
      } 
      catch (IOException exception) {
         System.out.println(" File not found!");
         System.exit(0);
      }
   
      String[] array = {"New Patient", "Next Patient", "Exit Program"};
      int choice = 0;
   
       // display loop   
      while (choice != array.length-1) {
         choice = JOptionPane.showOptionDialog(null, 
                  "Press a Button", 
                  "Patient Scheduling menu", 
                  JOptionPane.YES_NO_CANCEL_OPTION, 
                  JOptionPane.QUESTION_MESSAGE, 
                  null, 
                  array, 
                  array[array.length - 1]);  
      
      
         if(choice == 0){
         
                //inserts a name into queue, and give priority 
            name = JOptionPane.showInputDialog(null,"Enter Patient's name");
            
            
            
            priority = JOptionPane.showInputDialog(null,"Enter Patient's priority");
            
            Patient patient = new Patient(name, Integer.parseInt(priority));
            pQueue.offer(patient);
         }
         
         
         else if(choice == 1){
         
                //displays next patient
            JOptionPane.showMessageDialog(null, "The next patient is " +  pQueue.peek() );
         
         }
        else if(choice == 2) {
         
        }
      
               
      }
      try {
         try {
            writeToFile(pQueue, args[1]); //writes to file
         }  
         catch (IOException exception) {
            System.out.println(" File not found!");
            System.exit(0);
         }
      }
      catch (ArrayIndexOutOfBoundsException exception) {
         JOptionPane.showMessageDialog(null, " A second file is needed to write to!");
      }
   
   
   
     
     
     
   } //end of main

 
   /**
     * Reads a file
     * @param queue 
     * @param fileName is name of file
     */
   public static void readFromFile(PriorityQueue<Patient> queue, String fileName) throws IOException{
   
        
        File file = new File(fileName);
        Scanner input = new Scanner(fileName);
        String name;
        String priority;
        String line;
        
        line = input.nextLine();
          while (input.hasNextLine()) {
          
           line = input.nextLine();
           
          Scanner lineInput = new Scanner(line).useDelimiter(",");
         
         priority = lineInput.next();
         name = lineInput.next();
           
         Patient patient1 = new Patient(name, Integer.parseInt(priority));
        
         queue.offer(patient1);
         
       }
    
       input.close();  
 
   }

   /**
     * Writes to file
     * @param queue QueueInterface methods
     * @param fileName is name of file
     */
   public static void writeToFile(PriorityQueue<Patient> queue, String fileName) throws IOException{
      String name = "";
    //creating a buffer writer to write
      BufferedWriter bw = new BufferedWriter(new FileWriter(fileName));
      while((queue.peek()) != null){
        //write in in file
         bw.write(name);
         bw.newLine();
      
      }
   
      bw.close();
   }

   
   
}//end of McGovernChristian25
   
class Patient implements java.lang.Comparable<Patient> {
  
   //data fields
   private String name;
   private Integer priority;
   

   //constructer
   public Patient(String name, int priority) {
      
      this.name = name;
      this.priority = priority; 
      
   }

   public String toString(){
   
   
      String output =  name;
         
      return output;
   }

   
   
   public int getPriority() {
      return priority;
   }
   
   public String getName() {
      return name;
   }
   
   public int compareTo(Patient patient2){
   
      int result = priority.compareTo(patient2.priority);
     
      return result;
   
   } 

}