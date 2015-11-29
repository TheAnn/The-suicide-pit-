package echo1;

import java.io.*;
import java.net.*;

public class Server {
    private static ServerSocket serverSocket;
    private static final int PORT = 1234;
    public static void main(String[] args) throws IOException{
        try{
            serverSocket = new ServerSocket(PORT);
            System.out.println("\nPort set up!");
        }
        catch(IOException ioEx){
            System.out.println("\nUnable to set up port!");
            System.exit(1);
        }

        do{
            Socket client = serverSocket.accept();
            System.out.println("\nNew client accepted.\n");
            ClientHandler handler = new ClientHandler(client);
            handler.start();
        } while(true);
    }

}
