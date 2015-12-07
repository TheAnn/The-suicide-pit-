import java.net.*;
import java.util.*;
import java.io.*;

import javax.print.DocFlavor.CHAR_ARRAY;

public class TCPOutputClient2 {
	
	//internet address of the host
	private static InetAddress host;
	//port number
	private static final int Port = 1235;
	
	public static void main(String[] args){
		try{
			//the server and the client in our case are running on the same machine
			//so we don't need to find a diff. address
			host = InetAddress.getLocalHost();
		}
		catch(UnknownHostException uhEx){
			System.out.println("Host ID not found!");
			System.exit(1);
		}
		//create a new method to access the server. Step 1.
		accessServer();
	}
	//say what the method does
	private static void accessServer(){
		Socket link = null;
		try{
			//requesting connection between client and server
			link = new Socket(host, Port);
			//server has accepted the connection from the client here
			//input and output streams. Step 2
			Scanner input = new Scanner(link.getInputStream());
			PrintWriter output = new PrintWriter(link.getOutputStream(), true);
			
			//client should send messages to the server Messages from user
			Scanner userEntry = new Scanner(System.in);
			//client send and receive messages. Step 3.
			String message;
			
			//loop
			//do{
				//recebe mensagem
				message = input.nextLine();
				
				BinaryTreeClass bt = new BinaryTreeClass();
				bt.btClass(message);
				
				//we've now sent the message to the server. The server sends a response that needs to be catched
				System.out.println("\nSERVER: " + message);	

			//} /*we do this as long as this -->*/ while(!message.equals("QUIT"));
		}
		catch (IOException ioEx){
			ioEx.printStackTrace();
		}
		finally{
			try{
				System.out.println("\nClosing connection...");
				link.close();
			}
			catch(IOException ioEx){
				System.out.println("Unable to disconnect!");
				System.exit(1);
				
			}
		}
	}
}

