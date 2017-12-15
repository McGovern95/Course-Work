import javax.swing.JOptionPane;
import java.util.Scanner;
import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.Stack;
import java.util.EmptyStackException;
/**
 * A console menu for the IRS
 * 
 * @author William McDaniel Albritton
 */
public class McGovernChristian23 {
// data fields
   private BinarySearchTree<Person> tree = 
   new BinarySearchTree<Person>();
   private String database = 
   new String("presidents.csv");

/** No-parameter constructor */
   public McGovernChristian23() {
   // We don't need any code in constructor,
   // as we already initialized the data fields.
   }

/**
 * Starts the menu.
 * 
 * @param args
 *            is not used
 */
   public static void main(String[] args) {
   // Instantiate menu & display menu
      McGovernChristian23 menu = new McGovernChristian23();
      menu.displayMenu();
   }

/** Displays a menu, asks for choice, executes choice */
   public void displayMenu() {
   // read records from database and store in tree
      try {
         this.readFromDatabase();
      } 
      catch (Exception exception) {
         System.out.println("Error in reading from database: " + exception);
      }
   // list of choices
      String[] choices = { "Add Person", "Edit Person", "Remove Person",
            "Display Person", "Display List", "Exit Program",
            "Node Information" };
   // display loop
      int choice = 0;
      while (choice != choices.length) {
         choice = JOptionPane.showOptionDialog(null, // put in center of
            // screen
            "Select a Command", // message to user
            "Shopping List Main Menu", // title of window
            JOptionPane.YES_NO_CANCEL_OPTION, // type of option
            JOptionPane.QUESTION_MESSAGE, // type of message
            null, // icon
            choices, // array of strings
            choices[choices.length - 1]); // default choice (last one)
         switch (choice) {
            case 0:
               try {
                  this.add();
               } 
               catch (Exception exception) {
                  // "null" puts message in center of screen
                  JOptionPane.showMessageDialog(null,
                        "Unable to add, because " + exception);
               }
               break;
            case 1:
               try {
                  this.edit();
               } 
               catch (Exception exception) {
                  JOptionPane.showMessageDialog(null,
                        "Unable to edit, because " + exception);
               }
               break;
            case 2:
               try {
                  this.remove();
               } 
               catch (Exception exception) {
                  JOptionPane.showMessageDialog(null,
                        "Unable to remove, because " + exception);
               }
               break;
            case 3:
               try {
                  this.displayOne();
               } 
               catch (Exception exception) {
                  JOptionPane.showMessageDialog(null,
                        "Unable to display, because " + exception);
               }
               break;
            case 4:
               this.displayAll();
               break;
            case 5:
            // quit the program
               choice = choices.length;
               break;
            case 6:
            // Your programming assignment
               try {
                  this.nodeInformation();
               } 
               catch (Exception exception) {
                  JOptionPane.showMessageDialog(null,
                        "Unable to display node information, because "
                        + exception);
               }
               break;
         }
      }
   // write records stored in tree to database
      try {
         this.writeToDatabase();
      } 
      catch (Exception exception) {
         System.out.println("Error in writing to database: " + exception);
         System.out.println("You might need to close the file.");
      }
   }

/** read from a database */
   private void readFromDatabase() throws FileNotFoundException {
   // Connect to the file in the current directory
      File file = new File(database);
      Scanner input = new Scanner(file); // may throw FileNotFoundException
   // read from file
      String line;
      String ssn;
      String tax;
      String name;
   // get rid of 1st line
      line = input.nextLine();
   // read contents of file and display on console
      while (input.hasNextLine()) {
         line = input.nextLine();
      // returns all characters up to a comma
         Scanner lineInput = new Scanner(line).useDelimiter(",");
         ssn = lineInput.next();
         tax = lineInput.next();
         name = lineInput.next();
         Person person = new Person(ssn, tax, name);
         tree.add(person);
      }
      input.close();
   }

/**
 * write Person records (objects) from tree and store in database.
 * 
 * @exception FileNotFoundException
 *                if cannot find the specified file
 */
   private void writeToDatabase() throws FileNotFoundException {
   // make connection to database
      PrintWriter fileWriter = new PrintWriter(database);
   // write to file: title of each column (top row)
   // with NO spaces between commas (",")
      fileWriter.println("ssn,tax,name");
   // Write to file: all the data in the list.
   // We want PREORDER, so that when we read from the file again,
   // the tree will have the same structure as before.
   // If we use INORDER, then we will have an extremely unbalanced
   // tree (a linked list) when we read from the file again.
   // If we use POSTORDER, then we will have an unbalanced (but not
   // extremely unbalanced) tree when we read from the file again.
      String allData = tree.preOrder();
   // loop from 0 to length of string
      for (int i = 0; i < allData.length(); i++) {
      // isolate a single character
         String character = allData.substring(i, i + 1);
      // Since class PrintWriter will not create a newline in a file for
      // "\n",
      // we have to use println() instead of "\n"
         if (character.equals("\n")) {
            fileWriter.println();
         }
         // otherwise, we write all other characters to the file
         else {
            fileWriter.print(character);
         }
      }
   // don't forget to close the file connection!
   // may not write to file if not closed!
      fileWriter.close();
   }// end of writeToDatabase()

/** Prompt user for ssn, tax, and name */
   private void add() {
   // get user input
      String ssn = JOptionPane.showInputDialog("Enter person's ssn");
      String tax = JOptionPane.showInputDialog("Enter person's tax");
      String name = JOptionPane.showInputDialog("Enter person's name");
   // instantiate person & add
      Person person = new Person(ssn, tax, name);
      tree.add(person);
   }

/** Prompt user for person's ssn, then change to new tax */
   private void edit() {
   // get user input
   // displays message, and returns a string of text in text box
      String ssn = JOptionPane.showInputDialog("Enter person's ssn");
   // get user input
      String tax = JOptionPane.showInputDialog("Enter person's new tax");
   // get reference to real person using searchKey person
   // "searchKey" variable only contains the search key SSN
      Person searchKey = new Person(ssn);
      Person person = tree.get(searchKey); // no casting!!!
   // change the tax
      person.setTax(tax);
   }

/** Prompt user for person's ssn and remove */
   private void remove() {
   // get user input
   // displays message, and returns a string of text from text box
      String ssn = JOptionPane.showInputDialog("Enter person's ssn");
   // get reference to real person using searchKey person
   // "searchKey" variable only contains the search key SSN
      Person searchKey = new Person(ssn);
      tree.remove(searchKey);
   }

/** Prompt user for person's ssn, then display data for 1 person */
   private void displayOne() {
   // get user input
   // displays message, and returns a string of text in text box
      String ssn = JOptionPane.showInputDialog("Enter person's ssn");
   // get reference to real person using searchKey person
   // "searchKey" variable only contains the search key SSN
      Person searchKey = new Person(ssn);
      Person person = tree.get(searchKey); // no casting!!!
      if (person != null) {
         double tax = person.getTax();
         String name = person.getName();
      // make the output nice and pretty
         String output = new String("");
         output = output + "Name: " + name + "\n";
         output = output + "SSN:  " + ssn + "\n";
         output = output + "Tax: ";
         if (tax < 0) {
            tax = -tax;
            output = output + "-$" + tax + "\n";
         } 
         else {
            output = output + " $" + tax + "\n";
         }
         JOptionPane.showMessageDialog(null, output);
      } 
      else {
      // record does not exist
         JOptionPane.showMessageDialog(null, "ERROR: Record #" + ssn
            + " does not exist!");
      }
   }

/** Display */
   private void displayAll() {
      System.out.println("ssn,tax,name");
      System.out.println("------------");
      System.out.println(tree.toString());
   }

/**
 * Your programming assignment code goes in class BinarySearchTree in the
 * method "void nodeInformation(T searchKey)"
 */
   private void nodeInformation() {
   // get user input
      String ssn = JOptionPane.showInputDialog("Enter person's ssn");
      Person searchKey = new Person(ssn);
      tree.nodeInformation(searchKey);
   }

}// end of class


