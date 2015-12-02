
import java.io.*;
import java.net.*;
import java.util.*;

public class ClientHandlerInput extends Thread {
	
	private Socket client;
	private Scanner input;
	private PrintWriter output;
	private String receivedClientMessage;
	
	public ClientHandlerInput(Socket socket, String clientMessage){
		this.receivedClientMessage = clientMessage;
		client = socket;
		//try to set up the input and output stream to server
		try{
			input = new Scanner(client.getInputStream());
			// we pass the output stream of the socket to the printwriter
			output = new PrintWriter(client.getOutputStream(), true);
		}
		catch(IOException ioEx){
			//because we don't know what issue went wrong
			ioEx.printStackTrace();
		}
	}
	
	public void run(){
		do{
			//we save the input message in the received String
			this.receivedClientMessage = input.nextLine();
			output.println("Message Received.");
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
			System.out.println("Unnable to disconnet");
			//is the server is unable to disconnect we exit
		}
	}

}
