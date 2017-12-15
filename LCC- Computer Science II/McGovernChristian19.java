import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.JOptionPane;

  /*
   * Menu-driven program that allows the user to add a name to a line/Queue
   * 
   * @author: Christian McGovern
   * @assignment: ICS 211 Assignment #19
   * @date : 3/20/15
   *
   * */

public class McGovernChristian19 {


    /**
     * main method which starts the program
     * 
     * @param arguments is the arguments entered      
     * @throws IOException 
     */
   public static void main(String[] arguments) throws IOException {
         if(arguments.length == 0){
         System.out.println("Please enter the file name.");
         System.exit(0);
      }


    //Queue 
      MyQueue<String> queue= new MyQueue<String>(15);

      String name;
    //readFromFile method
      readFromFile(queue,arguments[0]);

      String[] array = { "Offer Person", "Poll Person", "Peek person",
                  "Display Queue", "Exit Program"};
      int choice = 0;

       // display loop   
      while (choice != array.length-1) {
         choice = JOptionPane.showOptionDialog(null, 
                  "Press a Button", 
                  "Queue(Line) of People", 
                  JOptionPane.YES_NO_CANCEL_OPTION, 
                  JOptionPane.QUESTION_MESSAGE, 
                  null, 
                  array, 
                  array[array.length - 1]);  


         if(choice==0){

                //inserts a name into queue
            name=JOptionPane.showInputDialog(null,"Enter Person's name","Input");
            queue.offer(name);

         }
         else if(choice==1){

                //displays and remove the name which is in front of line
            JOptionPane.showMessageDialog(null, queue.poll() + " is next in line");

         }

         else if(choice==2){

                //displays name which is at front of line
            JOptionPane.showMessageDialog(null, queue.peek() + " is front of the line");

         }

         else if(choice==3){
                //Dispay the list
            JOptionPane.showMessageDialog(null, queue.toString());


         }
               
      }
      try {
       writeToFile(queue, arguments[1]); //write 
      }
       catch (ArrayIndexOutOfBoundsException exception) {
         JOptionPane.showMessageDialog(null, " A second file is needed to write to!");
       }

   }// end of main

   /**
     * Reads a file
     * @param queue 
     * @param fileName is name of file
     */
   public static void readFromFile(QueueInterface<String> queue, String fileName) throws IOException{

      String name;
    //creates a BufferedReader
      BufferedReader br= new BufferedReader(new FileReader(fileName));
      while((name = br.readLine()) != null){
        //puts in queue
         queue.offer(name);


      }
   
      br.close();
   }

   /**
     * Writes to file
     * @param queue QueueInterface methods
     * @param fileName is name of file
     */
   public static void writeToFile(QueueInterface<String> queue, String fileName) throws IOException{
      String name;
    //creating a buffer writer to write
      BufferedWriter bw = new BufferedWriter(new FileWriter(fileName));
      while((name = queue.poll()) != null){
        //writin in file
         bw.write(name);
         bw.newLine();

      }
   
      bw.close();
   }



}// end of class



class MyQueue<T> extends ArrayQueue<T>{

   /**
     * Constructor method
     * 
     * @param max is the max number of elements in a the queue     
     */
   public MyQueue(int max) {
      super(max);

   }

   /**
     * Returns a string representation of the object
     * 
     * @return a name on different lines
     */
   public String toString() {
   
      String element = "";
      int count = frontIndex;

      if (!this.empty()) {
        
           
         
         while(count <= endIndex){
          
            
            element = element + array[count]+"\n";
            count = (count + 1) % maxSize;
         
              
         
         }
      }
  
      return element;

   }
}