/**
* Class BinarySearchTree used to run menu.
* 
*/ 

class BinarySearchTree<T extends java.lang.Comparable<T>> {

/**
 *Method to print out desired output using dialogue box interface
 * 
 * @param searchKey
 *            the item with the key value only
 */
   public void nodeInformation(T searchKey) {
      //Current node
      T person1 = this.get(searchKey);
     //Instantiate node of type BinaryNode
      BinaryNode <T> node = this.getNode(root, searchKey); 
      System.out.println("current node       = " +  person1); 
      System.out.println("type = " + getType(searchKey));
      System.out.println("depth              = " + depth);  
      
      if (node == root){
         System.out.println("ancestors          = none" );
      }
      else{
         System.out.println("ancestors          = ");
         try{
            while(ancestors != null){
               System.out.print("                     ");
               System.out.println(ancestors.pop());
               top--;
            }
         }
         catch (EmptyStackException e){
            
         }
      }

      System.out.println();
      if(node.getLeftChild() != null){
         System.out.println("left descendants   = " + getPreOrder(node.getLeftChild()));
      }
      else{
         System.out.println("left descendants   = none");
      }

      if(node.getRightChild() != null){
         System.out.println("right descendants  = " + getPreOrder(node.getRightChild()));                   
      }
      else{
         System.out.println("right descendants  = none \n");
      }

      //Resets depth counter
      depth = 0;
   }

// data fields
   private BinaryNode<T> root = null;
   protected int depth = 0;              
   Stack ancestors = new Stack();        
   int top = 0;
   
  
   
