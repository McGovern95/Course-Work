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
   * @assignment: ICS 211 Assignment #20
   * @date : 3/30/15
   *
   * */
  public class McGovernChristian20 {


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


    //Queue Object
      MyQueue<String> queue = (new MyQueue<String>());

      String name;
      
      readFromFile(queue,arguments[0]);//read

      String[] array = { "Offer Person", "Poll Person", "Peek person","Display Queue", "Exit Program"};
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


         if(choice==0)
         {
            //inserting the new name in queue
            name=JOptionPane.showInputDialog(null,"Enter Person's name","Input");
            queue.offer(name);

         }
         else if(choice==1){

                //Display and remove the name which is at front of line
            JOptionPane.showMessageDialog(null, queue.poll() + " is next in line");

         }

         else if(choice==2){

                //Display name which is at front of line
            JOptionPane.showMessageDialog(null, queue.peek() + " is front of the line");

         }

         else if(choice==3){
                //Dispay all the list
            JOptionPane.showMessageDialog(null, queue.toString());


         }
             
      }
  
      try {
       writeToFile(queue, arguments[1]); //write 
      }
       catch (ArrayIndexOutOfBoundsException exception) {
         JOptionPane.showMessageDialog(null, " A second file is needed to write to!");
       }



   }// end of main()

   /**
     * Reads a file
     * @param queue 
     * @param fileName name of file
     */
   public static void readFromFile(QueueInterface<String> queue, String fileName) throws IOException{
      

      try
      {
         String name;
            //creating a buffer reader to read
         BufferedReader br= new BufferedReader(new FileReader(fileName));
         while((name = br.readLine()) != null){
              //putting in the queue
            queue.offer(name);
         }
              //closing buffer reader
         br.close();
      }
      catch(Exception e)
      {
         System.err.println(e.getMessage());
      }

   }

   /**
    * Writes the contents of LinkedQueue to the output file at the ned of program
    * @param queue QueueInterface methods
    * @param file_name name of file
    */
   public static void writeToFile(QueueInterface<String> queue, String fileName) throws IOException{
      try
      {
         String name;
      //creating a buffer 
         BufferedWriter bw= new BufferedWriter(new FileWriter(fileName));
         while((name=queue.poll()) != null){
         
            bw.write(name);
            bw.newLine();

         }
          
         bw.close();
      }
      catch(Exception ex)
      {
         System.err.println(ex.getMessage());
      }
   }



}// end of class

 /**
   * Interface to be implemented by LinkedQueue
   */
   
   interface QueueInterface<T> 
  {
   public boolean empty();
   public boolean offer(String element);
   public String poll();
   public String peek();
 }

  class Node<T>
{
   private String data;
   private Node nextNode;
   public Node(String dataObject, Node nextNodeObject)
   {
      this.data=dataObject;
      this.nextNode = nextNodeObject;
   }

    /**
    * Gets the next node
    * @return next node
    */
   public Node getNext()
   {
      return nextNode;
   }

    /**
    * Sets the next node of the current node
    * @param nextNodeObject next node to be set as next to the current node
    */
   public void setNext(Node nextNodeObject)
   {
      nextNode = nextNodeObject;
   }

    /**
    * Sets data of the current node
    * @param dataObject data to be inserted in new node
    */
   public void setData(String dataObject)
   {
      this.data = dataObject;
   }

    /**
    * Gets data of the current node
    * @return data of the node
    */
   public String getData()
   {
      return this.data;
   }
}

class LinkedQueue<T> implements QueueInterface<T>
{
   protected Node<T> lastNode = null;

   LinkedQueue() {
   }

    /**
    * Checks if the queue is empty
    * @return true if empty, false if not empty
    */
   public boolean empty() {
      if(lastNode == null)
      {
         return true;
      }
      else
         return false;
   }

    /**
    * Inserts new node in the queue
    * @param element data to be inserted in new node
    * @return true on success
    */
   public boolean offer(String element) 
   {
      Node<T> newLastNode = new Node<T>(element,null);

       
      if(empty())
      {
         newLastNode.setNext(newLastNode);
      }
      else
      {
           
         newLastNode.setNext(lastNode.getNext());
         lastNode.setNext(newLastNode);
      }
      lastNode = newLastNode;
      return true;
   }

    /**
    * Removes the first node and returns it
    * @return data at first node
    */
   public String poll() 
   {
        // If empty, return null
      if(empty())
         return null;
      else
      {
         Node<T> frontNode = lastNode.getNext();

            //Check if there will be no node left after polling this one
         if (frontNode == lastNode) 
         {
            lastNode = null;
         }
         else //Remove the first node and update next of the last node
         {
            lastNode.setNext(frontNode.getNext());
         }
         return frontNode.getData();
      }
   }

    /**
    * Returns data of the first node without removing it from the queue
    * @return data at first node
    */
   public String peek() 
   {
      if (empty())
      {
         return null;
      }
      else
      {
         Node<T> frontNode = lastNode.getNext();
         return frontNode.getData();
      }
   }
}

class MyQueue<T> extends LinkedQueue<T>{

   /**
    * Constructor
    * 
    */
   public MyQueue() 
   {
      super();      
   }

   /**
    * Returns a string representation of the object
    * 
    * @return a name on different lines
    */
   public String toString() 
   {
        
      String toReturn = "";

        // Traversing the list
      Node<T> frontNode = lastNode.getNext();

      if(empty())    //If queue is  empty
         return "";
      else if(frontNode == lastNode)    //If only one element
      {
         return frontNode.getData().toString();
      }
      else    //More than one element in the queue
      {
         while(frontNode != lastNode)
         {
            toReturn = toReturn + frontNode.getData()+"\n";
            frontNode=frontNode.getNext();
         }
         toReturn = toReturn + frontNode.getData()+"\n";    //Appending data of last node because it will be missed in the loop
      }
      return toReturn;
   }
}