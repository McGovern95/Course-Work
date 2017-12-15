/**
* Web worker: an object of this class executes in its own new thread
* to receive and respond to a single HTTP request. After the constructor
* the object executes on its "run" method, and leaves when it is done.
*
* One WebWorker object is only responsible for one client connection. 
* This errorCode uses Java threads to parallelize the handling of clients:
* each WebWorker runs in its own thread. This means that you can essentially
* just think about what is happening on one client at a time, ignoring 
* the fact that the entirety of the webserver execution might be handling
* other clients, too. 
*
* This WebWorker class (i.e., an object of this class) is where all the
* client interaction is done. The "run()" method is the beginning -- think
* of it as the "main()" for a client interaction. It does three things in
* a row, invoking three methods in this class: it reads the incoming HTTP
* request; it writes out an HTTP header to begin its response, and then it
* writes out some HTML content for the response content. HTTP requests and
* responses are just lines of text (in a very particular format). 
*
**/

import java.net.Socket;
import java.lang.Runnable;
import java.io.*;
import java.util.*;
import java.util.Date;
import java.text.DateFormat;
import java.util.TimeZone;

public class WebWorker implements Runnable
{

//my global variables 
String line;
String line2;
public String filename;
String mimeType;
String s;
int errorCode;
int a;
long filesize; 
byte[] buffer;
InputStream file;


private Socket socket;

/**
* Constructor: must have a valid open socket
**/
public WebWorker(Socket s)
{
   socket = s;
}

/**
* Worker thread starting point. Each worker handles just one HTTP 
* request and then returns, which destroys the thread. This method
* assumes that whoever created the worker created it with a valid
* open socket object.
**/
public void run()
{
   System.err.println("Handling connection...");
   try( InputStream  is = socket.getInputStream();
      OutputStream os = socket.getOutputStream();) 
      {
      //My modified functions 
      readHTTPRequest(is, os);
      writeHTTPHeader(os, mimeType); 
      writeImage(os);
      //end of my modified functions
      
      os.flush();
      socket.close();
   } catch (Exception e) {
      System.err.println("Output error: "+e);
   }
   System.err.println("Done handling connection.");
   return;
}

/**
* Read the HTTP request header.
**/
private void readHTTPRequest(InputStream is, OutputStream os){

   BufferedReader r = new BufferedReader(new InputStreamReader(is));
   BufferedReader html;
   int count = 0;
   while (true) {
      try {
	      count++;
         while (!r.ready()) Thread.sleep(1);
         line = r.readLine();
      /*   
         //doesnt work for images for some reason 
         StringTokenizer serve = new StringTokenizer(line);
         if(serve.hasMoreElements() && serve.nextToken().equalsIgnoreCase("GET")
            && serve.hasMoreElements()){
         filename = serve.nextToken();
       }
        */
    //parses the GET command     
	   String client[] = line.split(" ");
	   if(client.length > 1 && count == 1){
	       filename = client[1];
	       filename = filename.substring(1);
   //changes the mimeType based on file extenstion
          if(filename.endsWith(".html"))
	          mimeType = "text/html";
	         else if(filename.endsWith(".gif"))
	                  mimeType = "image/gif";
	         else if(filename.endsWith(".jpg"))
	                  mimeType = "image/jpeg";
	         else if(filename.endsWith(".png"))
	                  mimeType = "image/png";
            else if(filename.endsWith(".ico"))
                     mimeType = "image/ico"; 
	         System.err.println(filename);
	}//end if
   
         System.err.println("Request line: ("+line+")");
         if (line.length()==0) break;
      } catch (Exception e) {
         System.err.println("Request error: "+e);
         break;
      }
   }//end while(true)


  try{
      if (mimeType == "text/html"){
      s = "";
      errorCode = 200;
      html = new BufferedReader(new FileReader(filename));
      //new date code for <cs371date>
      Date d1 = new Date();
      DateFormat df1 = DateFormat.getDateTimeInstance();
      df1.setTimeZone(TimeZone.getTimeZone("GMT"));

   	while((line2 = html.readLine()) != null){
            //tag code 
	         line2 = line2.replaceAll("<cs371date>", df1.format(d1));
	         line2 = line2.replaceAll("<cs371server>", "This is my server ID verification");
	          s += line2;
         if (line2.length()==0) 
         break;
	   }//end while
   }//end if(mimeType == "text/html")
    else{
      errorCode = 200;
      file = new FileInputStream(filename);
      filesize = new File(filename).length();
      buffer = new byte[(int)filesize];         
    }
  
      }//end try
       catch (Exception e) {
         errorCode = 404;
        } 	
        
       /**
       //my old file serving code
       //gives error:
       //Output error: java.net.SocketException: Software caused 
       //connection abort: socket write error

     InputStream file = new FileInputStream(filename);
     
     long fileSize = new File(filename).length();//gets the file length
     
     //sends file content to client   
     byte[] client = new byte[(int)fileSize];
     file.read(client);
     file.close();
     os.write(client);       
       
       **/ 
   return;
}//end readHTTPRequests()


/**
* Write the HTTP header lines to the client network connection.
* @param os is the OutputStream object to write to
* @param mimeType is the string MIME content type (e.g. "text/html")
**/
private void writeHTTPHeader(OutputStream os, String mimeType) throws Exception{
   Date d = new Date();
   DateFormat df = DateFormat.getDateTimeInstance();
   df.setTimeZone(TimeZone.getTimeZone("GMT"));
   if(errorCode == 200)
   os.write("HTTP/1.1 200 OK\n".getBytes());
   else if(errorCode == 404)
   os.write("HTTP/1.1 404 Not Found\n".getBytes());
  //os.write("Date: ".getBytes());
  //os.write((df.format(d)).getBytes());
  //os.write("\n".getBytes());
  //os.write("Server: Jon's very own server\n".getBytes());
   //os.write("Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n".getBytes());
   //os.write("Content-Length: 438\n".getBytes()); 
   //os.write("Connection: close\n".getBytes());
   os.write("Content-Type: ".getBytes());
   os.write(mimeType.getBytes());
   os.write("\n\n".getBytes()); // HTTP header ends with 2 newlines
   return;
}//end writeHTTPHeader


/*
 * My writeImage method
 * outputs the file 
 */
private void writeImage(OutputStream os) throws Exception{

      if(s != null)
         os.write(s.getBytes());

      else if(mimeType == "image/jpeg" || mimeType == "image/gif" || 
              mimeType == "image/png" || mimeType == "image/ico")
	            while((a=file.read(buffer))>0)
               os.write(buffer,0,a);
    
      if(errorCode == 404){
         os.write("<html><head></head><body>\n".getBytes());
         os.write("<h3>404: Error Page not Found!</h3>\n".getBytes());
         os.write("</body></html>\n".getBytes());
        }

    }//end writeImage()

} // end class