   /**use to access private method
    *
    *@ param searchKey object for storing search key
    */
   public BinaryNode<T> getNode(T searchKey1) {
     // cannot get direct access to the root outside the class
      return this.getNode(root, searchKey1);
   }

/**
 * gets an item from the tree with the same search key
 * method used to get left and right child
 *
 * @param node root of the tree/subtree
 * @param searchKey2 object storing the search key
 */
   private BinaryNode<T> getNode(BinaryNode<T> node, T searchKey2) {
    
      // if not found, throw exception
      
      if (node == null) {
         throw new TreeException("ERROR: No such Person for " + searchKey2);
      } 
      else {
      // if the search key matches, return the item's address
         if (searchKey2.compareTo(node.getData()) == 0) {
            return node;
         }
         // if the search key of the searchKey is less than the node,
         // then search the left subtree
         else if (searchKey2.compareTo(node.getData()) < 0) {
            depth++;
            ancestors.push(node);
            top++;
            return this.getNode(node.getLeftChild(), searchKey2);
         }
         // if the search key of the searchKey is greater than the node,
         // then search the right subtree
         else {
            depth++;
            ancestors.push(node);
            top++;
            return this.getNode(node.getRightChild(), searchKey2);
         }
               
      }
            

   }
   
/**
 * preOrder traversal
 * 
 * @return a preOrder String of the tree
 */
   public String getPreOrder() {
      return this.getPreOrder(root);
   }

/**
 * preOrder display of nodes, with newline between each node
 * 
 * @param node root of the tree/subtree
 *            
 * @return a preOrder String of the tree
 */
   private String getPreOrder(BinaryNode<T> node) {
      String displayNodes = "";
      if (node != null) {
         displayNodes = displayNodes + node.toString() + "\n                     " ;
         displayNodes = displayNodes + 
            this.preOrder(node.getLeftChild());
         displayNodes = displayNodes + 
            this.preOrder(node.getRightChild());
      }
      return displayNodes ;
   }


/** constructor */
   public BinarySearchTree() {
   // data fields already initialized
   }
   
   
  /**
 * gets the type of the node
 * 
 * @param searchKey is an object storing only the search key
 */

   
   public String getType(T searchKey){
   
    T rightChild = getRight(searchKey);
    T leftChild = getLeft(searchKey);
    T parent = getParent(searchKey);
    
    if (rightChild == null && leftChild == null){
      return "leaf";
    }
   else if (parent == null){
       return "root";
   }
  else {
    return "internal";
  }
          
 }//end of getType 

/**
 * gets the left child of the node
 * 
 * @param searchKey is an object storing only the search key
 */
   public T getLeft(T searchKey){
       return this.getLeft(root, searchKey);

   } 
   
 /**
 * gets the left child of the node
 * 
 * @param searchKey is an object storing only the search key
 */
   
   private T getLeft(BinaryNode<T> node, T searchKey){
      if (node == null) {
         throw new TreeException("Item not found!");
      } 
      else {

         if (searchKey.compareTo(node.getData()) == 0) {
            BinaryNode<T> leftChild = node.getLeftChild();
            if  (leftChild == null) {
               return null;
            }
            else {
               return node.getLeftChild().getData();
            }
              
         }
  
         else if (searchKey.compareTo(node.getData()) < 0) {
            return this.getLeft(node.getLeftChild(), searchKey);
         }
     
         else {
            return this.getLeft(node.getRightChild(), searchKey);
         }
      }
     
 }//end of getLeft
 
 /**
 * gets the right child of the node
 * 
 * @param searchKey is an object storing only the search key
 */
 
     public T getRight(T searchKey){
       return this.getRight(root, searchKey);

   } 
   
 /**
  * gets the right child of the node
  * 
  * @param searchKey is an object storing only the search key
  */
 
