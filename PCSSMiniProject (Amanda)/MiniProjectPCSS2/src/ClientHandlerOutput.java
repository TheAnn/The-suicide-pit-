
import java.io.*;
import java.net.*;
import java.util.*;

public class ClientHandlerOutput extends Thread {
	
	private Socket client;
	private Scanner input;
	private PrintWriter output;
	private String receivedClientMessage;
	
	public ClientHandlerOutput(Socket socket, String clientMessage){
		this.receivedClientMessage = clientMessage;
		client = socket;
		//try to set up the input and output stream to server
		try{
			input = new Scanner(client.getInputStream());
			// we pass he output stream of the socket to the printwriter
			output = new PrintWriter(client.getOutputStream(), true);
		}
		catch(IOException ioEx){
			//because we don't know what issue went wrong
			ioEx.printStackTrace();
		}
	}
	
	public void run(){
		
		do{
			//make method to bubble sort, binary tree, quicksort
			//sends modified message to the client
			this.receivedClientMessage = "Message Received from Client Handler";
			output.println(this.receivedClientMessage);

		}
		//we do that as long as the equals has not received "QUIT" message
		while (!this.receivedClientMessage.equals("QUIT"));
		
		try{
			if (client!=null){
				System.out.println("Closing connection...");
				client.close();
			}
		}
		catch(IOException ioEx){
			System.out.println("Inable to disconnet");
			//is the server is unable to disconnect we exit
		}
	}
	
	//method per sé is here

}
