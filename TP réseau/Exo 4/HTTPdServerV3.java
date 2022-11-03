import java.io.*;
import java.net.*;

public class HTTPdServerV3 {

    public static void main(String[] args){

        int port = Integer.parseInt(args[0]);
        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(port);
        }
        catch(IOException e){
            System.err.println("Le port spécifié n'est pas disponible.");
            return;
        }
        
        System.err.println("Instance du server est lancé sur le port " + port);
    
        try{
            while (true) {
                
                Socket clientSocket = serverSocket.accept();
                System.err.println("Client détécté");
        
        
                BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                BufferedWriter out = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
                
                
                String s;
                while ((s = in.readLine()) != null) {
                    System.out.println(s);
                }
                out.write("HTTP/1.0 200 OK\r\n");
                out.write("Server: HandMade ESIEA\r\n");
                out.write("Content-Type: text/html\r\n");
                out.write("Content-Length: 59\r\n");
                out.write("\r\n");
                out.write("<!DOCTYPE html>");
                out.write("<html><head><title>tete de page</title></head><body><p>Super page Internet</p></body></html>");
                
                System.err.println("Fin de communication.");
                out.close();
                in.close();
                clientSocket.close();
            }
        }
        catch(Exception e) {
            System.err.println("Fermeture de la session du server");
            try {
                serverSocket.close();
            }
            catch(IOException y){
                System.err.println("Erreur lors de la fermeture du server");
            }
            
        }
        
    }
}
