import java.net.*;
import java.io.*;
import java.util.*;


public class TCPServer2 {
	//this is the input serverSocket
	private static ServerSocket serverSocketInput;
	//this is the input port
	private static final int PortInput = 1234;
	
	//this is the output serverSocket
	private static ServerSocket serverSocketOutput;
	//this is the output port
	private static final int PortOutput = 1235;
	
	public static String clientMessage = "";
	
	public static void main (String[] args){
		
		try{
			//try connecting with input client
			System.out.println("Opening port for Input Clients...\n");
			serverSocketInput = new ServerSocket(PortInput);
			
			//try connecting with output client
			System.out.println("Opening port for Output Clients...\n");
			serverSocketOutput = new ServerSocket(PortOutput);
			
			}
		catch (IOException e){
			System.out.println("Unable to attach" + e.getMessage());
			System.exit(1);
		}
		
		System.out.println("Waiting Connections...");

		
			//if that worked then. This do while loop doesn't exist in the client.
			do { 
				//start a loop that runs forever
				//new socket for handling the client. That is done when we accept the connection from the client
				
				try {
					Socket clientInput = serverSocketInput.accept();
					System.out.println("Input Client Connected!");
					ClientHandlerInput handlerInput = new ClientHandlerInput(clientInput, clientMessage);
					handlerInput.start();
					System.out.println("Thread Started for Input Client!");
					
					Socket clientOutput = serverSocketOutput.accept();
					System.out.println("Output Client Connected!");
					ClientHandlerOutput handlerOutput = new ClientHandlerOutput(clientOutput, clientMessage);
					handlerOutput.start();
					System.out.println("Thread Started for Output Client!");
					
				} catch (IOException e) {
					System.out.println("Unable to attach" + e.getMessage());
					System.exit(1);
				}
				
			}
			while(true);	
	}
}