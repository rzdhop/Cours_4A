import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class HTTPdServerV2 {

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
        
                BufferedWriter out = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
        
                InputStream indexFile = new FileInputStream("index.html");
        

                byte[] buffer=new byte[4096];
                int size;
                String s;

                out.write("HTTP/1.0 200 OK\r\n");
                out.write("Server: HandMade ESIEA\r\n");
                out.write("Content-Type: text/html\r\n");
                out.write("Content-Length: 59\r\n");
                out.write("\r\n");

                while ((size = indexFile.read(buffer)) > 0){
                    s = new String(buffer, StandardCharsets.UTF_8);
                    out.write(s, 0, size);
                }
                indexFile.close();
                
                System.err.println("Fin de communication.");
                out.close();
                
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