   private T getRight(BinaryNode<T> node, T searchKey){
      if (node == null) {
         throw new TreeException("Item not found!");
      } 
      else {
      
         if (searchKey.compareTo(node.getData()) == 0) {
            BinaryNode<T> rightChild = node.getRightChild();
            if  (rightChild == null) {
               return null;
            }
            else {
               return node.getRightChild().getData();
            }
              
         }
  
         else if (searchKey.compareTo(node.getData()) > 0) {
            return this.getRight(node.getRightChild(), searchKey);
         }
     
         else {
            return this.getRight(node.getLeftChild(), searchKey);
         }
      }
     
 }//end of getRight
 
  /**
  * gets the parent of the node
  * 
  * @param searchKey is an object storing only the search key
  */
 
   public T getParent(T searchKey){
       return this.getParent(root, searchKey, null);
       
   } 
   
 /**
  * gets the parent of the node
  * 
  * @param searchKey is an object storing only the search key
  */

   private T getParent(BinaryNode<T> node, T searchKey,BinaryNode<T> parent){
       
     
      if (node == null) {
         throw new TreeException("Item not found!");
      } 
      else {
      
         if (searchKey.compareTo(node.getData()) == 0) {
         //try catch method for root node with no parent
           try { 
             return parent.getData();
              } catch (NullPointerException exception) {
                return null; 
           }
         }
  
         else if (searchKey.compareTo(node.getData()) < 0) {
            return this.getParent(node.getLeftChild(), searchKey,node);
         }
        
         else {
            return this.getParent(node.getRightChild(), searchKey,node);
         }
       
      }
     
   } //end of parent    


/**
 * adds an item to the tree
 * 
 * @param item
 *            is the object to be added
 */
   public void add(T item) {
   // calls a recursive, private method
   // cannot get direct access to the root outside the class
      root = add(root, item);
   }

/**
 * adds an item to the tree
 * 
 * @param node
 *            is the root of the tree/subtree
 * @param item
 *            is the object to be added
 */
   private BinaryNode<T> add(BinaryNode<T> node, T item) {
   // base case: empty tree or end of a leaf
      if (node == null) {
         return new BinaryNode<T>(item, null, null);
      }
      // base case: duplicate node, so throw exception
      else if (item.compareTo(node.getData()) == 0) {
         throw new TreeException("No duplicate items are allowed!");
      }
      // recursive case: if item is less than current node
      // then move to left child node
      else if (item.compareTo(node.getData()) < 0) {
      // set the node's left child to the
      // left subtree with item added
         node.setLeftChild(this.add(node.getLeftChild(), item));
         return node;
      }
      // recursive case: if item is greater than current node
      // then traverse to right child node
      else {
      // set the node's right child to the
      // right subtree with item added
         node.setRightChild(this.add(node.getRightChild(), item));
         return node;
      }
   }

/**
 * called automatically by println/print method
 * 
 * @return an inorder String of the tree
 */
   public String toString() {
      return this.inOrder(root);
   }

/**
 * inOrder display of nodes, with newline between each node
 * 
 * @param node
 *            is the root of the tree/subtree
 * @return an inorder String of the tree
 */
   private String inOrder(BinaryNode<T> node) {
      String displayNodes = "";
      if (node != null) {
         displayNodes = displayNodes + 
            this.inOrder(node.getLeftChild());
         displayNodes = displayNodes + node.toString() + "\n";
         displayNodes = displayNodes + 
            this.inOrder(node.getRightChild());
      }
      return displayNodes;
   }

/**
 * preOrder traversal
 * 
 * @return an preOrder String of the tree
 */
   public String preOrder() {
      return this.preOrder(root);
   }

/**
 * preOrder display of nodes, with newline between each node
 * 
 * @param node
 *            is the root of the tree/subtree
 * @return an preOrder String of the tree
 */
   private String preOrder(BinaryNode<T> node) {
      String displayNodes = "";
      if (node != null) {
         displayNodes = displayNodes + node.toString() + "\n";
         displayNodes = displayNodes + 
            this.preOrder(node.getLeftChild());
         displayNodes = displayNodes + 
            this.preOrder(node.getRightChild());
      }
      return displayNodes;
   }

/**
 * postOrder traversal
 * 
 * @return an postOrder String of the tree
 */
   public String postOrder() {
      return this.postOrder(root);
   }

/**
 * postOrder display of nodes, with newline between each node
 * 
 * @param node
 *            is the root of the tree/subtree
 * @return an postOrder String of the tree
 */
   private String postOrder(BinaryNode<T> node) {
      String displayNodes = "";
      if (node != null) {
         displayNodes = displayNodes + this.postOrder(node.getLeftChild());
         displayNodes = displayNodes + this.postOrder(node.getRightChild());
         displayNodes = displayNodes + node + "\n";
      }
      return displayNodes;
   }

/**
 * gets an item from the tree with the same search key
 * 
 * @param searchKey1
 *            is an object storing only the search key
 */
   public T get(T searchKey1) {
   // cannot get direct access to the root outside the class
      return this.get(root, searchKey1);
   }

/**
 * gets an item from the tree with the same search key
 * 
 * @param node
 *            is the root of the tree/subtree
 * @param searchKey2
 *            is an object storing only the search key
 */
   private T get(BinaryNode<T> node, T searchKey2) {
   // if not found, throw exception
      if (node == null) {
         throw new TreeException("Item not found!");
      } 
      else {
      // if the search key matches, return the item's address
         if (searchKey2.compareTo(node.getData()) == 0) {
            return node.getData();
         }
         // if the search key of the searchKey is less than the node,
         // then search the left subtree
         else if (searchKey2.compareTo(node.getData()) < 0) {
            return this.get(node.getLeftChild(), searchKey2);
         }
         // if the search key of the searchKey is greater than the node,
         // then search the right subtree
         else {
            return this.get(node.getRightChild(), searchKey2);
         }
      }
   }

/**
 * Calls a recursive method that removes an item from the tree with the same
 * search key
 * 
 * @param searchKey3
 *            is an object storing only the search key
 */
   public void remove(T searchKey3) {
      root = this.remove(root, searchKey3);
   }

/**
 * Finds the item to be removed from the tree with the same search key
 * 
 * @param node
 *            is the root of the tree/subtree
 * @param searchKey4
 *            is an object storing only the search key
 */
   private BinaryNode<T> remove(BinaryNode<T> node, T searchKey4) {
   // if item not found, throw exception
      if (node == null) {
         throw new TreeException("Item not found!");
      }
      // if search key is less than node's search key,
      // continue to left subtree
      else if (searchKey4.compareTo(node.getData()) < 0) {
         node.setLeftChild(this.remove(node.getLeftChild(), searchKey4));
         return node;
      }
      // if search key is greater than node's search key,
      // continue to right subtree
      else if (searchKey4.compareTo(node.getData()) > 0) {
         node.setRightChild(this.remove(node.getRightChild(), searchKey4));
         return node;
      }
      // found node containing object with same search key,
      // so delete it
      else {
      // call private method remove
         node = this.remove(node);
         return node;
      }
   }

/**
 * Removes leaf nodes, and nodes with one child node from the tree with the
 * same search key & removes 2 child nodes too
 * 
 * @param node
 *            is the root of the tree/subtree
 */
   private BinaryNode<T> remove(BinaryNode<T> node) {
   // if node is a leaf,return null
      if (node.getLeftChild() == null && node.getRightChild() == null) {
         return null;
      }
      // if node has a single right child node,
      // then return a reference to the right child node
      else if (node.getLeftChild() == null) {
         return node.getRightChild();
      }
      // if node has a single left child node,
      // then return a reference to the left child node
      else if (node.getRightChild() == null) {
         return node.getLeftChild();
      }
      // if the node has two child nodes
      else {
      // get next Smaller Item, which is Largest Item in Left Subtree
      // The next Smaller Item is stored at the rightmost node in the left
      // subtree.
         T largestItemInLeftSubtree = this.getItemWithLargestSearchKey(node
            .getLeftChild());
      // replace the node's item with this item
         node.setData(largestItemInLeftSubtree);
      // delete the rightmost node in the left subtree
         node.setLeftChild(this.removeNodeWithLargestSearchKey(node
            .getLeftChild()));
         return node;
      }
   }

/**
 * Returns the address of the item with the largest search key in the tree
 * 
 * @param node
 *            is the root of the tree/subtree
 */
   private T getItemWithLargestSearchKey(BinaryNode<T> node) {
   // if no right child, then this node contains the largest item
      if (node.getRightChild() == null) {
         return node.getData();
      }
      // if not, keep looking on the right
      else {
         return this.getItemWithLargestSearchKey(node.getRightChild());
      }
   }

/**
 * Removes the node with the largest search key
 * 
 * @param node
 *            is the root of the tree/subtree
 */
   private BinaryNode<T> removeNodeWithLargestSearchKey(BinaryNode<T> node) {
   // if no right child, then this node contains the largest item
   // so replace it with its left child
      if (node.getRightChild() == null) {
         return node.getLeftChild();
      }
      // if not, keep looking on the right
      else {
         node.setRightChild(this.removeNodeWithLargestSearchKey(node
            .getRightChild()));
         return node;
      }
   }

}// end of class


