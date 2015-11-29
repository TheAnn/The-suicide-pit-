package echo1;

import java.io.*;
import java.net.*;
import java.util.*;

public class Client {
    private static InetAddress host;
    private static final int PORT = 1234;
    
    private static void sendMessages(){
        Socket socket = null;
        try{
            socket = new Socket(host, PORT);
            Scanner input = new Scanner(socket.getInputStream());
            PrintWriter output = new PrintWriter(socket.getOutputStream(),true);
            System.out.println(host);
            Scanner userEntry = new Scanner(System.in);
            String message, response;
            do{
                System.out.print("Enter message (QUIT to exit): ");
                message = userEntry.nextLine();
                message=destro(message);
                output.println(message);
                
                response = input.nextLine();
                System.out.println("\nSERVER> " + response);
            }while (!message.equals("QUIT"));
        }
        catch(IOException ioEx){
            ioEx.printStackTrace();
        }
        finally{
            try{
                System.out.println("\nClosing connection ...");
                socket.close();
            }
            catch(IOException ioEx){
                System.out.println("Unable to disconnect!");
                System.exit(1);
            }
        }
    }
    
    public static void main(String[] args) {
        try{
            host = InetAddress.getLocalHost();
        }
        catch(UnknownHostException uhEx){
            System.out.println("\nHost ID not found!");
            System.exit(1);
        }
        sendMessages();
    }

    public static String destro(String source){
    	source=source.toLowerCase();
    	char[] sourceArr=source.toCharArray();
    	char[] alphabet = "abcdefghijklmnopqrstuvwxyz".toCharArray();
    	boolean isLetter;
    	for(int i=0;i<sourceArr.length;i++)
    	{
    		isLetter=false;
    		for(int j=0;j<alphabet.length;j++)
        	{
        		if(sourceArr[i]==alphabet[j])
        		{
        			isLetter=true;
        		}
        		
        	}
    		if(!isLetter)
    		{
    			sourceArr[i] = ' ';    		 		
    		}
    		
    		
    	}
    	source=new String(sourceArr);
    	return source;
    }
    
}
