
import java.io.*;
import java.net.*;
import java.util.*;

public class ClientHandlerOutput extends Thread {
	
	private Socket client;
	private PrintWriter output;
	
	public ClientHandlerOutput(Socket socket){
		client = socket;
		//try to set up the input and output stream to server
		try{
			// we pass the output stream of the socket to the printwriter
			output = new PrintWriter(client.getOutputStream(), true);
		}
		catch(IOException ioEx){
			//because we don't know what issue went wrong
			ioEx.printStackTrace();
		}
	}
	
	// void would mean that the function would't return anything
	//map is the type of the return of the function
	public Map<String, Integer> splitWords(String message){
		
		//this counts the number of characters in a word using a hash map
		Map<String, Integer> numWords = new HashMap<String, Integer>(Math.min(message.length(), 26));
		
		String[] wordAt = new String[] {};		
		//split returns a vector of strings
		wordAt = message.split(" ");
			
		//for each letter in the message count the time the characters appear
		for (int i = 0; i < wordAt.length; i++){
			
		    if (!numWords.containsKey(wordAt[i]))
		    {
		        numWords.put(wordAt[i], 1);
		    }
		    else
		    {
		        numWords.put(wordAt[i], numWords.get(wordAt[i]) + 1);
		    }
		}
		return numWords;
	}
	
	public void run(){

		splitWords(TCPServer2.getClientMessage());

		//make method to bubble sort, binary tree, quicksort
		//sends modified message to the client

		output.println(TCPServer2.getClientMessage());

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

	//method per sé is here

}
